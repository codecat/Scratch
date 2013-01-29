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

#include "Common.h"

/* CString: high level string management
 * -------------------------------------
 * Basic usage:
 *   CString strFoo = "Scratch"; // Scratch
 *   CString strBar = "lib" + strFoo.ToLower(); // libscratch
 *   CString strTest = strBar.Replace("libs", "S") + "!"; // Scratch!
 *
 *   CStackArray<CString> astrParse = strTest.Split("c");
 *   ASSERT(astrParse.Count() == 3);
 *   ASSERT(astrParse[0] == "S");
 *   ASSERT(astrParse[1] == "rat");
 *   ASSERT(astrParse[2] == "h");
 */
#include "CString.h"

/* CStackArray: high level array management
 * ----------------------------------------
 * Basic usage:
 *   CStackArray<int> aiTest;
 *   aiTest.Push() = 5;
 *   aiTest.Push() = 10;
 *   aiTest.Push() = 123;
 *   ASSERT(aiTest[0] == 5);
 *   ASSERT(aiTest.Pop() == 123);
 *   ASSERT(aiTest.Count() == 2);
 */
#include "CStackArray.h"

/* CDictionary: high level table management
 * ----------------------------------------
 * Basic usage:
 *   CDictionary<CString, CString> dstrTest;
 *   dstrTest.Add("Name", "libscratch");
 *   dstrTest["Author"] = "Angelo Geels";
 */
#include "CDictionary.h"

/* CFileStream: high level file stream management
 * ----------------------------------------------
 * Basic usage:
 *   CFileStream fs;
 *   fs.Open("test.bin", "r+");
 *   INDEX iTest;
 *   fs >> iTest;
 *   fs << iTest * 2;
 *   fs.Close();
 */
#include "CFileStream.h"

/* CMemoryStream: high level memory stream management
 * --------------------------------------------------
 * Basic usage:
 *   CMemoryStream ms;
 *   ms << INDEX(5);
 *   CFileStream fs;
 *   fs.Open("test.bin", "w");
 *   fs << ms.Size();
 *   fs << ms;
 */
#include "CMemoryStream.h"

/* Vectors: high level vectors
 * ---------------------------
 * Basic usage:
 *   Vector3f vPos;
 *   vPos *= 2.0f;
 */
#include "CVectors.h"
