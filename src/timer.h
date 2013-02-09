#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

class Timer
{
    public:
        Timer();
        void start();
        float stop();

        float elapsed;
    private:
        timeval m_start, m_stop;
        bool m_running;
};

#endif
