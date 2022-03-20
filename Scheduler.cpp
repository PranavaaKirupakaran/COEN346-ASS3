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
    terminated = false;
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
int Scheduler::calculatePriority(Process* p) {
    fstream out;
    //Update priority whenever process executes twice
    if (p->getCpuIteration() % 2 == 0) {
        int bonus = floor((p->getWaitingTime() * 10) / (clk->getTime() - p->getArrivalTime()));
        int newPriority = max(100, min((p->getPriority() - bonus + 5), 139));
        out.open("output.txt", std::ios_base::app);
        //Lock thread access to printing to output.txt
        print->lock();
        out << "TIME " << clk->getTime() << ", " << p->getProcessID() << ", priority updated to " << newPriority << endl;
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
    Process* tempProcess;
    fstream out;
    out.open("output.txt", std::ios_base::app);
    
    while (true) {
        //Check if both queues are empty and all processes have been added to the scheduler
        if (terminated && q1.checkEmpty() && q2.checkEmpty()) {
            //Join all process threads and stop the clock
            joinThreadVector();
            clk->setStartFlag(false);
            break;
        }
        while (q1.checkEmpty() && q2.checkEmpty()) {

        }
        
        //If active queue is empty, swap flags and reinitialize active & expired queues
        if (active->checkEmpty()) {
            arrival->lock();
            swapFlag();
            active = getActiveQueue();
            expired = getExpiredQueue();
            arrival->unlock();
        }

        tempProcess = active->removeProcess();
        timeSlice = calculateTimeSlice(tempProcess);
        
        //Check if its the first execution of a process
        if (tempProcess->getCpuIteration() == 0) {
            tempProcess->setState("STARTED");
            thread th(&Process::execute, tempProcess);
            print->lock();
            out << "TIME " << clk->getTime() << ", " << tempProcess->getProcessID() << " STARTED, GRANTED " << timeSlice << endl;
            print->unlock();
            threadVector.push_back(move(th));
        }
        else {

            tempProcess->setState("RESUMED");
            print->lock();
            out << "TIME " << clk->getTime() << ", " << tempProcess->getProcessID() << " RESUMED, GRANTED " << timeSlice << endl;
            print->unlock();

        }
        //Simulate process execution for a timeslice by halting scheduler and letting the clock run
        sleepScheduler();

        tempProcess->setState("PAUSED");
        if (tempProcess->getState() != "TERMINATED") {
            print->lock();
            out << "TIME " << clk->getTime() << ", " << tempProcess->getProcessID() << " PAUSED" << endl;
            print->unlock();
            
            //Claclulate and set the new priority of a process
            tempProcess->setPriority(calculatePriority(tempProcess));
            addProcess(tempProcess);
            
        }
        else {

        }
    }
}

void Scheduler::sleepScheduler() {
    int startClk = clk->getTime();
    //Infinite loop till simulated time reaches required clock time ie, process has executed for a timeslice
    while (timeSlice + startClk != clk->getTime()) {

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
