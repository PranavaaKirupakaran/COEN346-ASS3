#include "MemoryManager.h"
#include <string>
#include <fstream>
using namespace std;

MemoryManager::MemoryManager() {
    availablePages = new vector<Page*>();
    apiCommand = "";
    variableId = "";
    variableValue = 0;
    timeOut = 0;
    k = 0;

}

MemoryManager::MemoryManager(int noOfPages, int timeOutValue, int kValue) {
    availablePages = new vector<Page*>();
    for (int i = 0; i < noOfPages; i++) {
        Page* temp = new Page();
        availablePages->push_back(temp);
    }

    timeOut = timeOutValue;
    k = kValue;

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

void MemoryManager::setAccessedPage(int pageNumber) {
    accessedPage = pageNumber;
}

int MemoryManager::getAccessedPage() {
    return accessedPage;
}

void MemoryManager::lruk(bool swapPage) {
    int currentTime = clk->getTime();

    if (!swapPage) {
        int accessTime = clk->getTime();
        Page* tempPage = availablePages->at(accessedPage);
        int PageLast = tempPage->getLast();
        vector<int>* PageHistory = tempPage->getHistory();
        if ((accessTime - PageLast) < timeOut) {
            tempPage->setLast(accessTime);
        }
        else if ((accessTime - PageLast) > timeOut) {
            int lcp = PageLast - PageHistory->at(0);

            for (int i = 1; k >= i; i++) {
                PageHistory->at(i) = PageHistory->at(i - 1) + lcp;
            }
            tempPage->setLast(currentTime);
            PageHistory->at(0) = currentTime;

        }
        delete PageHistory;
    }
    else {
        int minIndex = -1;
        int minValue = INT_MAX;
        for (int i = 0; i < availablePages->size(); i++) {
            Page* tempPage = availablePages->at(i);
            if (tempPage->getLast() - tempPage->getHistoryAt(0) > timeOut) {
                if (tempPage->getHistoryAt(k) < minValue) {
                    minValue = tempPage->getHistoryAt(k);
                    minIndex = i;
                }
            }

        }

    }

}

void MemoryManager::run(){
    
    int temp;

    fstream vm;

    do {
        if (apiCommand == "Store") {
            temp = 1;
        }
        else if (apiCommand == "Release") {
            temp = 2;
        }
        else if (apiCommand == "Lookup") {
            temp = 3;
        }
        switch (temp) {
        case 1: {
            bool addedFlag = false;
            for (int i = 0; i < availablePages->size(); i++) {
                Page* temp = availablePages->at(i);
                if (temp->getVariableID() == "") {
                    temp->setVariableID(variableId);
                    temp->setVariableValue(variableValue);
                    addedFlag = true;
                    break;
                }
            }
            if (!addedFlag) {
                vm.open("vm.txt", std::ios_base::app);
                vm << variableId << " " << variableValue << endl;
                vm.close();
            }

            }

            case 2: {
                bool removedFlag = false;
                for (int i = 0; i < availablePages->size(); i++) {
                    Page* temp = availablePages->at(i);
                    if (temp->getVariableID() == variableId) {
                        temp->setVariableID("");
                        temp->setVariableValue(NULL);
                        removedFlag = true;
                        break;
                    }
                }
                if (!removedFlag) {
                    cout << "variable not found" << endl;
                }

            }
            case 3: {
                bool foundFlag = false;
                for (int i = 0; i < availablePages->size(); i++) {
                    Page* temp = availablePages->at(i);
                    if (temp->getVariableID() == variableId) {
                        cout << "Variable " << variableId << ", Value: " << variableValue << endl;
                        foundFlag = true;
                        break;
                    }
                }
                if (!foundFlag) {
                    vm.open("vm.txt", std::ios_base::in);
                    do {
                        string tempLine;
                        getline(vm, tempLine);
                        string id = tempLine.substr(0, tempLine.find_first_of(" "));
                        if (id == variableId) {

                        }

                    } while (!vm.eof());
                }
            }

        }
    } while (true);
}

void MemoryManager::setK(int kValue) {
    k = kValue;
}

int MemoryManager::getK() {
    return k;
}
