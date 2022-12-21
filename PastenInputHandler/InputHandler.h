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
	void AddInput(std::string inputName, InputType inputType, std::function<InputValueTypes  ()> getValFunc);
	void AddBinding(std::string commandName, std::string inputName, std::function<InputValueTypes (InputValueTypes)> convertionFunc = DefaultConvertionFunction);

	InputValueTypes GetValueOfInput(std::string inputName);
	InputValueTypes GetValueOfInput(std::string inputName, std::map<std::string, InputValueTypes > inputState);

	InputValueTypes GetStateOfCommand(std::string commandName);

	void LoadConfigFromFile();
	void LoadConfigFromFile(std::string filePath);

private:
	std::map<std::string, Command*> _commandMap;
	std::map<std::string, Input*> _inputMap;
	std::map<std::pair<std::string, std::string>, Binding*> _bindingMap;
	std::map<std::string, InputValueTypes > _inputState;

	std::string _defaultPath = "..\\..\\..\\Assets\\Configs\\actionmap.ini";;
	std::string _name;
};