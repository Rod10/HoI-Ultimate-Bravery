#pragma once
#include "regimenttype.hpp"
#include "unitsubtype.hpp"

#include <string>

class Unit
{
public:
	Unit(
		RegimentType::Type regimentType,
		std::string name,
		UnitSubType::Type unitSubType,
		int width):
		regimentType(regimentType),
		name(name),
		unitSubType(unitSubType),
		width(width) {}

	RegimentType::Type regimentType;
	std::string name;
	UnitSubType::Type unitSubType;
	int width;
};

