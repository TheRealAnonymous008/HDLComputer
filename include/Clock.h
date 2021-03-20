#ifndef CLOCK_H
#define CLOCK_H

#include<chrono>

class Clock
{
    public:
        Clock();
        int getSignal();

    private:
        int signal = 0;
        int peakLength = 10;

        void updateClock();

};

#endif // CLOCK_H
