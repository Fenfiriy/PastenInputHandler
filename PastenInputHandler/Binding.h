#pragma once

#include <any>
#include <functional>

#include "Command.h"
#include "Input.h"

class Binding
{
public:
	std::string commandName;
	std::string inputName;
	Binding(std::string commandName, std::string inputName, std::function<std::any (std::any)> convertionFunc);
private:
	std::function<std::any (std::any)> _ConvertionFunc;
};