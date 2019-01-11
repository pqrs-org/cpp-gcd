#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <pqrs/gcd.hpp>
#include <thread>

TEST_CASE("main_queue") {
  REQUIRE(pqrs::gcd::running_on_main_queue());

  {
    std::thread t([] {
      REQUIRE(!pqrs::gcd::running_on_main_queue());
    });
    t.join();
  }
}
