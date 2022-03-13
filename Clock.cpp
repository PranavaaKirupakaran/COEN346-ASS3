#include "Clock.h"
#include <thread>
#include <chrono>

Clock::Clock(){
    time = 0;
    startFlag = true;
}

Clock::Clock(int startValue, bool flag){
    time = startValue;
    startFlag = flag;
}

Clock::~Clock(){

}

void Clock::setTime(int value){
    time = value;
}

int Clock::getTime(){
    return time;
}

void Clock::setStartFlag(bool flag){
    startFlag = flag;
}

bool Clock::getStartFlag(){
    return startFlag;
}

void Clock::startClock(){
    while(startFlag){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        time += 1;
        std::cout << time << std::endl;
    }
}

