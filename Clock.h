#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>

class Clock{
    private:
        int time;
        bool startFlag;

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
