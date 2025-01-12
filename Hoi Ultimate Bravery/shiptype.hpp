#pragma once
#include "hull.hpp"

#include <string>
class ShipType
{
public:
	enum Type {
		Destroyer,
		LightCruiser,
		HeavyCruiser,
		Battlecruiser,
		Battleship,
		SuperHeavyBattleship,
		Carrier,
		Submarine,
		Last
	};

	static ShipType::Type intToShipType(int type) {
		switch (type)
		{
		default: break;
		case 0: return Destroyer;
		case 1: return LightCruiser;
		case 2: return HeavyCruiser;
		case 3: return Battlecruiser;
		case 4: return Battleship;
		case 5: return SuperHeavyBattleship;
		case 6: return Carrier;
		case 7: return Submarine;
		}
	}

	static std::string shipTypeToString(Type type) {
		switch (type)
		{
		case ShipType::Destroyer: return "destroyer";
		case ShipType::LightCruiser: return "lightCruiser";
		case ShipType::HeavyCruiser: return "heavyCruiser";
		case ShipType::Battlecruiser: return "battlecruiser";
		case ShipType::Battleship: return "battleship";
		case ShipType::SuperHeavyBattleship: return "superHeavyBattleship";
		case ShipType::Carrier: return "carrier";
		case ShipType::Submarine: return "submarine";
		default:
			break;
		}
	}

	static std::string shipTypeToIconString(Type type) {
		switch (type)
		{
		case ShipType::Destroyer: return "destroyer";
		case ShipType::LightCruiser: return "light_cruiser";
		case ShipType::HeavyCruiser: return "light_cruiser";
		case ShipType::Battlecruiser: return "battleship";
		case ShipType::Battleship: return "battleship";
		case ShipType::SuperHeavyBattleship: return "superHeavyBattleship";
		case ShipType::Carrier: return "carrier";
		case ShipType::Submarine: return "submarine";
		default:
			break;
		}
	}

	static ShipType::Type hullToShipType(Hull::Type hull) {
		switch (hull) {
		case Hull::Destroyer: return Destroyer;
		case Hull::SuperHeavyShip: return SuperHeavyBattleship;
		case Hull::Carrier: return Carrier;
		case Hull::Submarine: return Submarine;
		}
	}

	static std::string typeToEquipmentString(ShipType::Type type) {
		switch (type)
		{
		case ShipType::Destroyer: return "light";
		case ShipType::LightCruiser: return "cruiser";
		case ShipType::HeavyCruiser: return "cruiser";
		case ShipType::Battlecruiser: return "heavy";
		case ShipType::Battleship: return "heavy";
		case ShipType::SuperHeavyBattleship: return "heavy";
		case ShipType::Carrier: return "carrier";
		case ShipType::Submarine: return "submarine";
		case ShipType::Last:
			break;
		default:
			break;
		}
	}
};

