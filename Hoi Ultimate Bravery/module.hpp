#pragma once
#include "shiptype.hpp"
#include "shipversion.hpp"
#include "utils.hpp"

#include <time.h>
#include <tuple>

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
		Secondary,
		Empty
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
	Module(Type type) : type(type){}
	Module(Type type, SubType subType) : type(type), subType(subType){}
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

	static std::string moduleTypeToEquipmentString(Type type) {
		switch (type)
		{
		case Module::Engine: return "fixed_ship_engine_slot";
		case Module::Armor: return "fixed_ship_armor_slot";
		case Module::LightBattery: return "fixed_ship_battery_slot";
		case Module::HeavyBattery: return "fixed_ship_battery_slot";
		case Module::SecondaryBattery: return "fixed_ship_secondaries_slot ";
		case Module::AntiAir: return "fixed_ship_anti_air_slot";
		case Module::Torpedo: return "fixed_ship_torpedo_slot";
		case Module::RadarSonar: return "fixed_ship_radar_slot";
		case Module::Snorkel: return "";
		case Module::FireControl: return "fixed_ship_fire_control_system_slot";
		case Module::AntiSubmarine: return "";
		case Module::Mine: return "";
		case Module::Aircraft: return "fixed_ship_deck_slot_";
		case Module::Fuel: return "";
		case Module::Radar: return "fixed_ship_radar_slot";
		case Module::Sonar: return "fixed_ship_radar_slot";
		case Module::None: return "";
		case Module::Last:
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

	static std::string typeToEquipmentFileValue(Module module, Hull::Type hullType, ShipType::Type shipType) {
		if (module.subType == Empty) {
			return "empty";
		}
		switch (module.type)
		{
		case Module::Engine: return std::format("{0}_ship_engine_{1}", Hull::typeToEquipmentString(hullType), module.version + 1);
		case Module::Armor: 
			if (shipType == ShipType::Type::Battleship) return std::format("ship_armor_bb_{0}", module.version + 1);
			else if (shipType == ShipType::Type::Battlecruiser) return std::format("ship_armor_bc_{0}", module.version + 1);
			else if (shipType == ShipType::Type::SuperHeavyBattleship) return "ship_armor_shbb";
			else if (shipType == ShipType::Type::LightCruiser || shipType == ShipType::Type::HeavyCruiser) return std::format("ship_armor_cruiser_{0}", module.version + 1);
			else if (shipType == ShipType::Type::Carrier) return "ship_armor_carrier_deck";
		case Module::LightBattery:
			if (module.subType == Light) return std::format("ship_light_battery_{0}", module.version + 1);
			else if (module.subType == LightCruiser) return std::format("ship_light_medium_battery_{0}", module.version + 1);
			else if (module.subType == AutoLoader) "dp_ship_medium_1";
			else if (module.subType == DualPurpose) return std::format("dp_light_battery_{0}", module.version + 1);
		case Module::HeavyBattery:
			if (shipType == ShipType::Type::HeavyCruiser) return std::format("ship_medium_battery_{0}", module.version + 1);
			else if (shipType == ShipType::Battleship || shipType == ShipType::Type::Battlecruiser) return std::format("ship_heavy_battery_{0}", module.version + 1);
			else if (shipType == ShipType::SuperHeavyBattleship) return "ship_super_heavy_battery_1";
		case Module::SecondaryBattery:
			if (module.subType == DualPurpose) return std::format("dp_ship_secondaries_{0}", module.version + 1);
			else if (module.subType == Secondary) return std::format("ship_secondaries_{0}", module.version + 1);
		case Module::AntiAir: return std::format("ship_anti_air_{0}", module.version + 1);
		case Module::Torpedo:
			if (shipType == ShipType::Type::Submarine) return std::format("ship_torpedo_sub_{0}", module.version + 1);
			else return std::format("ship_torpedo_{0}", module.version + 1);
		case Module::Snorkel: return std::format("ship_sub_snorkel_{0}", module.version + 1);
		case Module::FireControl: return std::format("ship_fire_control_system_{0}", module.version + 1);
		case Module::AntiSubmarine: return std::format("ship_depth_charge_{0}", module.version + 1);
		case Module::Mine:
			if (module.subType == MineLaying) {
				if (shipType == ShipType::Type::Submarine) return "ship_mine_layer_sub";
				else return "ship_mine_layer_1";
			}
			return "ship_mine_sweeper_1";
		case Module::Aircraft:
			if (shipType == ShipType::Type::Carrier) return "ship_deck_space";
			else return std::format("ship_airplane_launcher_{0}", module.version + 1);
		case Module::Fuel: return "ship_extra_fuel_tank";
		case Module::Radar: return std::format("ship_radar_{0}", module.version + 1);
		case Module::Sonar: return std::format("ship_sonar_{0}", module.version + 1);
		case Module::None: return "empty";
		case Module::Last:
			break;
		default:
			break;
		}
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
		default: return "None";
		}
	}

	static std::string versionToString(Version version) {
		switch (version)
		{
		case Module::Basic: return "1";
		case Module::Early: return "2";
		case Module::Improved: return "3";
		case Module::Advanced: return "4";
		case SuperHeavyBattleship: return "Super Heavy";
		default:
			break;
		}
	}

	static std::string customKeyEquipmentFile(ShipType::Type type, ShipVersion::Version version, int index) {
		auto [slotPrefix, newIndex] = getSlotPrefix(type, index, version);

		if (!slotPrefix.empty()) {
			return std::format("{0}_{1}_custom_slot", slotPrefix, newIndex);
		}

		return ""; // ou une valeur par défaut en cas d'entrée inattendue
	}

	static std::tuple<std::string, int> getSlotPrefix(ShipType::Type type, int index, ShipVersion::Version version) {
		switch (type) {
		case ShipType::Destroyer:
			return getDestroyerSlotPrefix(index, version);
		case ShipType::LightCruiser:
			return getCruiserSlotPrefix(index, version);
		case ShipType::HeavyCruiser:
			return getCruiserSlotPrefix(index, version);
		case ShipType::Battlecruiser:
			return getBattleshipSlotPrefix(index, version);
		case ShipType::Battleship:
			return getBattleshipSlotPrefix(index, version);
		case ShipType::SuperHeavyBattleship:
			// TODO: DO SUPERBATTLESHIP
			break;
		case ShipType::Carrier:
			return getCarrierSlotPrefix(index, version);
		case ShipType::Submarine: 
			return getSubmarineSlotPrefix(index, version);
		default:
			return { "", 0 };
		}
	}

	static std::tuple<std::string, int> getDestroyerSlotPrefix(int index, ShipVersion::Version version) {
		std::string slotPrefix = "";
		if (index == 0) {
			slotPrefix = "rear";
			index = index + 1;
		}
		else if (index == 1) {
			slotPrefix = "mid";
		}
		else if (index == 2) {
			if (version == ShipVersion::Early || version == ShipVersion::Basic || version == ShipVersion::Improved) {
				slotPrefix = "front";
				index = index - 1;
			}
			else if (version == ShipVersion::Advanced) {
				slotPrefix = "mid";
			}
		}
		else if (index == 3) {
			slotPrefix = "front";
			index = index - 2;
		}

		return { slotPrefix, index };
	}

	static std::tuple<std::string, int> getCruiserSlotPrefix(int index, ShipVersion::Version version) {
		std::string slotPrefix = "";
		if (index == 0) {
			slotPrefix = "rear";
			index = index + 1;
		}
		else if (index == 1) {
			if (version == ShipVersion::Improved || version == ShipVersion::Advanced) {
				slotPrefix = "rear";
				index++;
			}
			else slotPrefix = "mid";
		}
		else if (index == 2) {
			if (version == ShipVersion::Advanced || version == ShipVersion::Improved) {	
				index--;
			}
			slotPrefix = "mid";
		}
		else if (index == 3) {
			if (version == ShipVersion::Improved || version == ShipVersion::Advanced) {
				slotPrefix = "mid";
				index--;
			}
			else {
				slotPrefix = "front";
				index = index - 2;
			}
		}
		else if (index == 4) {
			slotPrefix = "front";
			index = index - 3;
		}
		return { slotPrefix, index };
	}

	static std::tuple<std::string, int> getBattleshipSlotPrefix(int index, ShipVersion::Version version) {
		std::string slotPrefix = "";
		if (index == 0) {
			slotPrefix = "front";
			index = index + 1;
		}
		else if (index == 1) {
			slotPrefix = "mid";
		}
		else if (index == 2) {
			slotPrefix = "mid";
		}
		else if (index == 3) {
			if (version == ShipVersion::Basic) {
				slotPrefix = "rear";
				index = index - 2;
			}
			else {
				slotPrefix = "mid";
			}
		}
		else if (index == 4) {
			slotPrefix = "rear";
			index = index - 3;
		}
		return { slotPrefix, index };
	}

	static std::tuple<std::string, int> getCarrierSlotPrefix(int index, ShipVersion::Version version) {
		std::string slotPrefix = "";
		if (index == 0) {
			slotPrefix = "front";
			index++;
			return { slotPrefix, index };
		}
		if (((index == 1 && version == ShipVersion::Improved || version == ShipVersion::Advanced)
			|| (index == 2 && version == ShipVersion::Advanced)) && index < 3 ) {
			slotPrefix = "mid";
		}
		return { slotPrefix, index };
	}

	static std::tuple<std::string, int> getSubmarineSlotPrefix(int index, ShipVersion::Version version) {
		std::string slotPrefix = "";
		if (index == 0) {
			slotPrefix = "front";
			index++;
			return { slotPrefix, index };
		}
		else if (index == 1) {
			slotPrefix = "mid";
		}
		else if (index == 2) {
			slotPrefix = "rear";
			index--;
		}
		return { slotPrefix, index };
	}

	static Module generateModule(Type moduleType, ShipType::Type type, ShipVersion::Version version);
	static Module generateNone(Type type);
	static Module generateNone(Type type, SubType subType);
};

