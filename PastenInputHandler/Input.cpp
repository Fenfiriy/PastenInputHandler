#include "pch.h"
#include "Input.h"

Input::Input(std::string inputName)
{
	this->name = inputName;

	std::pair<InputType, std::function<std::any()>> defaults = GetDefaultsForInput(inputName);
	this->type = defaults.first;
	this->getValueFunction = defaults.second;
}
Input::Input(std::string inputName, InputType inputType, std::function<std::any()> getValFunc)
{
	this->name = inputName;
	this->type = inputType;
	this->getValueFunction = getValFunc;
}

std::pair<InputType, std::function<std::any()>> GetDefaultsForInput(std::string inputName)
{
	InputType resultType;
	std::function<std::any()> resultFunc;
	//better implement some better type of check
	if (inputName.compare("A") >= 0 && inputName.compare("Z") <= 0)
	{
		resultType = InputType::Button;
		resultFunc = [vk_key = inputName.c_str()[0]]()
		{
			return GetAsyncKeyState(vk_key) & 0x8000;
		};
	}
	else if (inputName.compare("0") >= 0 && inputName.compare("9") <= 0)
	{
		resultType = InputType::Button;
		resultFunc = [vk_key = inputName.c_str()[0]]()
		{
			return GetAsyncKeyState(vk_key) & 0x8000;
		};
	}
	else if (inputName.compare("LeftMouseButton") == 0)
	{
		resultType = InputType::Button;
		resultFunc = []()
		{
			return GetAsyncKeyState(VK_LBUTTON) & 0x8000;
		};
	}
	else if (inputName.compare("RightMouseButton") == 0)
	{
		resultType = InputType::Button;
		resultFunc = []()
		{
			return GetAsyncKeyState(VK_RBUTTON) & 0x8000;
		};
	}
	else if (inputName.compare("MouseX") == 0)
	{
		resultType = InputType::Coordinate;
		resultFunc = []()
		{
			POINT p;
			if (GetCursorPos(&p))
				return (int)p.x;
			return 0;
		};
	}
	else if (inputName.compare("MouseY") == 0)
	{
		resultType = InputType::Coordinate;
		resultFunc = []()
		{
			POINT p;
			if (GetCursorPos(&p))
				return (int)p.y;
			return 0;
		};
	}

	return std::pair<InputType, std::function<std::any()>>(resultType, resultFunc);
}