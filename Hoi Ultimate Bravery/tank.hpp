#pragma once
#include "armor.hpp"
#include "engine.hpp"
#include "gun.hpp"
#include "special.hpp"
#include "suspension.hpp"
#include "tanktype.hpp"
#include "texture.hpp"
#include "turret.hpp"
#include "turrettype.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Tank {
public:
	enum Version {
		InterWar,
		Basic,
		Improved,
		Advanced,
		VLast
	};

	Tank();
	Tank(
		TankType::Type type,
		Version version,
		Turret turret,
		Gun gun,
		std::array<SpecialModule, 4> specialModules,
		Suspension suspension,
		Armor armor,
		Engine engine,
		Stats stats) :
		type(type),
		version(version),
		turret(turret),
		gun(gun),
		specialModules(specialModules),
		suspension(suspension),
		armor(armor),
		engine(engine),
		stats(stats) {
		engineLevel = rand() % 20;
		armorLevel = rand() % 20;
	}

	TankType::Type type;
	Tank::Version version;
	Turret turret;
	Gun gun;
	std::array<SpecialModule, 4> specialModules;
	Suspension suspension;
	Armor armor;
	Engine engine;
	Stats stats;
	int engineLevel;
	int armorLevel;

	/*enum Modules {
		Turret, 
		Gun,
		Special,
		Chassis,
		Armor,
		Engines
	};*/

	static std::string tankTypeToString(TankType::Type& type) {
		switch (type) {
		default: return "INVALID TYPE";
		case TankType::Type::Light: return "light";
		case TankType::Type::Medium: return "medium";
		case TankType::Type::Heavy: return "heavy";
		case TankType::Type::SuperHeavy: return "superHeavy";
		case TankType::Type::Modern: return "modern";
		}
	};

	static std::string tankVersionToString(Tank::Version& version) {
		switch (version) {
		default: return "INVALID VERSION";
		case Tank::Version::InterWar: return "interWar";
		case Tank::Version::Basic: return "basic";
		case Tank::Version::Improved: return "improved";
		case Tank::Version::Advanced: return "advanced";
		}
	}
	
	static int tankVersionStringToInt(std::string version) {
		if (version == "interWar") return 0;
		else if (version == "basic") return 1;
		else if (version == "improved") return 2;
		else if (version == "advanced") return 3;
	}

	static Tank::Version tankVersionStringToVersion(std::string& version) {
		switch (tankVersionStringToInt(version)) {
		case 0: return Tank::Version::InterWar;
		case 1: return Tank::Version::Basic;
		case 2: return Tank::Version::Improved;
		case 3: return Tank::Version::Advanced;
		}
	}

	static int tankModuleToInt(std::string module) {
		if (module == "gun") return 0;
		if (module == "turret") return 1;
	}

	static Tank::Version generatingRandomVersion(TankType::Type type);
	static Stats getStatsFromVersion(TankType::Type type, Tank::Version version);

	static Tank generateRandomTank();
	static Tank generateRandomTank(TankType::Type type);
};