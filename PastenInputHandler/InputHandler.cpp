
#include <windows.h>
#include <algorithm>

#include "pch.h"
#include "InputHandler.h"
#include "INIReader.h"

InputHandler::InputHandler()
{
}

void InputHandler::LoadConfigFromFile()
{
	LoadConfigFromFile(_defaultPath);
}
void InputHandler::LoadConfigFromFile(std::string filePath)
{
	INIReader reader(filePath.c_str());
	if (reader.ParseError() < 0) {
		printf("Can't load %s", filePath.c_str());
		return;
	}
	
	auto fields = reader.GetFields("Keyboard");
	for (auto& field : fields)
	{
		std::string strCommand = field;
		std::string strSymbol = reader.Get("Keyboard", field, "");

		AddBinding(strCommand, strSymbol);
	}
}

void InputHandler::Update()
{
	_inputState.clear();
	for (auto& it : _inputMap)
	{
		auto input = _inputMap[it.first];
		_inputState.insert_or_assign(it.first, input->getValueFunction());
	}
}

InputValueTypes InputHandler::GetValueOfInput(std::string inputName)
{
	return GetValueOfInput(inputName, _inputState);
}
InputValueTypes InputHandler::GetValueOfInput(std::string inputName, std::map<std::string, InputValueTypes> inputState)
{
	return inputState[inputName];
}

InputValueTypes InputHandler::GetStateOfCommand(std::string commandName)
{
	InputValueTypes result;
	if (_commandMap.contains(commandName))
	{
		Command* command = _commandMap[commandName];
		for (auto& bind : _bindingMap)
		{
			if (bind.first.first == commandName)
			{
				std::string inputName = bind.first.second;

				InputValueTypes temp = GetValueOfInput(inputName);

				if (temp > result)
					result = temp;
			}
		}
	}
	return result;
}

void InputHandler::AddCommand(std::string commandName, CommandType commandType)
{
	auto newCommand = new Command(commandName, commandType);
	_commandMap.insert_or_assign(commandName, newCommand);
}

void InputHandler::AddInput(std::string inputName)
{
	auto newInput = new Input(inputName);
	_inputMap.insert_or_assign(inputName, newInput);
}
void InputHandler::AddInput(std::string inputName, InputType inputType, std::function<InputValueTypes  ()> getValFunc)
{
	auto newInput = new Input(inputName, inputType, getValFunc);
	_inputMap.insert_or_assign(inputName, newInput);
}

void InputHandler::AddBinding(std::string commandName, std::string inputName, std::function<InputValueTypes  (InputValueTypes )> convertionFunc)
{
	if (!_commandMap.contains(commandName))
		AddCommand(commandName);
	if (!_inputMap.contains(inputName))
		AddInput(inputName);

	auto newBinding = new Binding(commandName, inputName, convertionFunc);
	this->_bindingMap.insert_or_assign(std::pair<std::string, std::string>(commandName, inputName), newBinding);
}