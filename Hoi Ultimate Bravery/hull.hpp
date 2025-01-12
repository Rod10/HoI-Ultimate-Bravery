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
		case Hull::HeavyShip: return "heavyShip";
		case Hull::SuperHeavyShip: return "superHeavyShip";
		case Hull::Carrier: return "carrier";
		case Hull::Submarine: return "submarine";
		default:
			break;
		}
	}

	static std::string typeToEquipmentString(Type type) {
		switch (type)
		{
		case Hull::Destroyer: return "light";
		case Hull::Cruiser: return "cruiser";
		case Hull::HeavyShip: return "heavy";
		case Hull::SuperHeavyShip: return "heavy";
		case Hull::Carrier: return "carrier";
		case Hull::Submarine: return "sub";
		default:
			break;
		}
	}
};

