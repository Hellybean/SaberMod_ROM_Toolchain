
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __java_util_concurrent_Executors$FinalizableDelegatedExecutorService__
#define __java_util_concurrent_Executors$FinalizableDelegatedExecutorService__

#pragma interface

#include <java/util/concurrent/Executors$DelegatedExecutorService.h>

class java::util::concurrent::Executors$FinalizableDelegatedExecutorService : public ::java::util::concurrent::Executors$DelegatedExecutorService
{

public: // actually package-private
  Executors$FinalizableDelegatedExecutorService(::java::util::concurrent::ExecutorService *);
public: // actually protected
  virtual void finalize();
public:
  static ::java::lang::Class class$;
};

#endif // __java_util_concurrent_Executors$FinalizableDelegatedExecutorService__
