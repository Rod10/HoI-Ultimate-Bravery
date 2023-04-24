#pragma once
#include <string>
#include <vector>
#include "Cannon.hpp"
#include "Stats.hpp"

class Turret
{
public :
	enum Type {
		Light,
		Medium,
		Large,
		SuperHeavy,
		Modern,
		Last
	};

	Turret(Turret::Type type, int crew, std::vector<Gun::Size> allowedGun, Stats stats) :
		type(type),
		crew(crew),
		allowedGun(allowedGun),
		stats(stats) {}

	static std::string turretTypeToString(Turret::Type& type) {
		switch (type) {
		default: return "INVALID TYPE";
		case Turret::Type::Light: return "light";
		case Turret::Type::Medium: return "medium";
		case Turret::Type::Large: return "large";
		case Turret::Type::SuperHeavy: return "superHeavy";
		case Turret::Type::Modern: return "modern";
		}
	};

    static Turret generatingRandomTurret(int tankType);

	Turret::Type type;
	int crew;
	std::vector<Gun::Size> allowedGun;
	Stats stats;
};

