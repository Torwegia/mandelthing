#include "timer.h"

Timer::Timer()
{
    m_running = false;
}

void Timer::start()
{
    if(!m_running)
    {
        m_running = true;
        gettimeofday(&m_start, 0);
    }
}

float Timer::stop()
{
    m_running = false;
    gettimeofday(&m_stop, 0);
    elapsed = m_stop.tv_sec - m_start.tv_sec;
    if(m_stop.tv_usec > m_start.tv_usec)
        elapsed += (m_stop.tv_usec - m_start.tv_usec) / 1000000.0;
    else
        elapsed += ((m_stop.tv_usec - m_start.tv_usec) / 1000000.0) + 1;
    return elapsed;
}
