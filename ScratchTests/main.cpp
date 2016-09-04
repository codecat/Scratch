#include <stdio.h>

// This is so that we can access private fields for
// checking their values in tests.

#ifndef _MSC_VER
// Visual Studio: fatal error C1189: #error :	The C++ Standard Library forbids macroizing keywords. Enable warning C4005 to find the forbidden macro.
#define TEST_PRIVATE(expr) TEST(expr)

#define protected public
#define private public
#else
#define TEST_PRIVATE(expr)
#endif

#define SCRATCH_IMPL
#include <Scratch.hpp>
using namespace Scratch;

static int g_iTestNumber = 1;
static int g_iTestOK = 0;
static int g_iTestFailed = 0;

#if DEBUG
	#if WINDOWS
		#define TEST_BREAK() __asm { int 3 };
	#else
		#define TEST_BREAK() __asm__("int $0x03");
	#endif
#else
	#define TEST_BREAK()
#endif

#define TESTS(id) \
	if(!strcmp(strArg, id) || !strcmp(strArg, "All"))

#define TEST(expr) { \
	if(!(expr)) { \
		puts(TERMCOL_RED "\u2717 [FAIL] " TERMCOL_RESET #expr); \
		g_iTestFailed++; \
		TEST_BREAK(); \
	} else { \
		puts(TERMCOL_GREEN "\u2713 [ OK ] " TERMCOL_RESET #expr); \
		g_iTestOK++; \
	} \
	g_iTestNumber++; \
}

#if WINDOWS
#define TEST_WINDOWS(expr) TEST(expr)
#define TEST_UNIX(expr)
#define MAIN int wmain(int argc, wchar_t* argv[])
#else
#define TEST_WINDOWS(expr)
#define TEST_UNIX(expr) TEST(expr)
#define MAIN int main(int argc, char* argv[])
#endif

// Used in testing Function<>
static int FunctionTest(int x)
{
	return x * x * x;
}

static int FunctionTest2(const Function<int(int)> &f, int x)
{
	return f(x);
}

MAIN
{
	const char* strArg = nullptr;

	char buffer[1024];
	if(argc > 1) {
#if WINDOWS
		int writen = wcstombs(buffer, argv[1], sizeof(buffer));
		if (writen == 1024) {
			printf("Invalid test name given");
			return -1;
		}

		strArg = buffer;
#else
		strArg = argv[1];
#endif
	} else {
		printf("No test name given!\n");
		printf("Pass \"All\" to run all tests.\n");
		return 1;
	}

	TESTS("String")
	{
		String strFoo;
		TEST_PRIVATE(strFoo.str_szBuffer == String::str_szEmpty);

		strFoo = "a";
		TEST(strFoo == "a");

		strFoo = "";
		TEST_PRIVATE(strFoo.str_szBuffer == String::str_szEmpty);

		int x = 5;
		int y = 10;
		strFoo.SetF("%d %d", x, y);
		TEST(strFoo == "5 10");

		strFoo.AppendF(" %d", x);
		TEST(strFoo == "5 10 5");

		StackArray<String> aParse;
		strFoo.Split(" ", aParse);
		TEST(aParse.Count() == 3);
		TEST(aParse[0] == "5" && aParse[1] == "10" && aParse[2] == "5");

		StackArray<String> aParseCmd;
		strFoo = "test \"foo bar\" abc xyz";
		strFoo.CommandLineSplit(aParseCmd);
		TEST(aParseCmd[0] == "test" && aParseCmd[1] == "foo bar" && aParseCmd[2] == "abc" && aParseCmd[3] == "xyz");

		strFoo = "      Foo  ";
		TEST(strFoo.Trim() == "Foo");
		TEST(strFoo.TrimLeft() == "Foo  ");
		TEST(strFoo.TrimRight() == "      Foo");

		strFoo = "..Foo!!";
		TEST(strFoo.Trim('!') == "..Foo");
		TEST(strFoo.TrimLeft('.') == "Foo!!");
		TEST(strFoo.TrimRight('!') == "..Foo");

		strFoo = "/";
		TEST(strFoo.TrimRight('/') == "");

		strFoo = "foo";
		TEST(strFoo.Replace("foo", "bar") == "bar");

		strFoo = "a a b b a";
		TEST(strFoo.Replace("b", "a") == "a a a a a");

		TEST(strFoo.SubString(4, 3) == "b b");

		TEST(strFoo.ToUpper() == "A A B B A");

		strFoo = "A A B B A";
		TEST(strFoo.ToLower() == "a a b b a");

		strFoo = "AbcXyzAbcXyz!!";
		TEST(strFoo.IndexOf('X') == 3);
		TEST(strFoo.IndexOf("Xyz") == 3);
		TEST(strFoo.IndexOfLast('X') == 9);
		TEST(strFoo.IndexOfLast("Xyz") == 9);

		strFoo.Fill('x', 5);
		TEST(strFoo == "xxxxx");

		strFoo = "BaaaaaXaaaB";
		TEST(strFoo.Contains('X'));
		TEST(strFoo.Contains("Xaaa"));

		TEST(strFoo.StartsWith("Baaa"));
		TEST(strFoo.EndsWith("aaaB"));
		TEST(!strFoo.EndsWith("Xaaa"));

		TEST_PRIVATE((const char*)strFoo == strFoo.str_szBuffer);

		strFoo = "x";
		strFoo += "x";
		strFoo += String("x");

		TEST(strFoo == "xxx");

		strFoo *= 3;
		TEST(strFoo == "xxxxxxxxx");
		TEST(strFoo != "aaaaaaaaa");

		strFoo = "x";
		TEST(strFoo + "y" == "xy");

		TEST(strFoo * 3 == "xxx");

		TEST(strPrintF("Hello %d %d", x, y) == "Hello 5 10");

		for (int i = 1; i <= 6; i++) {
			TEST(strPrintF("F%d", i).Length() == 2);
		}

		String strA = "Aaaa";
		String strB = "Bbbb";
		TEST(strA < strB);
		TEST(strB > strA);
		TEST(strA <= strA);
		TEST(strB >= strB);

#ifndef SCRATCH_NO_UTF8
		String strUtf8;
		strUtf8 += 0x888d90f0;
		TEST(strUtf8.Length() == 1);
#endif
	}

	TESTS("Filename")
	{
		Filename fnmFoo;

		TEST_PRIVATE(fnmFoo.str_szBuffer == String::str_szEmpty);

		fnmFoo = "/var/www/test.html";
		TEST(fnmFoo.Extension() == "html");
		TEST(fnmFoo.Path() == "/var/www/");
		TEST(fnmFoo.PathName() == "www");
		TEST(fnmFoo.Name() == "test.html");

		fnmFoo = "/home";
		TEST(fnmFoo.Path() == "/");

		fnmFoo = "/";
		TEST(fnmFoo.Path() == "/");

		fnmFoo.FromHome(".zshrc");
		TEST_WINDOWS(fnmFoo.StartsWith("C:\\Users"));
		//TEST_UNIX(fnmFoo.StartsWith("/home/")); // This test isn't very accurate
	}

	TESTS("StackArray")
	{
		StackArray<int> sa;
		TEST(sa.Count() == 0);

		sa.Push() = 5;
		TEST(sa.Count() == 1);
		TEST(sa[0] == 5);

		sa.PushBegin() = 10;
		TEST(sa.Count() == 2);
		TEST(sa[0] == 10);

		int* pNewInt = new int;
		*pNewInt = 15;
		sa.Push(pNewInt);
		TEST(sa.Count() == 3);
		TEST(sa[2] == 15);

		int* pLastInt = sa.Pop();
		TEST(sa.Count() == 2);
		TEST(pLastInt == pNewInt);
		delete pLastInt;

		delete sa.PopAt(0);
		TEST(sa.Count() == 1);
		TEST(sa[0] == 5);

		int* pRemainingInt = &sa[0];
		sa.PopAll();
		TEST(sa.Count() == 0);
		TEST(*pRemainingInt == 5);
		delete pRemainingInt;

		sa.Push() = 20;
		sa.Clear();
		TEST(sa.Count() == 0);

		pNewInt = new int;
		*pNewInt = 15;
		sa.Push() = 5;
		sa.Push() = 10;
		sa.Push(pNewInt);
		sa.Push() = 20;
		TEST(sa.Find(10) == 1);
		TEST(sa.Find(25) == -1);
		TEST(sa.FindPointer(pNewInt) == 2);
		TEST(sa.FindAny([](int &i) { return i == 20; }) == 3);

		TEST(sa.Contains(15));
		TEST(!sa.Contains(25));
		TEST(sa.ContainsPointer(pNewInt));
		TEST(sa.ContainsAny([](int &i) { return i == 20; }));

		StackArray<int> arr;
		arr.Push() = 5;
		arr.Push() = 10;
		arr.Push() = 15;
		int iSum = 0;
		int iCount = 0;
		for (int i : arr) {
			iSum += i;
			iCount++;
		}
		TEST(iCount == 3);
		TEST(iSum == 30);
	}

	TESTS("Dictionary")
	{
		Dictionary<String, int> dic;
		TEST(dic.Count() == 0);

		dic.Add("foo", 5);
		TEST(dic.Count() == 1);
		TEST(dic["foo"] == 5);

		dic["bar"] = 10;
		TEST(dic["bar"] == 10);

		DictionaryPair<String, int> &pair = dic.Push("foobar");
		pair.value = 15;
		TEST(dic["foobar"] == 15);

		TEST(dic.IndexByKey("bar") == 1);
		TEST(dic.IndexByValue(10) == 1);

		TEST(dic.HasKey("foobar"));
		TEST(dic.HasValue(15));

		dic.RemoveByIndex(0);
		TEST(dic.Count() == 2);
		TEST(!dic.HasKey("foo"));

		dic.RemoveByKey("bar");
		TEST(dic.Count() == 1);
		TEST(!dic.HasKey("bar"));

		dic.RemoveByValue(15);
		TEST(dic.Count() == 0);

		dic["foo"] = 5;
		dic["bar"] = 10;
		dic["foobar"] = 15;
		dic["barfoo"] = 20;
		TEST(dic.Count() == 4);
		delete &dic.PopByIndex(0);
		TEST(dic.Count() == 3);
		TEST(!dic.HasKey("foo"));
		delete &dic.PopByKey("bar");
		TEST(dic.Count() == 2);
		TEST(!dic.HasKey("bar"));
		delete &dic.PopByValue(15);
		TEST(dic.Count() == 1);
		TEST(!dic.HasKey("foobar"));

		dic.Clear();
		TEST(dic.Count() == 0);

		dic["foo"] = 5;
		dic["bar"] = 10;
		TEST(dic.GetKeyByIndex(0) == "foo");
		TEST(dic.GetValueByIndex(1) == 10);
	}

	TESTS("FileStream")
	{
		FileStream fsWriter;
		fsWriter.Open("test.txt", "w");
		fsWriter.WriteLine("foo");
		fsWriter.WriteLine("bar");
		fsWriter << int32_t(5);
		fsWriter << float(2.5f);
		fsWriter << String("test");
		fsWriter.Close();

		FileStream fsReader;
		fsReader.Open("test.txt", "r");

		TEST(fsReader.ReadLine() == "foo");
		TEST(fsReader.ReadLine() == "bar");

		int32_t i;
		float f;
		String s;

		fsReader >> i;
		TEST(i == 5);

		fsReader >> f;
		TEST(f > 2.0f && f < 3.0f);

		fsReader >> s;
		TEST(s == "test");

		fsReader.ReadChar();
		TEST(fsReader.AtEOF());

		fsReader.Close();
	}

	TESTS("Mutex")
	{
		Mutex mutex;

		{
			TEST(mutex.TryLock() == true);
			TEST(mutex.TryLock() == false);
			mutex.Unlock();
		}

		{
			mutex.Lock();
			mutex.Unlock();
		}

		{
			MutexWait wait(mutex);
		}
	}

#ifndef SCRATCH_NO_EXCEPTIONS
	TESTS("Exception")
	{
		try {
			throw Exception("%d", 123);
		} catch(Exception &ex) {
			TEST(ex.Message == "123");
		}
	}
#endif

	TESTS("Function")
	{
		Function<int(int)> fd = [](int x) { return x * 2; };
		TEST(fd(10) == 20);
		TEST(fd(100) == 200);

		fd = [](int x) { return x * x; };
		TEST(fd(10) == 100);
		TEST(fd(50) == 2500);

		bool b = false;
		Function<void()> fs = [&b]() { b = true; };
		fs();
		TEST(b == true);
		TEST(fs != nullptr);

		Function<int(int)> fp = &FunctionTest;
		TEST(fp(10) == 1000);
		TEST(fp(50) == 125000);
		TEST(fp != nullptr);

		Function<void()> fn = nullptr;
		TEST(fn == nullptr);

		Function<int(int)> &fpr = fp;
		TEST(fpr(10) == 1000);

		Function<int(int)>* fdp = &fd;
		TEST((*fdp)(10) == 100);

		TEST(FunctionTest2([](int x) { return x * 2; }, 10) == 20);

		Function<int()> f1 = []() { return 10; };
		Function<int()> f2 = [f1]() { return f1(); };
		Function<void()> f3 = [f2]() {
			TEST(f2() == 10);
		};
		f3();
	}

	printf("\n");
	printf("      OK: %d\n", g_iTestOK);
	printf("  Failed: %d\n", g_iTestFailed);
	printf("\n");

#if _DEBUG
	getchar();
#endif

	return g_iTestFailed;
}
