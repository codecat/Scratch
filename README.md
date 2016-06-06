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

## License
Scratch is licensed under the permissive MIT license.

## Example usage

```C++
#define SCRATCH_IMPL
#include <Scratch.h>

#include <stdio.h>

int main()
{
  Scratch::String foo = "Hello";
  foo += " world!";
  printf("foo = '%s'\n", (const char*)foo);
  return 0;
}
```
