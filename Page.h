#pragma once
#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <vector>

class Page {
private:
    int variableId;
    int variableValue;
    int last;
    std::vector<int>* history;

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