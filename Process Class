//
//  Process.cpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-09.
//

#include "Process.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;

class Process{
private:
    string process_id;
    int arrival_time,burst_time, priority;
    
public:
    Process(string name, int arrive, int burst, int pri)
    {
        process_id = name;
        arrival_time = arrive;
        burst_time = burst;
        priority = pri;
    }
    
    void processID(string name)
    {
        process_id = name;
    }
    
    void addArrivalTime(int wait)
    {
        arrival_time = wait;
    }
    
    void addBurstTime(int burst)
    {
        burst_time = burst;
    }
    
    void addPriority(int time)
    {
        priority = time;
    }
    
    int getArrivalTime(int wait)
    {
        return arrival_time;
    }
    
    int getBurstTime(int burst)
    {
        return burst_time;
    }
    
    int getPriority(int time)
    {
        return priority;
    }
    
    
};
