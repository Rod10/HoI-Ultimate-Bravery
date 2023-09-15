#pragma once
#include "shiptype.hpp"
#include "shipversion.hpp"
#include "utils.hpp"

#include <time.h>

class Module
{
public:
	enum Type {
		Engine,
		Armor,
		LightBattery,
		HeavyBattery,
		SecondaryBattery,
		AntiAir,
		Torpedo,
		RadarSonar,
		Snorkel,
		FireControl,
		AntiSubmarine,
		Mine,
		Aircraft,
		Fuel,
		Radar,
		Sonar,
		None,
		Last
	};

	enum SubType {
		Light,
		LightCruiser,
		DualPurpose,
		AutoLoader,
		MineLaying,
		MineSweeping,
		Secondary
	};

	enum Version {
		Early,
		Basic,
		Improved,
		Advanced,
		SuperHeavyBattleship
	};

	enum CustomModulePos {
		First = 20,
		Second = 90,
		Third = 168,
		Four = 238,
		Five = 313,
		Six = 388,
		Sevent = 455
	};

	Module() {}
	Module(Type type) : type(type) {}
	Module(Type type, Version version) :
		type(type),
		version(version) {}
	Module(Type type, SubType subType, Version version) :
		type(type),
		subType(subType),
		version(version) {}

	Type type;
	SubType subType;
	Version version;

	static std::string moduleTypeToStringFile(Type type) {
		switch (type)
		{
		case Module::Engine: return "Engine";
		case Module::Armor: return "Armor";
		case Module::LightBattery: return "LightBattery";
		case Module::HeavyBattery: return "HeavyBattery";
		case Module::SecondaryBattery: return "SecondaryBattery";
		case Module::AntiAir: return "AntiAir";
		case Module::Torpedo: return "Torpedo";
		case Module::RadarSonar: return "RadarSonar";
		case Module::Snorkel: return "Snorkel";
		case Module::FireControl: return "FireControl";
		case Module::AntiSubmarine: return "AntiSubmarine";
		case Module::Mine: return "Mine";
		case Module::Aircraft: return "Aircraft";
		case Module::Fuel: return "Fuel";
		case Module::Radar: return "Radar";
		case Module::Sonar: return "Sonar";
		case Module::None:
			break;
		default:
			break;
		}
	}
	
	static Module::Version stringToVersion(std::string version) {
		if (version == "early") return Early;
		if (version == "basic") return Basic;
		if (version == "improved") return Improved;
		if (version == "advanced") return Advanced;
		if (version == "superHeavyBattleship") return SuperHeavyBattleship;
	}

	static Module::Version intToVersion(int type) {
		switch (type)
		{
		case 0: return Early;
		case 1: return Basic;
		case 2: return Improved;
		case 3: return Advanced;
		case 4: return SuperHeavyBattleship;
		default:
			break;
		}
	}

	static Module::SubType stringToSubType(std::string type) {
		if (type == "light") return Light;
		if (type == "lightCruiser") return LightCruiser;
		if (type == "dualPurpose") return DualPurpose;
		if (type == "autoLoader") return AutoLoader;
		if (type == "mineLaying") return MineLaying;
		if (type == "mineSweeping") return MineSweeping;
		if (type == "secondary") return Secondary;
	}

	static std::string typeToImagesString(Type type, SubType subType, ShipType::Type shipType) {
		switch (type)
		{
		case Module::Engine: return "Engine";
		case Module::Armor: 
			if (shipType == ShipType::Type::Battlecruiser) {
				return "Armor";
			}
			else if (shipType == ShipType::Type::Battleship || shipType == ShipType::Type::SuperHeavyBattleship) {
				return "Armor_thick";
			}
			else if (shipType == ShipType::Type::Carrier || shipType == ShipType::Type::LightCruiser || shipType == ShipType::Type::HeavyCruiser) {
				return "Armor_thin";
			}
		case Module::LightBattery:
			if (subType == Light) {
				return "Light_battery";
			}
			else if (subType == LightCruiser) {
				return "Medium_light_battery";
			}
			else if (subType == AutoLoader) {
				return "Dp_medium_light_battery";
			}
			else if (subType == DualPurpose) {
				return "Dp_light_battery";
			}
		case Module::HeavyBattery:
			if (shipType == ShipType::Type::HeavyCruiser) return "Medium_battery";
			else if (shipType == ShipType::Type::Battleship || shipType == ShipType::Type::SuperHeavyBattleship) return "Heavy_battery";
		case Module::SecondaryBattery:
			if (subType == Secondary) return "Secondary_battery";
			else if (subType == DualPurpose) return "Dp_secondary_battery";
		case Module::AntiAir: return "Anti_air";
		case Module::Torpedo:
			if (shipType == ShipType::Submarine) {
				return "Sub_torpedo_launcher";
			} else {
				return "Ship_torpedo_launcher";
			}
		case Module::Snorkel: return "Submarine_snorkel";
		case Module::FireControl: return "Fire_control_system";
		case Module::AntiSubmarine: return "Depth_charge";
		case Module::Mine:
			if (subType == MineLaying) {
				return "Minelaying_rails";
			}
			else if (subType == MineSweeping) {
				return "Minesweeping_gear";
			}
		case Module::Aircraft:
			if (shipType == ShipType::Type::Carrier) {
				return "Deck_space";
			}
			else {
				return "Airplane_launcher";
			}
		case Module::Fuel: return "Fuel_tank";
		case Module::Radar: return "Radar";
		case Module::Sonar: return "Sonar";
		case Module::None: return "None";
		default:
			break;
		}
	}

	static std::string versionToString(Version version) {
		switch (version)
		{
		case Module::Basic: return "1";
		case Module::Early: return "2";
		case Module::Improved: return "3";
		case Module::Advanced: return "4";
		default:
			break;
		}
	}

	static Module generateModule(Type moduleType, ShipType::Type type, ShipVersion::Version version);
	static Module generateNone(Type type);
};

