#include "MemoryManager.hpp"

using namespace std;

MemoryManager::MemoryManager() {
    availablePages = new vector<Page*>();
    apiCommand = "";
    variableId = "";
    variableValue = 0;
    timeOut = 0;

}

MemoryManager::MemoryManager(int noOfPages, int timeOutValue) {
    availablePages = new vector<Page*>();
    for (int i = 0; i < noOfPages; i++) {
        Page* temp = new Page();
        availablePages->push_back(temp);
    }

    timeOut = timeOutValue;

}

MemoryManager::~MemoryManager() {

    for (int i = 0; i < availablePages->size(); i++) {
        delete availablePages->at(i);
    }
}

void MemoryManager::setApiCommand(std::string command) {
    apiCommand = command;
}

string MemoryManager::getApiCommand() {
    return apiCommand;
}

void MemoryManager::setVariableId(string id) {
    variableId = id;
}

string MemoryManager::getVariableId() {
    return variableId;
}

void MemoryManager::setVariableValue(int value) {
    variableValue = value;
}

int MemoryManager::getVariableValue() {
    return variableValue;
}

void MemoryManager::setTimeOut(int timeOutValue) {
    timeOut = timeOutValue;
}

int MemoryManager::getTimeOut() {
    return timeOut;
}

void MemoryManager::setClock(Clock* timer) {
    clk = timer;
}

Clock* MemoryManager::getClock() {
    return clk;
}

void MemoryManager::setAccessedPage(int pageNumber){
    accessedPage = pageNumber;
}

int MemoryManager::getAccessedPage(){
    return accessedPage;
}

void MemoryManager::lruk(){
    int accessTime = clk->getTime();
    Page* tempPage = availablePages->at(accessedPage);
    int PageLast = tempPage->getLast();
    vector<int>* PageHistory = tempPage->getHistory();
    int currentTime = clk->getTime();
    
    if((accessTime - PageLast) < timeOut){
        tempPage->setLast(accessTime);
    }

    else if((accessTime - PageLast) > timeOut){
        int lcp = PageLast - PageHistory->at(1);

        for(int i=1; availablePages->size() >= i && i > 1; i++){
            PageHistory->at(i) = PageHistory->at(i-1) +lcp;
        }
        tempPage->setLast(currentTime);
        PageHistory->at(1) = currentTime;
        
    }
    
    delete PageHistory;
}

