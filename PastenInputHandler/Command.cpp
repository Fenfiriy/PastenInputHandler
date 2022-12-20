#include "pch.h"
#include "Command.h"

Command::Command(std::string n, CommandType t)
{
	this->name = n;
	this->type = t;
}