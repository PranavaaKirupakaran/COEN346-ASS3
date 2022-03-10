//
//  main.cpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-09.
//

#include "Process.hpp"
#include "Process.cpp"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <queue>
using namespace std;

int process_count;
queue<Process> q1;
queue<Process> q2;

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
                        q1.push(Process(p_id,arrival,burst,priority));
                        line = "";
                    }
                }
                
                if (myFile.eof())
                    break;
            }
        }
}

int main(){

    startUp();
}

