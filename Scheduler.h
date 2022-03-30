//
//  Scheduler.hpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-13.
//

#ifndef Scheduler_h
#define Scheduler_h

#include <stdio.h>
#include <string>
//#include "Clock.cpp"
#include "ProcessQueue.cpp"
#include <thread>

class Scheduler {

private:
    Clock* clk;
    ProcessQueue q1;
    ProcessQueue q2;
    int timeSlice;
    vector<thread> threadVector;
    bool terminated;
    std::mutex* arrival;
    std::mutex* print;

public:
    Scheduler();
    int calculateTimeSlice(Process* p);
    int calculatePriority(Process* p);
    void swapFlag();
    void addProcess(Process* p);
    void schedule();
    void setClock(Clock* c);
    ProcessQueue* getActiveQueue();
    ProcessQueue* getExpiredQueue();
    void sleepScheduler();
    void setTerminated(bool flag);
    bool getTerminated();
    void joinThreadVector();
    void setArrivalMutex(std::mutex* m);
    std::mutex* getArrivalMutex();
    void setPrintMutex(std::mutex* m);
    std::mutex* getPrintMutex();

};
#endif /* Scheduler_hpp */

