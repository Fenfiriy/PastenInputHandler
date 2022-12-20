#pragma once

#include <any>
#include <functional>
#include <string>

#include "InputType.h"

struct Input
{
	std::string name;
	InputType type;
	std::function<std::any()> getValueFunction;

	Input(std::string inputName);
	Input(std::string inputName, InputType inputType, std::function<std::any ()> getValFunc);
};

std::pair<InputType, std::function<std::any()>> GetDefaultsForInput(std::string inputName);

