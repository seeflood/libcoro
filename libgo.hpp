#pragma once
#include <atomic>
#include <functional>

namespace libgo {

#define COROUTINE_BEGIN                                                        \
  switch (_status) {                                                           \
  case 0:;
#define WRITE_CHAN(expr)                                                       \
  do {                                                                         \
    _status = __LINE__;                                                        \
    return expr;                                                               \
  case __LINE__:;                                                              \
  } while (0)
#define COROUTINE_END                                                          \
  _status = -1;                                                                \
  return {};                                                                   \
  default:;                                                                    \
    return {};                                                                 \
    }
#define GO(expr)                                                               \
  operator()() {                                                               \
    COROUTINE_BEGIN                                                            \
    expr;                                                                      \
    COROUTINE_END                                                              \
  }

class chan {
public:
protected:
  int _status = 0;
};

template <typename T> class atomic_value {
public:
  atomic_value(T value) : _value{} { _value.store(new T(value)); }

  T Load() { return *(_value.load()); }

  void Store(const T &value) {
    T *new_value = new T(value);
    T *old_value = _value.exchange(new_value);
    if (old_value) {
      delete old_value;
    }
  }

  bool CompareAndSwap(const T &old_value, const T &new_value) {
    auto old_ptr = _value.load();
    if (*old_ptr != old_value) {
      return false;
    }
    T *new_value_ptr = new T(new_value);
    if (_value.compare_exchange_strong(old_ptr, new_value_ptr)) {
      delete old_ptr;
      return true;
    }
    delete new_value_ptr;
    return false;
  }

  virtual ~atomic_value() {
    T *value = _value.load();
    if (value) {
      delete value;
    }
  }

private:
  std::atomic<T *> _value;
};
} // namespace libgo