//
//  main.cpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-09.
//

#include <unistd.h>
//#include "Process.cpp"
//#include "ProcessQueue.cpp"
//#include "Clock.hpp"
#include "Scheduler.cpp"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <queue>
#include <thread>
#include <vector>

using namespace std;

void startUp();
void updateClock();
void sleepScheduler(int timeSlice);

int clck;
int process_count;
ProcessQueue q1(true);
ProcessQueue q2(false);
queue<Process*> processList;
vector<thread> threadList;
Clock* timer = new Clock();
Scheduler sched;

int main(){

    startUp();
    timer->startClock();
    thread th(&Scheduler::schedule, sched);
    while(processList.size() != 0){
        if(processList.front()->getArrivalTime() == timer->getTime()){
            processList.front()->setClock(timer);
            sched.addProcess(processList.front());
        }
    }

    sched.setTerminated(true);
    
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

void sleepScheduler(int timeSlice){
    int startclk = timer->getTime();
    while((startclk + timeSlice) != timer->getTime()){

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
                    if( i == 0){
                        process_count = stoi(line);
                        line = "";
                    }
                    
                    else{
                        string p_id = line.substr(0,line.find_first_of(" "));
                        line = line.substr(line.find_first_of(" ")+1);
                        int arrival = stoi(line.substr(0,line.find_first_of(" ")));
                        line = line.substr(line.find_first_of(" ")+1);
                        int burst = stoi(line.substr(0,line.find_first_of(" ")));
                        line = line.substr(line.find_first_of(" ")+1);
                        int priority = stoi(line.substr(0,line.find_first_of("\n")));
                        //cout<< arrival<<" "<<burst<<" "<<priority<<endl;
                        Process* tempProcess = new Process(p_id,arrival,burst,priority);
                        processList.push(tempProcess);
                        q2.addProcess(tempProcess);
                        line = "";
                    }
                }
                
                if (myFile.eof())
                    break;
            }
        }
}

void updateClock()  {
    while (true)    {
        sleep(0.1);
        clck++;
        cout << clck << endl;
    }
}
