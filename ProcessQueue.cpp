#include "ProcessQueue.h"

using namespace std;

ProcessQueue::ProcessQueue(bool active){
    flag = active;
}

void ProcessQueue::addProcess(Process p){
    plist.push(p);
}

void ProcessQueue::updateFlag(){
    if(plist.empty()){
        flag = !flag;
    }
}

Process ProcessQueue::removeProcess(){
    Process temp = plist.front();
    plist.pop();
    return temp;
}

int ProcessQueue::minIndex(int sortedIndex)
{
    int min_index = -1;
    int min_val = 140;
    int n = plist.size();
    for (int i=0; i<n; i++)
    {
        Process curr = plist.front();
        plist.pop();  // This is dequeue() in C++ STL
 
        // we add the condition i <= sortedIndex
        // because we don't want to traverse
        // on the sorted part of the queue,
        // which is the right part.
        if (curr.getPriority() <= min_val && i <= sortedIndex)
        {
            min_index = i;
            min_val = curr.getPriority();
        }
        plist.push(curr);  // This is enqueue() in
                       // C++ STL
    }
    return min_index;
}
 
// Moves given minimum element to rear of
// queue
void ProcessQueue::insertMinToRear(int min_index)
{
    Process min_val;
    int n = plist.size();
    for (int i = 0; i < n; i++)
    {
        Process curr = plist.front();
        plist.pop();
        if (i != min_index)
            plist.push(curr);
        else
            min_val = curr;
    }
    plist.push(min_val);
}
 
void ProcessQueue::sort()
{
    for (int i = 1; i <= plist.size(); i++)
    {
        int min_index = minIndex(plist.size() - i);
        insertMinToRear(min_index);
    }
}

void ProcessQueue::printQueue(){
    Process temp;
    queue<Process> tempList = plist;
    while(!tempList.empty()){
        temp = tempList.front();
        tempList.pop();
        cout << "PID: " << temp.getProcessID() <<" Priority: " << temp.getPriority() << endl;
    }
}