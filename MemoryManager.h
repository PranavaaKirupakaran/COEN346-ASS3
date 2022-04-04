#pragma once

#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <iostream>
#include <vector>
#include "Page.h"

class MemoryManager {
private:
    std::vector<Page*>* availablePages;
    std::string apiCommand;
    std::string variableId;
    int variableValue;
    int timeOut;

public:
    MemoryManager();
    MemoryManager(int noOfPages, int timeOutValue);
    ~MemoryManager();
    void setApiCommand(std::string command);
    std::string getApiCommand();
    void setVariableId(std::string id);
    std::string getVariableId();
    void setVariableValue(int value);
    int getVariableValue();
    void setTimeOut(int timeOutValue);
    int getTimeOut();

};

#endif