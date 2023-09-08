#pragma once
#include <string>
class PlaneType
{
public: 
	enum Type {
		Small,
		Medium,
		Large,
		Last
	};

	static std::string typeToString(Type type) {
		switch (type)
		{
		case PlaneType::Small: return "small";
		case PlaneType::Medium: return "medium";
		case PlaneType::Large: return "large";
		default:
			break;
		}
	}
};

