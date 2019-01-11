#pragma once

// pqrs::gcd v0.0

// (C) Copyright Takayama Fumihiko 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See http://www.boost.org/LICENSE_1_0.txt)

#include <cstring>
#include <dispatch/dispatch.h>

namespace pqrs {
namespace gcd {
inline bool running_on_main_queue(void) {
  auto main_queue_label = dispatch_queue_get_label(dispatch_get_main_queue());
  auto current_queue_label = dispatch_queue_get_label(DISPATCH_CURRENT_QUEUE_LABEL);

  return strcmp(main_queue_label, current_queue_label) == 0;
}
} // namespace gcd
} // namespace pqrs
