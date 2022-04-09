//
//  Clock.cpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-13.
//

#include "Clock.h"
#include <thread>
#include <chrono>

Clock::Clock() {
    time = 0;
    startFlag = true;
}

Clock::Clock(int startValue, bool flag) {
    time = startValue;
    startFlag = flag;
}

Clock::~Clock() {

}

//Set start value for clock
void Clock::setTime(int value) {
    time = value;
}

//Get current simulated clock time
int Clock::getTime() {
    return time;
}

void Clock::setStartFlag(bool flag) {
    startFlag = flag;
}

bool Clock::getStartFlag() {
    return startFlag;
}

//Start the simulated clock time
void Clock::startClock() {
    std::cout << "Start Clock" << std::endl;
    while (startFlag) {
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        time += 1;
        //std::cout << time << std::endl;
    }
    std::cout << "Stop Clock" << std::endl;
}
