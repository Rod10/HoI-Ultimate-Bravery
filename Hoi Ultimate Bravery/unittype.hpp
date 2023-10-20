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
		Infantry
	};

	static std::string typeToString(Type type) {
		switch (type)
		{
		case UnitType::Ship: return "ship";
		case UnitType::Tank: return "tank";
		case UnitType::Plane: return "plane";
		case UnitType::Infantry: return "infantry";
		default:
			break;
		}
	}
};

