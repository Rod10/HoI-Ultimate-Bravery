#pragma once
#include "planetype.hpp"
#include "planerole.hpp"
#include "planeversion.hpp"
#include "Ressources.hpp"

#include <format>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

class PlaneModule
{
public:
	
	enum Type {
		Gun,
		Bomb,
		Torpedo,
		SpecialModule,
		Armor,
		Fuel,
		Electronics,
		Defense,
		None,
		Last
	};

	enum SubType {
		LMG,
		HMG,
		Cannon,
		BombLocks,
		SmallBombBay,
		AntiTankCannon,
		RocketRail,
		MediumBombBay,
		LargeBombBay,
		TorpedoPlane,
		Missile,
		DeminingCoil,
		DiveBrakes,
		Floats,
		FlyingBoat,
		ArmorPlate,
		NonStrategicMaterial,
		AirAirRadar,
		AirGroundRadar,
		BombSight,
		RadioNavigation,
		LightMGDefense,
		HeavyMGDefense,
		CannonDefense,
		DropTanks, 
		ExtraFuelTanks,
		SelfSealingTanks
	};

	enum Version {
		Early,
		Basic,
		Improved,
		Advanced,
	};

	PlaneModule() {}
	PlaneModule(Type type) :
	type(type) {}
	PlaneModule(Type type,
		SubType subType,
		Version version) :
		type(type),
		subType(subType),
		version(version) {}
	PlaneModule(Type type,
		SubType subType,
		Version version,
		int number) :
		type(type),
		subType(subType),
		version(version),
		number(number) {}

	PlaneModule::Type type;
	PlaneModule::SubType subType;
	PlaneModule::Version version;
	int number;

	static std::string typeToFileString(Type type) {
		switch (type)
		{
		case PlaneModule::Gun: return "Gun";
		case PlaneModule::Bomb: return "Bomb";
		case PlaneModule::Torpedo: return "Torpedo";
		case PlaneModule::SpecialModule: return "SpecialModule";
		case PlaneModule::Armor: return "Armor";
		case PlaneModule::Fuel: return "Fuel";
		case PlaneModule::Electronics: return "Electronics";
		case PlaneModule::Defense: return "Defense";
		default:
			break;
		}
	}

	static SubType stringToSubType(std::string subType) {
		if (subType == "lmg") return LMG;
		if (subType == "hmg") return HMG;
		if (subType == "cannon") return Cannon;
		if (subType == "bombLocks") return BombLocks;
		if (subType == "smallBombBay") return SmallBombBay;
		if (subType == "mediumBombBay") return MediumBombBay;
		if (subType == "largeBombBay") return LargeBombBay;
		if (subType == "antiTankCannon") return AntiTankCannon;
		if (subType == "rocketRails") return RocketRail;
		if (subType == "torpedo") return TorpedoPlane;
		if (subType == "missile") return Missile;
		if (subType == "deminingCoil") return DeminingCoil;
		if (subType == "diveBrakes") return DiveBrakes;
		if (subType == "floats") return Floats;
		if (subType == "flyingBoat") return FlyingBoat;
		if (subType == "amorPlate") return ArmorPlate;
		if (subType == "nonStrategicMaterial") return NonStrategicMaterial;
		if (subType == "airAirRadar") return AirAirRadar;
		if (subType == "airGroundRadar") return AirGroundRadar;
		if (subType == "bombSight") return BombSight;
		if (subType == "radioNaviagation") return RadioNavigation;
	}

	static std::string versionToString(Version version) {
		switch (version)
		{
		case PlaneModule::Early: return "early";
		case PlaneModule::Basic: return "basic";
		case PlaneModule::Improved: return "improved";
		case PlaneModule::Advanced: return "advanced";
		default:
			break;
		}
	}

	static Version stringToVersion(std::string version) {
		if (version == "early") return Early;
		if (version == "basic") return Basic;
		if (version == "improved") return Improved;
		if (version == "advanced") return Advanced;
	}

	static std::string subTypeToString(SubType subType) {
		switch (subType)
		{
		case PlaneModule::LMG: return "lmg";
		case PlaneModule::HMG: return "hmg";
		case PlaneModule::Cannon: return "cannon";
		case PlaneModule::BombLocks: return "bombLocks";
		case PlaneModule::SmallBombBay: return "smallBombBay";
		case PlaneModule::AntiTankCannon: return "antiTankCannon";
		case PlaneModule::RocketRail: return "rocketRails";
		case PlaneModule::MediumBombBay: return "mediumBombBay";
		case PlaneModule::LargeBombBay: return "largeBombBay";
		case PlaneModule::TorpedoPlane: return "torpedo";
		case PlaneModule::Missile: return "missile";
		case PlaneModule::DeminingCoil: return "deminingCoil";
		case PlaneModule::DiveBrakes: return "diveBrakes";
		case PlaneModule::Floats: return "floats";
		case PlaneModule::FlyingBoat: return "flyingBoat";
		case PlaneModule::ArmorPlate: return "armorPlate";
		case PlaneModule::NonStrategicMaterial: return "nonStrategicMaterial";
		case PlaneModule::AirAirRadar: return "";
		case PlaneModule::AirGroundRadar: return "airGroundRadar";
		case PlaneModule::BombSight: return "bombSight";
		case PlaneModule::RadioNavigation: return "radioNaviagation";
		default: break;
		}
	}

