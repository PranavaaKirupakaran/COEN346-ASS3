//
//  main.cpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-09.
//

#include <unistd.h>
#include "Process.hpp"
#include "Process.cpp"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <queue>
using namespace std;

void startUp();
void updateClock();

int clck;
int process_count;
queue<Process> q1;
queue<Process> q2;
queue<Process> processList;

int main(){

    startUp();

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
                        cout<< arrival<<" "<<burst<<" "<<priority<<endl;
                        processList.push(Process(p_id,arrival,burst,priority));
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

