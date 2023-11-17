#pragma once
#include <map>
#include <string>
class UnitType
{
public:
	enum Type {
		Ship,
		Tank,
		Plane,
		Division
	};

	static std::string typeToString(Type type) {
		switch (type)
		{
		case UnitType::Ship: return "ship";
		case UnitType::Tank: return "tank";
		case UnitType::Plane: return "plane";
		case UnitType::Division: return "division";
		default:
			break;
		}
	}
};

