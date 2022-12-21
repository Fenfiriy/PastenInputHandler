#pragma once

#include <functional>

#include "Command.h"
#include "Input.h"

class Binding
{
public:
	std::string commandName;
	std::string inputName;
	Binding(std::string commandName, std::string inputName, std::function<InputValueTypes (InputValueTypes )> convertionFunc);
private:
	std::function<InputValueTypes  (InputValueTypes )> _ConvertionFunc;
};

InputValueTypes DefaultConvertionFunction(InputValueTypes val);