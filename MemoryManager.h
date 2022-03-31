#pragma once

//
//  Clock.hpp
//  COEN346Scheduler
//
//  Created by Rohit Vaidya on 2022-03-13.
//

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <iostream>
#include <mutex>
#include <vector>

class Page {
private:
    int variableId;
    int variableValue;
    int last;
    std::vector<int> history;

public:
    Page();
    Page(int id, int value);
    ~Page();
    void setVariableID(int id);
    int getVariableID();
    void setVariableValue(int value);
    int getVariableValue();
    void addToHistory(int timeStamp);
    int getHistoryAt(int position);
    void setLast(int timeStamp);
    int getLast();

};

#endif