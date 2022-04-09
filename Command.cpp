#include "Command.h"

using namespace std;

Command::Command(){
    commandName = "";
    variableID = "";
    variableValue = NULL;
}

Command::Command(string name, string id, int value){
    commandName = name;
    variableID = id;
    variableValue = value;
}

void Command::setCommandName(string name){
    commandName = name;
}

string Command::getCommandName(){
    return commandName;
}

void Command::setVariableID(string id){
    variableID = id;
}

string Command::getVariableID(){
    return variableID;
}

void Command::setVariableValue(int value){
    variableValue = value;
}

int Command::getVariableValue(){
    return variableValue;
}