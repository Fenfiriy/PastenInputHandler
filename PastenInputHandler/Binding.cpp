#include "pch.h"
#include "Binding.h"

Binding::Binding(std::string commandName, std::string inputName, std::function<InputValueTypes  (InputValueTypes )> convertionFunc)
{
	this->commandName = commandName;
	this->inputName = inputName;
	this->_ConvertionFunc = convertionFunc;
}

InputValueTypes DefaultConvertionFunction(InputValueTypes val)
{
	return val;
}