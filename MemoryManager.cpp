#pragma once
#include "MemoryManager.h"

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
	delete variableValue;
	delete apiCommand;
	delete variableId;

	for (int i = 0; i < availablePages->size(); i++) {
		delete availablePages->at(i);
	}
}

void MemoryManager::setApiCommand(std::string* command) {
	apiCommand = command;
}

string* MemoryManager::getApiCommand() {
	return apiCommand;
}

void MemoryManager::setVariableId(string* id) {
	variableId = id;
}

string* MemoryManager::getVariableId() {
	return variableId;
}

void MemoryManager::setVariableValue(int* value) {
	variableValue = value;
}

int* MemoryManager::getVariableValue() {
	return variableValue;
}

