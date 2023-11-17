#pragma once
#include "regimenttype.hpp"
#include "unitsubtype.hpp"

#include <string>
class Support {
public:
	Support(
		RegimentType::Type regimentType,
		std::string name,
		UnitSubType::Support unitSubType,
		int width) :
		regimentType(regimentType),
		name(name),
		unitSubType(unitSubType),
		width(width) {}

	RegimentType::Type regimentType;
	std::string name;
	UnitSubType::Support unitSubType;
	int width;
};