	static std::string typeToImagesString(PlaneType::Type planeType, SubType subType, Version version, int number) {
		switch (subType)
		{
		case PlaneModule::LMG: return std::format("{0}_{1}", "Airplane_light_mg", number);
		case PlaneModule::HMG: return std::format("{0}_{1}", "Airplane_light_mg", number);
		case PlaneModule::Cannon:
			if (version == Version::Early) {
				return std::format("{0}_{1}", "Airplane_cannon_1", number);
			}
			return std::format("{0}_{1}", "Airplane_cannon_2", number);
		case PlaneModule::BombLocks: return "Airplane_bomb_lock";
		case PlaneModule::SmallBombBay: return "Airplane_small_bomb_bay";
		case PlaneModule::AntiTankCannon:
			if (version == Version::Early) {
				return "Airplane_tank_buster_1";
			}
			return "Airplane_tank_buster_2";
		case PlaneModule::RocketRail: return "Airplane_rocket_rail";
		case PlaneModule::MediumBombBay: return "Airplane_medium_bomb_bay";
		case PlaneModule::LargeBombBay: return "Airplane_large_bomb_bay";
		case PlaneModule::TorpedoPlane: return "Airplane_torpedo";
		case PlaneModule::Missile: return "Airplane_anti_ship_missile";
		case PlaneModule::DeminingCoil: return "Airplane_demining_coil";
		case PlaneModule::DiveBrakes: return "Airplane_dive_brakes";
		case PlaneModule::Floats: return "Airplane_floats";
		case PlaneModule::FlyingBoat: return "Airplane_flying_boat";
		case PlaneModule::ArmorPlate: return std::format("Airplane_armor_plate_{0}", PlaneType::typeToString(planeType));
		case PlaneModule::NonStrategicMaterial: return "Airplane_non_strategic_materials";
		case PlaneModule::AirAirRadar: return std::format("Airplane_air_air_radar_{0}", version + 1);
		case PlaneModule::AirGroundRadar: return std::format("Airplane_air_ground_radar_{0}", version + 1);
		case PlaneModule::BombSight: return std::format("Airplane_bomb_sights_{0}", version + 1);
		case PlaneModule::RadioNavigation: return std::format("Airplane_radio_navigation_{0}", version + 1);
		default:
			break;
		}
	}

	static std::string moduleToEquipmentStringValue(PlaneModule module, PlaneType::Type planeType) {
		switch (module.subType)
		{
		case PlaneModule::LMG: return std::format("light_mg_{0}x", module.number);
		case PlaneModule::HMG: return std::format("heavy_mg_{0}x", module.number);
		case PlaneModule::Cannon: return std::format("aircraft_cannon_{0}_{1}x", module.version + 1, module.number);
		case PlaneModule::BombLocks: return "bomb_locks";
		case PlaneModule::SmallBombBay: return "small_bomb_bay";
		case PlaneModule::AntiTankCannon: return std::format("tank_buster_{0}", module.version + 1);
		case PlaneModule::RocketRail: return "rocket_rails";
		case PlaneModule::MediumBombBay: return "medium_bomb_bay";
		case PlaneModule::LargeBombBay: return "large_bomb_bay";
		case PlaneModule::TorpedoPlane: return "torpedo_mounting";
		case PlaneModule::Missile: return "guided_anti_ship_missile";
		case PlaneModule::DeminingCoil: return "demining_coil";
		case PlaneModule::DiveBrakes: return std::format("dive_brakes_{0}", PlaneType::typeToString(planeType));
		case PlaneModule::Floats: return "floats";
		case PlaneModule::FlyingBoat: return std::format("flying_boat_{0}", PlaneType::typeToString(planeType));
		case PlaneModule::ArmorPlate: return std::format("armor_plate_{0}", PlaneType::typeToString(planeType));
		case PlaneModule::NonStrategicMaterial: return std::format("non_strategic_materials_{0}", PlaneType::typeToString(planeType));
		case PlaneModule::AirAirRadar:return std::format("air_air_radar_{0}", module.version + 1);
		case PlaneModule::AirGroundRadar:return std::format("air_ground_radar_{0}", module.version + 1);
		case PlaneModule::BombSight: return std::format("bomb_sights_{0}", module.version + 1);
		case PlaneModule::RadioNavigation: return std::format("radio_navigation_{0}", module.version + 1);
		case PlaneModule::LightMGDefense: return std::format("lmg_defense_turret{0}", module.number == 2 ? "2x" : "");
		case PlaneModule::HeavyMGDefense: return std::format("hmg_defense_turret{0}", module.number == 2 ? "2x" : "");
		case PlaneModule::CannonDefense: return std::format("cannon_defense_turret{0}", module.number == 2 ? "2x" : "");
		case PlaneModule::DropTanks: return "drop_tanks";
		case PlaneModule::ExtraFuelTanks: return std::format("fuel_tanks_{0}", PlaneType::typeToString(planeType));
		case PlaneModule::SelfSealingTanks: return std::format("self_sealing_fuel_tanks_{0}", PlaneType::typeToString(planeType));
			break;
		default:
			break;
		}
	}

	static PlaneModule generateRandom(PlaneType::Type planeType, PlaneRole::Role role, Type type);
	static PlaneModule generateNone(Type type);
};

