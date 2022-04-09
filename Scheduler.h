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
#include "ProcessQueue.h"
#include "Command.h"
#include <vector>
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
    int core;
    vector<Command*>* commandList;
    vector<bool> isExecuting;

public:
    Scheduler();
    Scheduler(int noCores);
    int calculateTimeSlice(Process* p);
    int calculatePriority(Process* p, int timeNow);
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
    void setCore(int noCore);
    int getCore();
    void setCommandList(vector<Command*>* commandListPtr);

};
#endif /* Scheduler_hpp */

