// { dg-require-namedlocale "en_US" }
// { dg-require-namedlocale "de_DE" }

// 1999-10-11 bkoz

// Copyright (C) 1999-2013 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.


// 27.5.2 template class basic_streambuf

#include <streambuf>
#include <locale>
#include <testsuite_hooks.h>

class testbuf : public std::wstreambuf
{
public:
  typedef std::wstreambuf::traits_type traits_type;

  testbuf() : std::wstreambuf() { }
};

// libstdc++/9322
void test08()
{
  using std::locale;
  bool test __attribute__((unused)) = true;

  locale loc;
  testbuf ob;
  VERIFY( ob.getloc() == loc );

  locale::global(locale("en_US"));
  VERIFY( ob.getloc() == loc );

  locale loc_de = locale("de_DE");
  locale ret = ob.pubimbue(loc_de);
  VERIFY( ob.getloc() == loc_de );
  VERIFY( ret == loc );

  locale::global(loc);
  VERIFY( ob.getloc() == loc_de );
}

int main() 
{
  test08();
  return 0;
}
