#pragma once
#include "tanktype.hpp"

#include <iostream>
#include <vector>
class TurretType {
public:
	enum Type {
		Light,
		Medium,
		Large,
		SuperHeavy,
		Modern,
		Last
	};

	static std::string turretTypeToString(Type& type) {
		switch (type) {
		default: return "INVALID TYPE";
		case Type::Light: return "light";
		case Type::Medium: return "medium";
		case Type::Large: return "large";
		case Type::SuperHeavy: return "superHeavy";
		case Type::Modern: return "modern";
		}
	};

	static std::vector<TurretType::Type> getAllowedTurret(TankType::Type& type) {
		std::vector<TurretType::Type> allowedTurret;
		switch (type) {
		case TankType::Type::Light:
			allowedTurret.push_back(TurretType::Type::Light);
			break;
		case TankType::Type::Medium:
			allowedTurret.push_back(TurretType::Type::Light);
			allowedTurret.push_back(TurretType::Type::Medium);
			break;
		case TankType::Type::Heavy:
			allowedTurret.push_back(TurretType::Type::Light);
			allowedTurret.push_back(TurretType::Type::Medium);
			allowedTurret.push_back(TurretType::Type::Large);
			break;
		case TankType::Type::SuperHeavy:
			allowedTurret.push_back(TurretType::Type::Light);
			allowedTurret.push_back(TurretType::Type::Medium);
			allowedTurret.push_back(TurretType::Type::Large);
			allowedTurret.push_back(TurretType::Type::SuperHeavy);
			break;
		case TankType::Type::Modern:
			allowedTurret.push_back(TurretType::Type::Light);
			allowedTurret.push_back(TurretType::Type::Medium);
			allowedTurret.push_back(TurretType::Type::Large);
			break;
		}
		return allowedTurret;
	}
};

