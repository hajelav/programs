/*
  Sliding-window rate limiter

  The limiter allows at most maxRequests for each user in any window of
  windowMs milliseconds. It keeps a deque of accepted request timestamps for
  each user, ordered from oldest to newest.

  On each request:
  1. Find that user's timestamp deque.
  2. Remove timestamps at or before nowMs - windowMs; those requests are no
     longer inside the current window (nowMs - windowMs, nowMs].
  3. If maxRequests timestamps remain, reject the request.
  4. Otherwise, record nowMs and allow the request.

  This is an exact sliding window: unlike fixed time buckets, it does not
  allow extra bursts at bucket boundaries. Each timestamp is added once and
  removed once, though the limiter must store recent timestamps per user.
  The caller supplies nowMs, which also makes boundary behavior easy to test.
*/

#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
class SlidingWindowRateLimiter {
public:
  SlidingWindowRateLimiter(int maxRequests, long long windowMs)
      : maxRequests(maxRequests), windowMs(windowMs) {}

  bool allow(const string &userId, long long nowMs) {
    std::deque<long long> &log = requests[userId];
    // drop requests that have fallen out of the window (nowMs - windowMs, nowMs]
    while (!log.empty() && log.front() <= nowMs - windowMs)
      log.pop_front();
    if ((int)log.size() >= maxRequests)
      return false;
    log.push_back(nowMs);
    return true;
  }

private:
  int maxRequests;
  long long windowMs;
  std::unordered_map<string, std::deque<long long>> requests;
  // userId -> request times
};

static void check(const char *name, bool expected, bool actual, int &failures) {
  const bool passed = expected == actual;
  std::cout << (passed ? "PASS: " : "FAIL: ") << name
            << " (expected " << (expected ? "allow" : "reject")
            << ", got " << (actual ? "allow" : "reject") << ")\n";
  if (!passed) {
    ++failures;
  }
}

int main() {
  int failures = 0;
  SlidingWindowRateLimiter limiter(2, 1000);

  check("first request for user A", true, limiter.allow("A", 0), failures);
  check("second request for user A", true, limiter.allow("A", 500), failures);
  check("reject user A at limit", false, limiter.allow("A", 999), failures);

  // The request at t=0 is exactly 1000ms old, so it leaves the window.
  check("allow user A when oldest request expires",
        true, limiter.allow("A", 1000), failures);
  check("reject user A while two recent requests remain",
        false, limiter.allow("A", 1001), failures);

  // Each user's request timestamps are tracked independently.
  check("user B has an independent limit",
        true, limiter.allow("B", 1001), failures);
  check("user B can use its second request",
        true, limiter.allow("B", 1002), failures);
  check("reject user B after reaching its limit",
        false, limiter.allow("B", 1003), failures);

  std::cout << (failures == 0 ? "All tests passed.\n" : "Some tests failed.\n");
  return failures == 0 ? 0 : 1;
}