# Scratch [![Build Status](https://travis-ci.org/AngeloG/Scratch.svg?branch=master)](https://travis-ci.org/AngeloG/Scratch)

Scratch, a header-only core library. Thread-safe by default. Currently includes the following classes:

* Strings:
  * `String`
  * `Filename`
* Containers:
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

*Note:* At the moment of writing, on Linux, you will be required to link your application against pthreads.

## Options
There are a few specific precompiler definitions you can use during implementation compilation (SCRATCH_IMPL) that modify the behavior of the library.

* `SCRATCH_NO_THREADSAFE`: Don't enable mutex locking in classes.
* `SCRATCH_NO_EXCEPTIONS`: Don't throw any exceptions, silently fail instead.
* `SCRATCH_NO_ASSERT`: Don't define a custom ASSERT().

## License
Scratch is licensed under the permissive MIT license.
