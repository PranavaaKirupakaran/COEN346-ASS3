#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H

#include <iostream>
#include <stdio.h>
#include <queue>
#include <thread>

using namespace std;

class ProcessQueue{

    private:
        queue<thread> TH;
        bool flag;

    public:
        ProcessQueue(bool active);
        void addProcess(thread th);
        thread removeProcess();
        void updateFlag();
        

};

#endif
