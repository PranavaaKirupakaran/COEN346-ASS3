#pragma once
//
//  Process.cpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-09.
//

#include "Process.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

Process::Process() {
    process_id = "";
    state = "";
    arrival_time = 0;
    burst_time = 0;
    priority = 0;
    waiting_time = 0;
    cpu_iteration = 0;
}

Process::Process(std::string id, int arrivalTime, int burstTime, int p) {
    process_id = id;
    state = "";
    arrival_time = arrivalTime;
    burst_time = burstTime;
    priority = p;
    waiting_time = 0;
    cpu_iteration = 0;
}

Process::~Process() {

}

void Process::setProcessID(std::string processID) {
    process_id = processID;
}

std::string Process::getProcessID() {
    return process_id;
}

void Process::setArrivalTime(int arrivalTime) {
    arrival_time = arrivalTime;
}

int Process::getArrivalTime() {
    return arrival_time;
}

void Process::setBurstTime(int burstTime) {
    burst_time = burstTime;
}

int Process::getBurstTime() {
    return burst_time;
}

void Process::setPriority(int p) {
    priority = p;
}

int Process::getPriority() {
    return priority;
}

void Process::setWaitingTime(int waitingTime) {
    waiting_time = waitingTime;
}

int Process::getWaitingTime() {
    return waiting_time;
}

void Process::setCpuIteration(int iteration) {
    cpu_iteration = iteration;
}

int Process::getCpuIteration() {
    return cpu_iteration;
}

void Process::setState(string status) {
    if (state != "TERMINATED") {
        state = status;
    }
}

string Process::getState() {
    string temp = state;
    return temp;

}

void Process::setClock(Clock* timer) {
    clk = timer;
}

Clock* Process::getClock() {
    return clk;
}

void Process::execute() {
    int startTimeSlice = 0, endTimeSlice = 0;
    string prevState = "";
    while (true) {
        //Check the current state of the process
        if (state == "STARTED") {
            startTimeSlice = clk->getTime();
            //Update cpu_iteration to show process is not new and has begun execution
            cpu_iteration += 1;
            waiting_time += arrival_time - startTimeSlice;
            
            int timeNow = clk->getTime();
            while (state == "STARTED") {
                //Decrement process burst time if simulated clock time has incremented by 1
                if (clk->getTime() == timeNow + 1) {
                    burst_time--;
                    timeNow = clk->getTime();
                    if (burst_time == 0) {
                        print->lock();
                        state = "TERMINATED";
                    }
                }
            }
        }
        
        if (state == "PAUSED") {
            endTimeSlice = clk->getTime();
            //Stay in Paused state till state changed by scheduler
            while (state == "PAUSED") {

            }
        }
        
        if (state == "RESUMED") {
            startTimeSlice = clk->getTime();
            waiting_time += startTimeSlice - endTimeSlice;
            cpu_iteration++;
            
            int timeNow = clk->getTime();
            while (state == "RESUMED") {
                //Decrement process burst time if 1s has passed in simulated time
                if (clk->getTime() == timeNow + 1) {
                    burst_time--;
                    timeNow = clk->getTime();
                    if (burst_time == 0) {
                        print->lock();
                        state = "TERMINATED";
                    }
                }
            }
        }

        if (state == "TERMINATED") {
            fstream out;
            out.open("output.txt", std::ios_base::app);
            out << "TIME " << clk->getTime() << ", " << process_id << " " << state << endl;
            print->unlock();
            break;
        }
    }
}

//Set time when process has been termintated
void Process::setTerminateTime(int t) {
    terminateTime = t;
}

int Process::getTerminateTime() {
    return terminateTime;
}

void Process::setPrintMutex(mutex* m) {
    print = m;
}

mutex* Process::getPrintMutex() {
    return print;
}
