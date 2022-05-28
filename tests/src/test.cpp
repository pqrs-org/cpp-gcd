#include <CoreFoundation/CoreFoundation.h>
#include <boost/ut.hpp>
#include <pqrs/gcd.hpp>
#include <thread>

int main(void) {
  using namespace boost::ut;
  using namespace boost::ut::literals;

  "running_on_main_queue"_test = [] {
    expect(pqrs::gcd::running_on_main_queue());

    {
      std::thread t([] {
        expect(!pqrs::gcd::running_on_main_queue());
      });
      t.join();
    }

    {
      dispatch_async(dispatch_get_main_queue(), ^{
        {
          std::thread t([] {
            expect(!pqrs::gcd::running_on_main_queue());
          });
          t.join();
        }

        {
          auto marker = pqrs::gcd::scoped_running_on_main_queue_marker();

          std::thread t([] {
            expect(pqrs::gcd::running_on_main_queue());
          });
          t.join();
        }

        {
          std::thread t([] {
            expect(!pqrs::gcd::running_on_main_queue());
          });
          t.join();
        }

        CFRunLoopStop(CFRunLoopGetMain());
      });

      CFRunLoopRun();
    }
  };

  "dispatch_sync_on_main_queue"_test = [] {
    auto thread_id = std::this_thread::get_id();
    std::thread t([&] {
      pqrs::gcd::dispatch_sync_on_main_queue(
          ^{
            expect(std::this_thread::get_id() == thread_id);

            CFRunLoopStop(CFRunLoopGetMain());
          });
    });

    CFRunLoopRun();

    t.join();
  };

  return 0;
}
