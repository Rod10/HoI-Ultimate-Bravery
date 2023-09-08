#pragma once
#include "planetype.hpp"
#include "planerole.hpp"
#include "Ressources.hpp"

#include <fstream>
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
		Electronic,
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
		RocketRail
	};

	enum Version {
		Early,
		Basic,
		Improved,
		Advanced,
	};

	PlaneModule() {}
	PlaneModule(int i) :
	number(i) {}
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
		case PlaneModule::Electronic: return "Electronic";
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
		if (subType == "antiTankCannon") return AntiTankCannon;
		if (subType == "rocketRail") return RocketRail;
	}

	static Version stringToVersion(std::string version) {
		if (version == "early") return Early;
		if (version == "basic") return Basic;
		if (version == "improved") return Improved;
		if (version == "advanced") return Advanced;
	}

	static PlaneModule generateRandom(PlaneType::Type planeType, PlaneRole::Role role, Type type);
	static PlaneModule generateNone(int i);
};

