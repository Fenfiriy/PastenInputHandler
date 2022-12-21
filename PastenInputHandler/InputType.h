#pragma once

enum class InputType
{
	Axis,
	Coordinate,
	Button
};

typedef std::variant<bool, int, float> InputValueTypes;