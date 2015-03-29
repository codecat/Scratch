/*  libscratch - Multipurpose objective C++ library.
    
    Copyright (c) 2015 Angelo Geels <spansjh@gmail.com>
    
    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:
    
    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/

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

/* CNetworkStream: high level network connections management
 * ---------------------------------------------------------
 * Basic usage:
 *   CNetworkStream ns;
 *   ns.Connect("127.0.0.1", 1234);
 *   ns << INDEX(5);
 *   INDEX iResult;
 *   ns >> iResult;
 *   ns.Close();
 */
#include "CNetworkStream.h"
