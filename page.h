#pragma once
#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <vector>

class Page {
private:
    std::string variableId;
    int variableValue;
    int last;
    int timeout;
    std::vector<int>* history;


public:
    Page();
    Page(int id, int value);
    ~Page();
    void setVariableID(std::string id);
    std::string getVariableID();
    void setVariableValue(int value);
    int getVariableValue();
    void addToHistory(int timeStamp);
    int getHistoryAt(int position);
    std::vector<int>* getHistory();
    void setLast(int timeStamp);
    int getLast();

};

#endif
