#include "Page.h"

using namespace std;

Page::Page() {
    variableId = "";
    variableValue, last = NULL;
    history = new vector<int>();
}

Page::Page(int id, int value) {
    variableId = id;
    variableValue = value;
    last = 0;
    history = new vector<int>();
}

Page::~Page() {
    delete history;
}

void Page::setVariableID(string id) {
    variableId = id;
}

string Page::getVariableID() {
    return variableId;
}

void Page::setVariableValue(int value) {
    variableValue = value;
}

int Page::getVariableValue() {
    return variableValue;
}

void Page::addToHistory(int timeStamp) {
    history->push_back(timeStamp);
}

int Page::getHistoryAt(int position) {
    return history->at(position);
}

vector<int>* Page::getHistory() {
    return history;
}

void Page::setLast(int timeStamp) {
    last = timeStamp;
}

int Page::getLast() {
    return last;
}

