// Token bucket rate limiter.
//
// Every user gets a "bucket" that holds at most `capacity` tokens.
//   - Tokens drip into the bucket at a steady rate (`refillPerSec`).
//   - Each request takes one token out of the bucket.
//   - If the bucket has less than one token, the request is rejected.
//
// The two settings control different things:
//   - capacity     = biggest burst allowed (an idle user can send this many at once)
//   - refillPerSec = long-run average rate (after the burst, one request every
//                    1 / refillPerSec seconds)
//
// There is no background timer adding tokens. Instead we store how many tokens
// the bucket had at the last request and when that was, and when the next
// request arrives we calculate how many tokens have dripped in since then
// ("lazy refill"). Nobody looks at the bucket between requests, so computing
// the count only when it's needed gives the same answer a timer would.

#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

class TokenBucketRateLimiter {
public:
  TokenBucketRateLimiter(double capacity, double refillPerSec)
      // timestamps are in milliseconds, so convert the rate to tokens per ms
      : capacity(capacity), refillPerMs(refillPerSec / 1000.0) {}

  // Returns true if this request is allowed, false if it should be rejected.
  // The current time is passed in (instead of reading the clock here) so the
  // limiter is easy to test with exact timestamps.
  bool allow(const std::string &userId, long long nowMs) {
    // Step 1: a user we've never seen starts with a full bucket, so their
    // first `capacity` requests go through immediately.
    if (buckets.find(userId) == buckets.end()) {
      buckets[userId] = Bucket{capacity, nowMs};
    }
    Bucket &bucket = buckets[userId];

    // Step 2: add the tokens that dripped in since this user's last request.
    refill(bucket, nowMs);

    // Step 3: not even one whole token available -> reject.
    // Any partial token (e.g. 0.998) stays in the bucket and keeps growing.
    if (bucket.tokens < 1) {
      return false;
    }

    // Step 4: spend one token on this request and allow it.
    bucket.tokens -= 1;
    return true;
  }

private:
  struct Bucket {
    double tokens;          // tokens available as of lastRefillMs (can be fractional)
    long long lastRefillMs; // last time we brought `tokens` up to date
  };

  // Bring the bucket up to date: tokens now = tokens then + time passed * rate,
  // but never more than capacity.
  void refill(Bucket &bucket, long long nowMs) {
    long long elapsedMs = nowMs - bucket.lastRefillMs;

    // The cap stops an idle user from saving up an unlimited burst.
    // Nothing removes tokens between requests, so adding everything at once
    // and capping gives the same result as a timer adding tokens bit by bit
    // and stopping when the bucket is full.
    bucket.tokens =
        std::min(capacity, bucket.tokens + elapsedMs * refillPerMs);

    // The time up to now has been turned into tokens, so move the clock
    // forward. Otherwise the next refill would count the same time again.
    bucket.lastRefillMs = nowMs;
  }

  double capacity;                                 // max tokens a bucket can hold (max burst size)
  double refillPerMs;                              // tokens added per millisecond
  std::unordered_map<std::string, Bucket> buckets; // userId -> that user's bucket
};