#include "pch.h"
#include "Input.h"

Input::Input(std::string inputName)
{
	this->name = inputName;

	std::pair<InputType, std::function<InputValueTypes  ()>> defaults = GetDefaultsForInput(inputName);
	this->type = defaults.first;
	this->getValueFunction = defaults.second;
}
Input::Input(std::string inputName, InputType inputType, std::function<InputValueTypes  ()> getValFunc)
{
	this->name = inputName;
	this->type = inputType;
	this->getValueFunction = getValFunc;
}

std::pair<InputType, std::function<InputValueTypes  ()>> GetDefaultsForInput(std::string inputName)
{
	InputType resultType;
	std::function<InputValueTypes  ()> resultFunc;
	//better implement some better type of check
	if (inputName.size() == 1)
	{
		if (inputName.compare("A") >= 0 && inputName.compare("Z") <= 0)
		{
			resultType = InputType::Button;
			resultFunc = [vk_key = inputName.c_str()[0]]()
			{
				InputValueTypes result = (bool)(GetAsyncKeyState(vk_key) & 0x8000);
				return result;
			};
		}
		else if (inputName.compare("0") >= 0 && inputName.compare("9") <= 0)
		{
			resultType = InputType::Button;
			resultFunc = [vk_key = inputName.c_str()[0]]()
			{
				InputValueTypes result = (bool)(GetAsyncKeyState(vk_key) & 0x8000);
				return result;
			};
		}
	}
	else if (inputName.compare("LeftMouseButton") == 0)
	{
		resultType = InputType::Button;
		resultFunc = []()
		{
			InputValueTypes result = (bool)(GetAsyncKeyState(VK_LBUTTON) & 0x8000);
			return result;
		};
	}
	else if (inputName.compare("RightMouseButton") == 0)
	{
		resultType = InputType::Button;
		resultFunc = []()
		{
			InputValueTypes result = (bool)(GetAsyncKeyState(VK_RBUTTON) & 0x8000);
			return result;
		};
	}
	else if (inputName.compare("MouseX") == 0)
	{
		resultType = InputType::Coordinate;
		resultFunc = []()
		{
			InputValueTypes result;
			POINT p;
			if (GetCursorPos(&p))
				result = (int)p.x;
			else
				result = 0;
			return result;
		};
	}
	else if (inputName.compare("MouseY") == 0)
	{
		resultType = InputType::Coordinate;
		resultFunc = []()
		{
			InputValueTypes result;
			POINT p;
			if (GetCursorPos(&p))
				result = (int)p.y;
			else
				result = 0;
			return result;
		};
	}

	return std::pair<InputType, std::function<InputValueTypes()>>(resultType, resultFunc);
}