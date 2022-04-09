#pragma once
#ifndef COMMAND_H
#define CCOMMAND_H

#include <iostream>

class Command
{
	private:
		std::string commandName;
		std::string variableID;
		int variableValue;

	public:
		Command();
		Command(std::string name, std::string id, int value);
		void setCommandName(std::string name);
		std::string getCommandName();
		void setVariableID(std::string id);
		std::string getVariableID();
		void setVariableValue(int value);
		int getVariableValue();

};
#endif

