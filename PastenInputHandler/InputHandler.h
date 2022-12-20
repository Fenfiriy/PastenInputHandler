#pragma once

#ifdef PASTENINPUTHANDLER_EXPORTS
#define PASTENINPUTHANDLER __declspec(dllexport)
#else
#define PASTENINPUTHANDLER __declspec(dllimport)
#endif

#include <map>

#include "Binding.h"


class PASTENINPUTHANDLER InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void Update();

	void AddCommand(std::string commandName, CommandType commandType = CommandType::Button);
	void AddInput(std::string inputName);
	void AddInput(std::string inputName, InputType inputType, std::function<std::any()> getValFunc);
	void AddBinding(std::string commandName, std::string inputName, std::function<std::any(std::any)> convertionFunc = [](std::any inputValue) { return inputValue; });

	std::any GetInputValue(std::string inputName);
	std::any GetInputValue(std::string inputName, std::map<std::string, std::any> inputState);

	void LoadConfigFromFile();
	void LoadConfigFromFile(std::string filePath);

private:
	std::map<std::string, Command*> _commandMap;
	std::map<std::string, Input*> _inputMap;
	std::map<std::pair<std::string, std::string>, Binding*> _bindingMap;
	std::map<std::string, std::any> _inputState;

	std::string _defaultPath;
	std::string _name;
};