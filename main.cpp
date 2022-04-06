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
void sort();
int minIndex(int sortedIndex);
void insertMinToRear(int min_index);

int process_count;
int cores;
int noOfPages;
int K;
int timeOut;
queue<Process*>* processList = new queue<Process*>(); //Queue of pointers to processes taken from input.txt
Clock* timer = new Clock();
Scheduler* sched = new Scheduler();

int main() {

    startUp();
    sort(); //Sort the queue of process pointers by arrival time

    mutex* arrival = new mutex();
    mutex* print = new mutex();

    sched->setClock(timer); //Pass clock pointer to the scheduler
    
    sched->setArrivalMutex(arrival);
    sched->setPrintMutex(print);
    
    thread th2(&Clock::startClock, timer);
    thread th(&Scheduler::schedule, sched);
    
    while (processList->size() != 0) {
        //Lock thread access for getting arrival time
        arrival->lock();
        if (processList->front()->getArrivalTime() == timer->getTime()) {
            processList->front()->setClock(timer);
            processList->front()->setPrintMutex(print);
            //Add process to the scheduler
            sched->addProcess(processList->front());
            processList->pop();
        }
        arrival->unlock();

    }
    
    //Check if all processes have been scheduled and then join the threads
    sched->setTerminated(true);
    th.join();
    th2.join();


}

//Get process info from input.txt file and store as process pointer in queue
void startUp()
{
    fstream processFile;
    string fileName1 = "processes.txt";
    processFile.open(fileName1.c_str(), ios::in);

    if (!processFile) {
        cout << "Input File does not exist" << endl;
    }
    else {
        string line;
        while (true) {
            for (int i = 0; std::getline(processFile, line); i++) {
                if (i == 0) {
                    cores = stoi(line);
                    line = "";
                }
                else if (i == 1) {
                    process_count = stoi(line);
                    line = "";
                }
                else {
                    string p_id = "P" + to_string(i-1);
                    int arrival = stoi(line.substr(0, line.find_first_of(" ")));
                    line = line.substr(line.find_first_of(" ") + 1);
                    int burst = stoi(line.substr(0, line.find_first_of(" ")));
                    //Make a pointer fort he newly created process
                    Process* tempProcess = new Process(p_id, arrival, burst, 100);
                    //Store the pointer into the queue of process pointers
                    processList->push(tempProcess);
                    line = "";
                }
            }

            if (processFile.eof())
                break;
        }
    }

    fstream memconfigFile;
    string fileName2 = "memconfig.txt";
    memconfigFile.open(fileName2.c_str(), ios::in);

    if (!memconfigFile) {
        cout << "Input File does not exist" << endl;
    }
    else {
        string line;
        while (true) {
            for (int i = 0; std::getline(memconfigFile, line); i++) {
                if (i == 0) {
                    noOfPages = stoi(line);
                    line = "";
                }
                else if (i == 1) {
                    K = stoi(line);
                    line = "";
                }
                else if (i == 2) {
                    timeOut = stoi(line);
                    line = "";
                }
            }

            if (processFile.eof())
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

//Function to sort queue by arrival time
void sort()
{
    for (int i = 1; i <= processList->size(); i++)
    {
        int min_index = minIndex(processList->size() - i);
        insertMinToRear(min_index);
    }
}
