# Scratch [![Build Status](https://travis-ci.org/angelog/Scratch.svg?branch=master)](https://travis-ci.org/angelog/Scratch)

**NOTE:** This library is being replaced by its successor: [scratch2](https://github.com/codecat/scratch2).

Scratch, a header-only core library. Thread-safe by default. Currently includes the following classes:

* Strings:
  * `String`
  * `Filename`
* Containers:
	* `Array` (a much faster alternative than StackArray)
  * `StackArray`
  * `Dictionary`
* Streams:
  * `Stream`
  * `FileStream`
  * `NetworkStream`
  * `MemoryStream`
* Control flow:
  * `Exception`
  * `Mutex`
  * `Assert`
  * `Function`

## Usage
Include Scratch.hpp in at least 1 implementation file while `SCRATCH_IMPL` is defined.

```C++
#define SCRATCH_IMPL
#include <Scratch.hpp>

#include <stdio.h>

int main()
{
  Scratch::String foo = "Hello";
  foo += " world!";
  printf("foo = '%s'\n", (const char*)foo);
  return 0;
}
```

If you want to rename the Scratch namespace, you can do that by defining `SCRATCH_NAMESPACE` before including Scratch.hpp:

```C++
#define SCRATCH_IMPL
#define SCRATCH_NAMESPACE s
#include <Scratch.hpp>
```

Note that if you choose to rename the namespace, you have to define `SCRATCH_NAMESPACE` for both the implementation and everywhere else you're including Scratch.

*Note:* At the moment of writing, on Linux, you will be required to link your application against pthreads.

## Options
There are a few specific precompiler definitions you can use during implementation compilation (SCRATCH_IMPL) that modify the behavior of the library.

* `SCRATCH_NO_UTF8`: Disable utf8 support.
* `SCRATCH_NO_THREADSAFE`: Don't enable mutex locking in classes.
* `SCRATCH_NO_EXCEPTIONS`: Don't throw any exceptions, silently fail instead.
* `SCRATCH_NO_ASSERT`: Don't define a custom ASSERT().

## License
Scratch is licensed under the permissive MIT license.
