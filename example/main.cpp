#include <iostream>
#include <pqrs/gcd.hpp>

int main() {
  pqrs::gcd::dispatch_sync_on_main_queue(^{
    std::cout << "Hello from the main queue." << std::endl;
  });

  return 0;
}
