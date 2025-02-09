# libgo
I want to write cpp code in a golang style.

## Usage
### chan + GO
See [example.cpp](example.cpp).

```C++
#include "libgo.hpp"
#include <iostream>
#include <optional>

class GeneratorChan : public chan {
public:
  std::optional<int> GO(
    for (; i < 10; i++) {
      WRITE_CHAN(i);
    }
  )
private:
  int i = 0;
};

int main() {
  GeneratorChan ch;
  auto data = ch();
  while(data.has_value()) {
    std::cout << data.value() << std::endl;
    data = ch();
  }

  return 0;
}
```

This API essentially provides a stackless coroutine.

You can run it:

```shell
g++ -std=c++17 example.cpp -o main && chmod +x main && ./main
```

### atomic_value

See [example_atomic.cpp](example_atomic.cpp)

