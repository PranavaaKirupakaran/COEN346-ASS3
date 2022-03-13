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

using namespace std;

Process::Process(){
    process_id, state = "";
    arrival_time, burst_time, priority, waiting_time, cpu_iteration = 0;
}

Process::Process(std::string id, int arrivalTime, int burstTime, int p){
    process_id = id;
    state = "";
    arrival_time = arrivalTime;
    burst_time = burstTime;
    priority = p;
    waiting_time, cpu_iteration = 0;
}

Process::~Process(){
    
}

void Process::setProcessID(std::string processID){
    process_id = processID;
}

std::string Process::getProcessID(){
    return process_id;
}

void Process::setArrivalTime(int arrivalTime){
    arrival_time = arrivalTime;
}

int Process::getArrivalTime(){
    return arrival_time;
}

void Process::setBurstTime(int burstTime){
    burst_time = burstTime;
}

int Process::getBurstTime(){
    return burst_time;
}

void Process::setPriority(int p){
    priority = p;
}

int Process::getPriority(){
    return priority;
}

void Process::setWaitingTime(int waitingTime){
    waiting_time = waitingTime;
}

int Process::getWaitingTime(){
    return waiting_time;
}

void Process::setCpuIteration(int iteration){
    cpu_iteration = iteration;
}

int Process::getCpuIteration(){
    return cpu_iteration;
}

void Process::setState(string status){
    state = status;
}

string Process::getState(){
    return state;
}

void Process::setClock(Clock* timer){
    clk = timer;
}

Clock* Process::getClock(){
    return clk;
}

void Process::execute(){
    int startTimeSlice, endTimeSlice, deltaTimeSlice = 0;
    string prevState = "";
    while(true){
        if(state == "ARRIVED"){

            cout << "TIME " << arrival_time << ", " << process_id << " " << state << endl;

        }
        else if(state == "STARTED"){
            if(prevState != state){
                startTimeSlice = clk->getTime();
                cpu_iteration += 1;
                waiting_time += arrival_time - startTimeSlice;
                prevState = state;
            }
        }
        else if(state == "PAUSED"){
            if(prevState != state){
                endTimeSlice = clk->getTime();
                deltaTimeSlice = endTimeSlice - startTimeSlice;
                burst_time -= deltaTimeSlice;
                if(burst_time <= 0){
                    state = "TERMINATED";
                }
                else{
                    cout << "TIME " << startTimeSlice << ", " << process_id << " " << prevState << ", GRANTED " << deltaTimeSlice << endl;
                    cout << "TIME " << endTimeSlice << ", " << process_id << " " << state << endl;
                    prevState = state;
                }

            }

        }
        else if(state == "RESUMED"){
            if(prevState != state){
                startTimeSlice = clk->getTime();
                cpu_iteration += 1;
                waiting_time += startTimeSlice - endTimeSlice;
                prevState = state;
            }
        }
        
        if(state == "TERMINATED"){
            cout << "TIME " << startTimeSlice << ", " << process_id << " " << prevState << ", GRANTED " << deltaTimeSlice << endl;
            cout << "TIME " << endTimeSlice << ", " << process_id << " " << state << endl;
            break;
        }
    }
}

