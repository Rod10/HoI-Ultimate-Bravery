#pragma once
#include "armor.hpp"
#include "engine.hpp"
#include "gun.hpp"
#include "role.hpp"
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

	std::vector<int> upgrade = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20 };

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
		TankStats stats,
		Role::Type role,
		std::string name) :
		type(type),
		version(version),
		turret(turret),
		gun(gun),
		specialModules(specialModules),
		suspension(suspension),
		armor(armor),
		engine(engine),
		stats(stats),
		role(role),
		name(name){
		engineLevel = *Utils::select_randomly(upgrade.begin(), upgrade.end());
		armorLevel = *Utils::select_randomly(upgrade.begin(), upgrade.end());
	}

	TankType::Type type;
	Tank::Version version;
	Turret turret;
	Gun gun;
	std::array<SpecialModule, 4> specialModules;
	Suspension suspension;
	Armor armor;
	Engine engine;
	TankStats stats;
	Role::Type role;
	std::string iconName;
	int engineLevel;
	int armorLevel;
	std::string name;

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

	static int tankVersionToInt(Tank::Version& version) {
		switch (version) {
		case Tank::Version::InterWar: return 0;
		case Tank::Version::Basic: return 1;
		case Tank::Version::Improved: return 2;
		case Tank::Version::Advanced: return 3;
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
		if (module == "suspension") return 2;
		if (module == "armor") return 3;
		if (module == "engine") return 4;
	}

	static Tank::Version generatingRandomVersion(TankType::Type type);
	static TankStats getStatsFromVersion(TankType::Type type, Tank::Version version);
	static TankStats generateNewStats(Tank tank);

	static Tank generateRandomTank(TankType::Type type);
};