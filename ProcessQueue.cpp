#include "ProcessQueue.h"

using namespace std;

ProcessQueue::ProcessQueue(bool active){
    flag = active;
}

void ProcessQueue::addProcess(thread process){
    TH.push(process);
}

void ProcessQueue::updateFlag(){
    if(TH.empty()){
        flag = !flag;
    }
}

thread ProcessQueue::removeProcess(){
    TH.pop();
    updateFlag();
}
