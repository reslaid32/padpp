# padpp
Padding library written in C++

**padpp** is a lightweight, extensible library for working with byte padding in C++ and C. It supports popular padding schemes such as:

- ANSI X.923
- PKCS#7
- ISO 9797-1 Padding Method 1 (M1)
- ISO 9797-1 Padding Method 2 (M2)

---

## Features

- Clean, modern C++20 API
- Use of std::span for input data
- Full-featured C API for integration with C projects
- Modular architecture with a padder factory based on the Open-Closed Principle (`PadderFactory`)
- Examples of use in C and C++
- Easy and fast implementation of padding/anti-padding

---

## Installation

### Building and installing the library

```bash
make
sudo make install
```

## Examples

### C API

```c
#include <padpp-c/PadderFactory.h>

padpp_handle_t padder = padpp_create(“pkcs7”);
uint8_t padded[];
size_t padded_len = sizeof(padded);
size_t block_size = 16;
int res = padpp_pad(padder, padded, &padded_len, input_data, input_len, block_size);

padpp_destroy(padder);
```

### C++ API

```cpp
#include <padpp/PadderFactory.h>

auto padder = padpp::PadderFactory::instance().create(“pkcs7”);
std::vector<uint8_t> padded;
size_t block_size = 16;
padder->pad(padded, input_data, block_size);
```