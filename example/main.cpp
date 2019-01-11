#include <iostream>
#include <pqrs/gcd.hpp>

int main(void) {
  std::cout << "running_on_main_queue: " << pqrs::gcd::running_on_main_queue() << std::endl;

  return 0;
}
