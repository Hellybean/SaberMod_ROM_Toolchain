//===-- sanitizer_common.cc -----------------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file is shared between AddressSanitizer and ThreadSanitizer
// run-time libraries.
//===----------------------------------------------------------------------===//

#include "sanitizer_common.h"
#include "sanitizer_libc.h"

namespace __sanitizer {

const char *SanitizerToolName = "SanitizerTool";
uptr SanitizerVerbosity = 0;

uptr GetPageSizeCached() {
  static uptr PageSize;
  if (!PageSize)
    PageSize = GetPageSize();
  return PageSize;
}


// By default, dump to stderr. If |log_to_file| is true and |report_fd_pid|
// isn't equal to the current PID, try to obtain file descriptor by opening
// file "report_path_prefix.<PID>".
fd_t report_fd = kStderrFd;

// Set via __sanitizer_set_report_path.
bool log_to_file = false;
char report_path_prefix[sizeof(report_path_prefix)];

// PID of process that opened |report_fd|. If a fork() occurs, the PID of the
// child thread will be different from |report_fd_pid|.
uptr report_fd_pid = 0;

static DieCallbackType DieCallback;
void SetDieCallback(DieCallbackType callback) {
  DieCallback = callback;
}

DieCallbackType GetDieCallback() {
  return DieCallback;
}

void NORETURN Die() {
  if (DieCallback) {
    DieCallback();
  }
  internal__exit(1);
}

static CheckFailedCallbackType CheckFailedCallback;
void SetCheckFailedCallback(CheckFailedCallbackType callback) {
  CheckFailedCallback = callback;
}

void NORETURN CheckFailed(const char *file, int line, const char *cond,
                          u64 v1, u64 v2) {
  if (CheckFailedCallback) {
    CheckFailedCallback(file, line, cond, v1, v2);
  }
  Report("Sanitizer CHECK failed: %s:%d %s (%lld, %lld)\n", file, line, cond,
                                                            v1, v2);
  Die();
}

uptr ReadFileToBuffer(const char *file_name, char **buff,
                      uptr *buff_size, uptr max_len) {
  uptr PageSize = GetPageSizeCached();
  uptr kMinFileLen = PageSize;
  uptr read_len = 0;
  *buff = 0;
  *buff_size = 0;
  // The files we usually open are not seekable, so try different buffer sizes.
  for (uptr size = kMinFileLen; size <= max_len; size *= 2) {
    uptr openrv = OpenFile(file_name, /*write*/ false);
    if (internal_iserror(openrv)) return 0;
    fd_t fd = openrv;
    UnmapOrDie(*buff, *buff_size);
    *buff = (char*)MmapOrDie(size, __FUNCTION__);
    *buff_size = size;
    // Read up to one page at a time.
    read_len = 0;
    bool reached_eof = false;
    while (read_len + PageSize <= size) {
      uptr just_read = internal_read(fd, *buff + read_len, PageSize);
      if (just_read == 0) {
        reached_eof = true;
        break;
      }
      read_len += just_read;
    }
    internal_close(fd);
    if (reached_eof)  // We've read the whole file.
      break;
  }
  return read_len;
}

typedef bool UptrComparisonFunction(const uptr &a, const uptr &b);

template<class T>
static inline bool CompareLess(const T &a, const T &b) {
  return a < b;
}

void SortArray(uptr *array, uptr size) {
  InternalSort<uptr*, UptrComparisonFunction>(&array, size, CompareLess);
}

// We want to map a chunk of address space aligned to 'alignment'.
// We do it by maping a bit more and then unmaping redundant pieces.
// We probably can do it with fewer syscalls in some OS-dependent way.
void *MmapAlignedOrDie(uptr size, uptr alignment, const char *mem_type) {
// uptr PageSize = GetPageSizeCached();
  CHECK(IsPowerOfTwo(size));
  CHECK(IsPowerOfTwo(alignment));
  uptr map_size = size + alignment;
  uptr map_res = (uptr)MmapOrDie(map_size, mem_type);
  uptr map_end = map_res + map_size;
  uptr res = map_res;
  if (res & (alignment - 1))  // Not aligned.
    res = (map_res + alignment) & ~(alignment - 1);
  uptr end = res + size;
  if (res != map_res)
    UnmapOrDie((void*)map_res, res - map_res);
  if (end != map_end)
    UnmapOrDie((void*)end, map_end - end);
  return (void*)res;
}

void ReportErrorSummary(const char *error_type, const char *file,
                        int line, const char *function) {
  const int kMaxSize = 1024;  // We don't want a summary too long.
  InternalScopedBuffer<char> buff(kMaxSize);
  internal_snprintf(buff.data(), kMaxSize, "%s: %s %s:%d %s",
                    SanitizerToolName, error_type,
                    file ? file : "??", line, function ? function : "??");
  __sanitizer_report_error_summary(buff.data());
}

LoadedModule::LoadedModule(const char *module_name, uptr base_address) {
  full_name_ = internal_strdup(module_name);
  base_address_ = base_address;
  n_ranges_ = 0;
}

void LoadedModule::addAddressRange(uptr beg, uptr end) {
  CHECK_LT(n_ranges_, kMaxNumberOfAddressRanges);
  ranges_[n_ranges_].beg = beg;
  ranges_[n_ranges_].end = end;
  n_ranges_++;
}

bool LoadedModule::containsAddress(uptr address) const {
  for (uptr i = 0; i < n_ranges_; i++) {
    if (ranges_[i].beg <= address && address < ranges_[i].end)
      return true;
  }
  return false;
}

}  // namespace __sanitizer

using namespace __sanitizer;  // NOLINT

extern "C" {
void __sanitizer_set_report_path(const char *path) {
  if (!path) return;
  uptr len = internal_strlen(path);
  if (len > sizeof(report_path_prefix) - 100) {
    Report("ERROR: Path is too long: %c%c%c%c%c%c%c%c...\n",
           path[0], path[1], path[2], path[3],
           path[4], path[5], path[6], path[7]);
    Die();
  }
  internal_strncpy(report_path_prefix, path, sizeof(report_path_prefix));
  report_path_prefix[len] = '\0';
  report_fd = kInvalidFd;
  log_to_file = true;
}

void __sanitizer_set_report_fd(int fd) {
  if (report_fd != kStdoutFd &&
      report_fd != kStderrFd &&
      report_fd != kInvalidFd)
    internal_close(report_fd);
  report_fd = fd;
}

void NOINLINE __sanitizer_sandbox_on_notify(void *reserved) {
  (void)reserved;
  PrepareForSandboxing();
}

void __sanitizer_report_error_summary(const char *error_summary) {
  Printf("SUMMARY: %s\n", error_summary);
}
}  // extern "C"
