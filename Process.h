//
//  Process.hpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-09.
//

#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string>
#include "Clock.cpp"


class Process{
    private:
        std::string process_id, state;
        int arrival_time, burst_time, priority, waiting_time, cpu_iteration;
        Clock* clk;

    public:
        Process(); 
        Process(std::string id, int arrivalTime, int burstTime, int p);
        ~Process();
        void setProcessID(std::string processID);
        std::string getProcessID();
        void setArrivalTime(int arrivalTime);
        int getArrivalTime();
        void setBurstTime(int burstTime);
        int getBurstTime();
        void setPriority(int p);
        int getPriority();
        void setWaitingTime(int waitingTime);
        int getWaitingTime();
        void setCpuIteration(int iteration);
        int getCpuIteration();
        void setState(std::string status);
        std::string getState();
        void setClock(Clock* timer);
        Clock* getClock();
        void execute();

};

#endif
