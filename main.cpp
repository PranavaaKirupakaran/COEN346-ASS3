//
//  main.cpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-09.
//

#include "Scheduler.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <thread>
#include <vector>

using namespace std;

void startUp();
void sleepScheduler(int timeSlice);
void sort();
int minIndex(int sortedIndex);
void insertMinToRear(int min_index);

int process_count;
queue<Process*>* processList = new queue<Process*>();
Clock* timer = new Clock();
Scheduler* sched = new Scheduler();

int main() {

    startUp();
    sort();

    mutex* arrival = new mutex();
    mutex* print = new mutex();

    sched->setClock(timer);
    sched->setArrivalMutex(arrival);
    sched->setPrintMutex(print);
    thread th2(&Clock::startClock, timer);
    thread th(&Scheduler::schedule, sched); 
    while (processList->size() != 0) {
        arrival->lock();
        if (processList->front()->getArrivalTime() == timer->getTime()) {
            processList->front()->setClock(timer);
            processList->front()->setPrintMutex(print);
            sched->addProcess(processList->front());
            processList->pop();
        }
        arrival->unlock();

    }

    sched->setTerminated(true);
    th.join();
    th2.join();


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
                    Process* tempProcess = new Process(p_id, arrival, burst, priority);
                    processList->push(tempProcess);
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
