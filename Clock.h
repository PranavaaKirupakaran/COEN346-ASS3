#pragma once

//
//  Clock.hpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-13.
//

#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <mutex>

class Clock {
private:
    int time;
    bool startFlag;
    //std::mutex m;

public:
    Clock();
    Clock(int startValue, bool flag);
    ~Clock();
    void setTime(int value);
    int getTime();
    void setStartFlag(bool flag);
    bool getStartFlag();
    void startClock();


};

#endif
