//
//  main.cpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-09.
//

//#include "Process.cpp"
//#include "ProcessQueue.cpp"
//#include "Clock.hpp"
#include "Scheduler.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
//#include <queue>
#include <thread>
#include <vector>

using namespace std;

void startUp();
void sleepScheduler(int timeSlice);

int clck;
int process_count;
ProcessQueue q1(true);
ProcessQueue q2(false);
queue<Process*>* processList = new queue<Process*>();
vector<thread> threadList;
Clock* timer = new Clock();
Scheduler* sched = new Scheduler();
void sort();
int minIndex(int sortedIndex);
void insertMinToRear(int min_index);

int main() {

    startUp();
    sort();

    mutex* mutexPtr = new mutex();

    //cout << processList->size() << endl;
    sched->setClock(timer);
    sched->setMutex(mutexPtr);
    thread th2(&Clock::startClock, timer);
    thread th(&Scheduler::schedule, sched); 
    int aTime = 0;
    while (processList->size() != 0) {
        //cout << "enter loop" << endl;
        mutexPtr->lock();
        if (processList->front()->getArrivalTime() == timer->getTime()) {
            //cout << "adding process" << endl;
            processList->front()->setClock(timer);
            sched->addProcess(processList->front());
            processList->pop();
        }
        mutexPtr->unlock();

    }

    sched->setTerminated(true);
    //timer->setStartFlag(false);
    th.join();
    th2.join();

    /*
    processList.front()->setClock(timer);
    thread th2(&Clock::startClock, timer);
    sleepScheduler(100);
    processList.front()->setState("STARTED");
    thread th(&Process::execute,processList.front());
    sleepScheduler(100);
    processList.front()->setState("PAUSED");
    sleepScheduler(100);
    processList.front()->setState("RESUMED");
    sleepScheduler(150);
    processList.front()->setState("PAUSED");
    timer->setStartFlag(false);
    th.join();
    th2.join();
    */


}

void sleepScheduler(int timeSlice) {
    int startclk = timer->getTime();
    while ((startclk + timeSlice) != timer->getTime()) {

    }
}

void startUp()
{
    fstream myFile;
    string startup = "input.txt";
    myFile.open(startup.c_str(), ios::in);

    if (!myFile) {
        cout << "Input File does not exist" << endl;
    }
    else {
        string line;
        while (true) {
            for (int i = 0; std::getline(myFile, line); i++) {
                if (i == 0) {
                    process_count = stoi(line);
                    line = "";
                }

                else {
                    string p_id = line.substr(0, line.find_first_of(" "));
                    line = line.substr(line.find_first_of(" ") + 1);
                    int arrival = stoi(line.substr(0, line.find_first_of(" ")));
                    line = line.substr(line.find_first_of(" ") + 1);
                    int burst = stoi(line.substr(0, line.find_first_of(" ")));
                    line = line.substr(line.find_first_of(" ") + 1);
                    int priority = stoi(line.substr(0, line.find_first_of("\n")));
                    //cout<< arrival<<" "<<burst<<" "<<priority<<endl;
                    Process* tempProcess = new Process(p_id, arrival, burst, priority);
                    processList->push(tempProcess);
                    q2.addProcess(tempProcess);
                    line = "";
                }
            }

            if (myFile.eof())
                break;
        }
    }
}


int minIndex(int sortedIndex)
{
    int min_index = -1;
    int min_val = INT_MAX;
    int n = processList->size();
    for (int i = 0; i < n; i++)
    {
        Process* curr = processList->front();
        processList->pop();  // This is dequeue() in C++ STL

        // we add the condition i <= sortedIndex
        // because we don't want to traverse
        // on the sorted part of the queue,
        // which is the right part.
        if (curr->getArrivalTime() <= min_val && i <= sortedIndex)
        {
            min_index = i;
            min_val = curr->getArrivalTime();
        }
        processList->push(curr);  // This is enqueue() in
                       // C++ STL
    }
    return min_index;
}

// Moves given minimum element to rear of
// queue
void insertMinToRear(int min_index)
{
    Process* min_val;
    int n = processList->size();
    for (int i = 0; i < n; i++)
    {
        Process* curr = processList->front();
        processList->pop();
        if (i != min_index)
            processList->push(curr);
        else
            min_val = curr;
    }
    processList->push(min_val);
}

void sort()
{
    for (int i = 1; i <= processList->size(); i++)
    {
        int min_index = minIndex(processList->size() - i);
        insertMinToRear(min_index);
    }
}
