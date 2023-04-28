#pragma once
#include <string>
#include <vector>

#include "gun.hpp"
#include "special.hpp"
#include "suspension.hpp"
#include "turret.hpp"

struct Tank {
	enum Type {
		Light,
		Medium,
		Heavy,
		SuperHeavy,
		Modern,
		Last
	};

	enum Version {
		InterWar,
		Basic,
		Improved,
		Advanced,
		VLast
	};

	Tank(
		Type type,
		Version version,
		Turret turret,
		Gun gun,
		SpecialModule specialModules[4],
		Suspension suspension,
		Stats stats) :
		type(type),
		version(version),
		turret(turret),
		gun(gun),
		specialModules(),
		suspension(suspension),
		stats(stats){}

	Tank::Type type;
	Tank::Version version;
	Turret turret;
	Gun gun;
	SpecialModule specialModules[4];
	Suspension suspension;
	Stats stats;

	enum Modules {
		Turret,
		Gun,
		Special,
		Chassis,
		Armor,
		Engines
	};

	static std::string tankTypeToString(Tank::Type& type) {
		switch (type) {
		default: return "INVALID TYPE";
		case Tank::Type::Light: return "light";
		case Tank::Type::Medium: return "medium";
		case Tank::Type::Heavy: return "heavy";
		case Tank::Type::SuperHeavy: return "superHeavy";
		case Tank::Type::Modern: return "modern";
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

	static Tank::Type intToTankType(int type) {
		switch (type) {
		default: break;
		case 0: return Tank::Type::Light;
		case 1: return Tank::Type::Medium;
		case 2: return Tank::Type::Heavy;
		case 3: return Tank::Type::SuperHeavy;
		case 4: return Tank::Type::Modern;
		}
	};
	 
	static std::vector<Turret::Type> getAllowedTurret(Tank::Type& type) {
		std::vector<Turret::Type> allowedTurret;
		switch (type) {
		case Tank::Type::Light:
			allowedTurret.push_back(Turret::Type::Light);
			break;
		case Tank::Type::Medium:
			allowedTurret.push_back(Turret::Type::Light);
			allowedTurret.push_back(Turret::Type::Medium);
			break;
		case Tank::Type::Heavy:
			allowedTurret.push_back(Turret::Type::Light);
			allowedTurret.push_back(Turret::Type::Medium);
			allowedTurret.push_back(Turret::Type::Large);
			break;
		case Tank::Type::SuperHeavy:
			allowedTurret.push_back(Turret::Type::Light);
			allowedTurret.push_back(Turret::Type::Medium);
			allowedTurret.push_back(Turret::Type::Large);
			allowedTurret.push_back(Turret::Type::SuperHeavy);
			break;
		case Tank::Type::Modern:
			allowedTurret.push_back(Turret::Type::Light);
			allowedTurret.push_back(Turret::Type::Medium);
			allowedTurret.push_back(Turret::Type::Large);
			break;
		}
		return allowedTurret;
	}
};