/*  libscratch - Multipurpose objective C++ library.
    Copyright (C) 2012 - 2013  Angelo Geels

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include <cstdio> // for printf
#include <iostream> // for std::cin.get

#include <Scratch.h>

static INDEX _ctFailed = 0;

#define TEST(expr) ASSERT(expr);    \
  printf("  Test: (%s) ", #expr);   \
  if(!(expr)) {                     \
    _ctFailed++;                    \
    printf("FAILED!\n");            \
  } else {                          \
    printf("OK\n");                 \
  }

void TestString()
{
  printf("Testing strings\n");

  CString strTest;
  strTest += "Lib";
  strTest += "Scratch";
  strTest = strTest.ToLower();
  TEST(strTest == "libscratch");

  strTest += " is great";
  CStackArray<CString> astrParse = strTest.Split(" ");
  TEST(astrParse[2] == "great");
  TEST(astrParse[2][1] == 'r');

  CString strTest2 = strTest.Replace("great", "cool");
  TEST(strTest2 == "libscratch is cool");
}

int main()
{
  TestString();

  if(_ctFailed == 0) {
    printf("\n\nAll OK!\n");
  } else {
    printf("\n\nSome problems seem to have popped up. Please report a bug.\n");
  }

  std::cin.get();
  return 0;
}
