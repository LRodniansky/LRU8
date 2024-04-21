# LRU8

LRU8 is a lightweight and efficient implementation of a "Least Recently Used" (LRU) cache designed for 64-bit machines. It provides a fast and simple way to manage up to 8 elements in memory, optimizing performance by efficiently handling data access patterns.

## Features

- **Efficient Cache Management**: LRU8 efficiently manages up to 8 elements in memory, utilizing a "Least Recently Used" eviction policy to optimize data access.
  
- **Fast Access**: Designed for speed, LRU8 provides fast access to cached elements, minimizing latency and improving application performance.

- **Cross-Platform Compatibility**: LRU8 is designed to be compatible with both Unix and Windows systems, making it versatile for a wide range of applications.

## Usage

To use LRU8 in your project, simply include the `lru8.h` header file and instantiate an `LRU8` object with the desired key and value types. Here's a basic example:

```cpp
#include "lru8.h"

int main() {
    // Instantiate LRU8 with uint64_t keys and char values
    LRDN::LRU8<uint64_t, char> cache;

    // Access and manipulate cache elements
    cache[1] = 'A';
    char value = cache[1];

    // Check if an element exists in the cache
    if (cache.exists(2)) {
        // Do something
    }

    return 0;
}
```
## Test Program

The `test_lru8.cpp` file contains the code for a test program that demonstrates how to use LRU8. To build the test program, follow these steps:

```bash
mkdir build
cd build
cmake ..
make
```
After building, you can run the test program by executing the generated executable test_lru8.
When you run the test program, you should see output similar to the following:

```bash
> ./test_lru8 
_data[1] does not exist.
_data[1] exists.
_data[1]=C,_data[5]=5, _data[10]=A, data[11]=B
_strings["one"]=2
```

## Compatibility

LRU8 is compatible with both Unix and Windows systems. It utilizes standard C++ features and should work with any compliant C++ compiler.

LRU8 has been tested and verified to work on the following platforms:

- Red Hat Enterprise Linux 7 (el7.x86_64)
- Red Hat Enterprise Linux 9 (el9.x86_64)
- CentOS 7 (el7.x86_64)


## Contributing
Contributions to LRU8 are welcome! If you find a bug or have an enhancement idea, feel free to open an issue or submit a pull request on GitHub.

## License
LRU8 is licensed under the MIT License. See the LICENSE file for details.
