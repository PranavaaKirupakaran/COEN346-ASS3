#pragma once
//
//  ProcessQueue.hpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-12.
//

#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H

#include <iostream>
#include <stdio.h>
#include <queue>
#include "Process.cpp"

using namespace std;

class ProcessQueue {

private:
    queue<Process*> plist;
    bool flag;

public:
    ProcessQueue();
    ProcessQueue(bool active);
    ~ProcessQueue();
    void addProcess(Process* p);
    Process* removeProcess();
    void updateFlag();
    bool getFlag();
    int minIndex(int sortedIndex);
    void insertMinToRear(int min_index);
    void sort();
    void printQueue();
    bool checkEmpty();



};

#endif

