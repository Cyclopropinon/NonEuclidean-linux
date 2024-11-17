#pragma once
#include <ctime>

class Timer {
public:
  Timer() {
    // Using CLOCK_MONOTONIC for high-resolution and monotonic time
    clock_getres(CLOCK_MONOTONIC, &frequency);
  }

  void Start() {
    clock_gettime(CLOCK_MONOTONIC, &t1);
  }

  float Stop() {
    clock_gettime(CLOCK_MONOTONIC, &t2);
    return float((t2.tv_sec - t1.tv_sec) * 1e9 + (t2.tv_nsec - t1.tv_nsec)) / 1e9;
  }

  int64_t GetTicks() {
    clock_gettime(CLOCK_MONOTONIC, &t2);
    return (t2.tv_sec * 1e9 + t2.tv_nsec);
  }

  int64_t SecondsToTicks(float s) {
    return int64_t(s * 1e9); // Convert seconds to nanoseconds
  }

  float StopStart() {
    const float result = Stop();
    t1 = t2;
    return result;
  }

private:
  struct timespec frequency; // Resolution of the clock
  struct timespec t1, t2;    // Start and stop times
};
