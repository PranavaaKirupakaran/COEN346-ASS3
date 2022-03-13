#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H

#include <iostream>
#include <stdio.h>
#include <queue>
#include "Process.cpp"

using namespace std;

class ProcessQueue{

    private:
        queue<Process> plist;
        bool flag;

    public:
        ProcessQueue(bool active);
        void addProcess(Process p);
        Process removeProcess();
        void updateFlag();
        int minIndex(int sortedIndex);
        void insertMinToRear(int min_index);
        void sort();
        void printQueue();
        

};

#endif
