#include "Clock.h"
#include <chrono>
#include<thread>

Clock::Clock()
{
    std::thread t1(Clock::updateClock, this);
    t1.detach();
}

int Clock::getSignal(){
    return this->signal;
}

void Clock::updateClock(){
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(this->peakLength));
        this->signal = !this->signal;
    }
}
