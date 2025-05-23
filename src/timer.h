#ifndef TIMER_H
#define TIMER_H

#include <QObject>

class Timer {
public:
    Timer();
    
    void start();
    void stop();
    void reset();
    
    int getTime() const;
    bool isRunning() const;

private:
    int m_time;
    bool m_running;
};

#endif // TIMER_H