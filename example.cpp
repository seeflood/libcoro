#include "libgo.hpp"
#include <iostream>
#include <optional>

using namespace libgo;

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