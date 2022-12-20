#pragma once

#include <string>

#include "CommandType.h"

struct Command
{
	std::string name;
	CommandType type;


	Command(std::string n, CommandType t);
};

