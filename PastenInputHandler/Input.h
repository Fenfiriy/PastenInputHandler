#pragma once

#include <variant>
#include <functional>
#include <string>

#include "InputType.h"

struct Input
{
	std::string name;
	InputType type;
	std::function<InputValueTypes ()> getValueFunction;

	Input(std::string inputName);
	Input(std::string inputName, InputType inputType, std::function<InputValueTypes  ()> getValFunc);
};

std::pair<InputType, std::function<InputValueTypes ()>> GetDefaultsForInput(std::string inputName);

