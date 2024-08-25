#pragma once
#include <functional>

#define COROUTINE_BEGIN                                                        \
  switch (_status) {                                                           \
  case 0:;
#define WRITE_CHAN(expr)                                                    \
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
#define GO(expr)                                                         \
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