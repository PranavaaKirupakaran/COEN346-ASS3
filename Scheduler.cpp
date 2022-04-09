//
//  Scheduler.cpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-13.
//

#include "Scheduler.h"
#include <cmath>
#include <thread>
#include <vector>
#include <fstream>

using namespace std;

Scheduler::Scheduler() {
    q2.updateFlag();
    timeSlice = 0;
    core = 1;
    terminated = false;
}

Scheduler::Scheduler(int noCores) {
    q2.updateFlag();
    timeSlice = 0;
    core = noCores;
    terminated = false;
    for (int i = 0; i < noCores; i++) {
        isExecuting.push_back(false);
    }
}

//Calculate the time slice of a process based on the given formula
int Scheduler::calculateTimeSlice(Process* p) {
    if (p->getPriority() < 100)
        timeSlice = (140 - p->getPriority()) * 20;
    else if (p->getPriority() >= 100)
        timeSlice = (140 - p->getPriority()) * 5;
    return timeSlice;
}

//Calculate the priority of a process based on the given formula
int Scheduler::calculatePriority(Process* p, int timeNow) {
    fstream out;
    //Update priority whenever process executes twice
    if (p->getCpuIteration() % 2 == 0) {
        int bonus = floor((p->getWaitingTime() * 10) / (timeNow - p->getArrivalTime()));
        int newPriority = max(100, min((p->getPriority() - bonus + 5), 139));
        out.open("output.txt", std::ios_base::app);
        //Lock thread access to printing to output.txt
        print->lock();
        out << "TIME " << timeNow << ", " << p->getProcessID() << ", priority updated to " << newPriority << endl;
        print->unlock();
        return newPriority;
    }
    else
        return p->getPriority();

}

//Swap active and expired queues, and sort each based on priority
void Scheduler::swapFlag() {
    q2.updateFlag();
    q1.updateFlag();
    q2.sort();
    q1.sort();
}

//Add process to the queue
void Scheduler::addProcess(Process* p) {
    //Check if process is new and has never been executed
    if (p->getCpuIteration() == 0) {
        fstream out;
        out.open("output.txt", std::ios_base::app);
        print->lock();
        out << "TIME " << clk->getTime() << ", " << p->getProcessID() << " ARRIVED" << endl;
        print->unlock();
    }
    //Add process only to the expired queue (flag = false means it is the expired queue)
    if (q1.getFlag() == false) {
        q1.addProcess(p);
    }
    else if (!q2.getFlag()) {
        q2.addProcess(p);
    }
}

//Set the clock for the scheduler
void Scheduler::setClock(Clock* c) {
    clk = c;
}

//Return the current active queue
ProcessQueue* Scheduler::getActiveQueue() {
    if (q1.getFlag())
        return &q1;
    else
        return &q2;
}

//Return the current expired queue
ProcessQueue* Scheduler::getExpiredQueue() {
    if (!q1.getFlag())
        return &q1;
    else
        return &q2;
}

void Scheduler::schedule() {
    ProcessQueue* active = getActiveQueue();
    ProcessQueue* expired = getExpiredQueue();
    Process* tempProcess = nullptr;
    fstream out;
    out.open("output.txt", std::ios_base::app);
    int currtime = clk->getTime(); 
    int availableCore = core;
    int startSliceTime = 0;

    
    while (true) {

        //Check if both queues are empty and all processes have been added to the scheduler
        if (terminated && q1.checkEmpty() && q2.checkEmpty() && core == availableCore) {
            //Join all process threads and stop the clock
            joinThreadVector();
            clk->setStartFlag(false);
            break;
        }
        while (q1.checkEmpty() && q2.checkEmpty() && availableCore == core) {
            currtime = clk->getTime();
        }
        //If active queue is empty, swap flags and reinitialize active & expired queues
        if (active->checkEmpty() && availableCore == core) {
            arrival->lock();
            swapFlag();
            active = getActiveQueue();
            expired = getExpiredQueue();
            arrival->unlock();
        }
        /*
        vector<Process*> tempProcessList;
        for (int i = 0; i < core; i++) {
            if (!isExecuting.at(i) && !active->checkEmpty()) {
                tempProcessList.push_back(active->removeProcess());
                availableCore--;
            }
        }
        */
        for (int i = 0; i < core; i++) {
            if (!isExecuting.at(i) && !active->checkEmpty()) {
                tempProcess = active->removeProcess();
                availableCore--;
            }
            if (tempProcess->getCpuIteration() == 0) {
                tempProcess->setState("STARTED");
                timeSlice = calculateTimeSlice(tempProcess);
                thread th(&Process::execute, tempProcess);
                print->lock();
                out << "TIME " << currtime << ", " << tempProcess->getProcessID() << " STARTED, GRANTED " << timeSlice << endl;
                print->unlock();
                threadVector.push_back(move(th));
                startSliceTime = currtime;
                isExecuting.at(i) = true;
            }
            else if (!isExecuting.at(i)) {

                tempProcess->setState("RESUMED");
                timeSlice = calculateTimeSlice(tempProcess);
                print->lock();
                out << "TIME " << currtime << ", " << tempProcess->getProcessID() << " RESUMED, GRANTED " << timeSlice << endl;
                print->unlock();
                startSliceTime = currtime;
                isExecuting.at(i) = true;
            }
            if (currtime - startSliceTime >= timeSlice) {
                tempProcess->setState("PAUSED");
                isExecuting.at(i) = false;
                availableCore++;
                if (tempProcess->getState() != "TERMINATED") {
                    print->lock();
                    out << "TIME " << currtime << ", " << tempProcess->getProcessID() << " PAUSED" << endl;
                    print->unlock();
                    //Claclulate and set the new priority of a process
                    tempProcess->setPriority(calculatePriority(tempProcess, currtime));
                    addProcess(tempProcess);

                }
                else {

                }
            }
            this_thread::sleep_for(std::chrono::milliseconds((10)));
            currtime = clk->getTime();
            //Simulate process execution for a timeslice by halting scheduler and letting the clock run
            /*
            sleepScheduler();
            clktime = clk->getTime();

            tempProcess->setState("PAUSED");
            */
        }
    }
}

void Scheduler::sleepScheduler() {
    int startClk = clk->getTime();
    //Infinite loop till simulated time reaches required clock time ie, process has executed for a timeslice
    
    while (timeSlice + startClk != clk->getTime()) {
        this_thread::sleep_for(std::chrono::milliseconds((15)));
    }
    
}

//Set the termianted flag for when scheduler needs to be terminated
void Scheduler::setTerminated(bool flag) {
    terminated = flag;
}

bool Scheduler::getTerminated() {
    return terminated;
}

//Function to join all process threads
void Scheduler::joinThreadVector() {
    for (int i = 0; i < threadVector.size(); i++) {
        if (threadVector.at(i).joinable()) {
            threadVector.at(i).join();
        }
    }
}

void Scheduler::setArrivalMutex(mutex* m) {
    arrival = m;
}

mutex* Scheduler::getArrivalMutex() {
    return arrival;
}

void Scheduler::setPrintMutex(mutex* m) {
    print = m;
}

mutex* Scheduler::getPrintMutex() {
    return print;
}

void Scheduler::setCore(int noCore) {
    core = noCore;
}

int Scheduler::getCore() {
    return core;
}