#include "timer.h"

Timer::Timer() : m_time(0), m_running(false) {}

void Timer::start() {
    if (!m_running) {
        m_running = true;
    }
}

void Timer::stop() {
    if (m_running) {
        m_running = false;
    }
}

void Timer::reset() {
    m_time = 0;
    m_running = false;
}

int Timer::getTime() const {
    return m_time;
}

bool Timer::isRunning() const {
    return m_running;
}