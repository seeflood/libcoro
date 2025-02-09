#include "libgo.hpp"

#include <iostream>
#include <optional>
#include <string>
#include <thread>

using namespace libgo;

struct Config {
  int a;
  long b;
  std::string str;

  bool operator==(const Config &other) const {
    return a == other.a && b == other.b && str == other.str;
  }

  bool operator!=(const Config &other) const { return !(*this == other); }
};
atomic_value<Config> config{{1, 2, "hello"}};

int main() {
  auto cfg = config.Load();

  std::cout << "Before: " << cfg.a << " " << cfg.b << " " << cfg.str
            << std::endl;

  // create a new thread to update the config
  std::thread t([]() { config.Store({3, 4, "world"}); });
  std::thread t2([]() { config.Store({5, 6, "!"}); });
  t.join();
  t2.join();

  cfg = config.Load();
  std::cout << "After: " << cfg.a << " " << cfg.b << " " << cfg.str
            << std::endl;

  // test CompareAndSwap
  Config old_cfg = cfg;
  Config new_cfg{7, 8, "!!"};
  if (config.CompareAndSwap(old_cfg, new_cfg)) {
    std::cout << "CAS success" << std::endl;
    cfg = config.Load();
    std::cout << "After CAS: " << cfg.a << " " << cfg.b << " " << cfg.str
              << std::endl;
  } else {
    std::cout << "CAS failed" << std::endl;
  }
  return 0;
}