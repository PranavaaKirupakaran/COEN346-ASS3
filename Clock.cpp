//
//  Clock.cpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-13.
//

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
    //m.lock();
    time = value;
    //m.unlock();
}

int Clock::getTime(){
    //m.lock();
    int temp = time;
    //m.unlock();
    return temp;
}

void Clock::setStartFlag(bool flag){
    startFlag = flag;
}

bool Clock::getStartFlag(){
    return startFlag;
}

void Clock::startClock(){
    std::cout << "Start Clock" << std::endl;
    while(startFlag){
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //m.lock();
        time += 1;
        //std::cout << time << std::endl;
        //m.unlock();
    }
    std::cout << "Stop Clock" << std::endl;
}

