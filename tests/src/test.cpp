#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <CoreFoundation/CoreFoundation.h>
#include <pqrs/gcd.hpp>
#include <thread>

TEST_CASE("running_on_main_queue") {
  REQUIRE(pqrs::gcd::running_on_main_queue());

  {
    std::thread t([] {
      REQUIRE(!pqrs::gcd::running_on_main_queue());
    });
    t.join();
  }
}

TEST_CASE("dispatch_sync_on_main_queue") {
  auto thread_id = std::this_thread::get_id();
  std::thread t([&] {
    pqrs::gcd::dispatch_sync_on_main_queue(
        ^{
          REQUIRE(std::this_thread::get_id() == thread_id);

          CFRunLoopStop(CFRunLoopGetMain());
        });
  });

  CFRunLoopRun();

  t.join();
}
