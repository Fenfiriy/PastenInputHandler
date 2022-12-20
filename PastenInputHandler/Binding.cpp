#include "pch.h"
#include "Binding.h"

Binding::Binding(std::string commandName, std::string inputName, std::function<std::any (std::any)> convertionFunc)
{
	this->commandName = commandName;
	this->inputName = inputName;
	this->_ConvertionFunc = convertionFunc;
}
