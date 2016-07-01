#pragma once
#include <chrono>

template <typename Clock>
struct chrono_ival {
  // types
  using type = chrono_ival<typename Clock>;
  using clock_t = typename Clock;

  using timepoint_t = typename Clock::time_point;
  using duration_t = typename Clock::duration;

  // data
  timepoint_t begin, end;

  // ctor & dtor
  chrono_ival() : begin(), end() {}
  chrono_ival(timepoint_t b, timepoint_t e) : begin(b), end(e) {}
  virtual ~chrono_ival() = default;

  // members
  inline duration_t duration() { return end - begin; };

  // static
  static const timepoint_t timepoint_zero;
  static const duration_t duration_zero;
};

// the base type for an event
struct Event : public chrono_ival<std::chrono::steady_clock> {
  // chrono types
  using event_ival = type;
  using event_clock = type::clock_t;
  using event_duration = event_clock::duration;
  using event_timepoint = event_clock::time_point;
  using seconds_f32 = std::chrono::duration<float, std::ratio<60, 1>>;
  using minutes_f32 = std::chrono::duration<float, std::ratio<60, 1>>;
  using hours_f64 = std::chrono::duration<float, std::ratio<3600, 1>>;

  //Event(event_timepoint b, event_timepoint e) : chrono_ival(b,e) {}
  Event(const event_ival& i) : chrono_ival(i) {}

  void reset_ival(event_timepoint b, event_timepoint e) {
    chrono_ival(b,e);
  }
};

