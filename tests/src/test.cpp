#include <CoreFoundation/CoreFoundation.h>
#include <boost/ut.hpp>
#include <pqrs/gcd.hpp>
#include <thread>

int main() {
  using namespace boost::ut;
  using namespace boost::ut::literals;

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

  "dispatch_sync_on_main_queue_on_main_thread"_test = [] {
    auto thread_id = std::this_thread::get_id();

    pqrs::gcd::dispatch_sync_on_main_queue(^{
      expect(std::this_thread::get_id() == thread_id);
    });
  };

  return 0;
}
