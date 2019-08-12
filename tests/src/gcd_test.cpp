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

  {
    dispatch_async(dispatch_get_main_queue(), ^{
      {
        std::thread t([] {
          REQUIRE(!pqrs::gcd::running_on_main_queue());
        });
        t.join();
      }

      {
        auto marker = pqrs::gcd::scoped_running_on_main_queue_marker();

        std::thread t([] {
          REQUIRE(pqrs::gcd::running_on_main_queue());
        });
        t.join();
      }

      {
        std::thread t([] {
          REQUIRE(!pqrs::gcd::running_on_main_queue());
        });
        t.join();
      }

      CFRunLoopStop(CFRunLoopGetMain());
    });

    CFRunLoopRun();
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
