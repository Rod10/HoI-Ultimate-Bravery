#pragma once
#include <string>
class Hull
{
public:
	enum Type {
		Destroyer,
		Cruiser,
		HeavyShip,
		SuperHeavyShip,
		Carrier,
		Submarine,
		Last
	};

	static std::string typeToString(Type type) {
		switch (type)
		{
		case Hull::Destroyer: return "destroyer";
		case Hull::Cruiser: return "cruiser";
		case Hull::HeavyShip: return "heavySHip";
		case Hull::SuperHeavyShip: return "superHeavyShip";
		case Hull::Carrier: return "carrier";
		case Hull::Submarine: return "submarine";
		default:
			break;
		}
	}
};

