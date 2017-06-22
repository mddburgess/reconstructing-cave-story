#include "timer.h"

// static
std::set<Timer*> Timer::timers_;

// static
void Timer::updateAll(units::MS elapsed_time) {
    for (Timer* timer : timers_) {
        timer->update(elapsed_time);
    }
}
