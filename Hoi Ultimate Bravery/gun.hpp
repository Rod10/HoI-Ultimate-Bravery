#pragma once
#include <iostream>

#include "Stats.hpp"

class Gun
{
public:
	enum Category {
		Cannon,
		Flamethrower,
		FastFiringAntiGround,
		AntiTank,
		AntiInfantry,
		AntiAir,
		Last
	};

	enum Size {
		Small,
		Medium,
		Large,
		BFG
	};

	enum Type {
		Basic,
		Improved,
		Advanced
	};

	enum Name {
		SmallCannon,
		MediumCannon,
		HeavyCannon,
		SuperHeavyCannon,
		FT,
		HMG,
		AutomaticCannon,
		HighVelocity,
		CloseSupportGun,
		MediumHowitzer,
		RockectLauncher,
		HeavyHowitzer,
		AntiAirGun
	};

	Gun() {};

	Gun(Gun::Category category,
		Gun::Name name,
		Gun::Size size,
		std::map<Gun::Type, Stats> statsByType) :
		category(category),
		name(name),
		size(size),
		statsByType(statsByType){}

	Gun(Gun::Category category,
		Gun::Name name,
		Gun::Size size,
		Stats stats) :
		category(category),
		name(name),
		size(size),
		stats(stats){}

	static std::string gunCategoryToString(Gun::Category& category) {
		switch (category) {
		default: return "INVALID CATEGORY";
		case Gun::Category::Cannon: return "cannon";
		case Gun::Category::Flamethrower: return "flamethrower";
		case Gun::Category::FastFiringAntiGround: return "fastFiringAntiGround";
		case Gun::Category::AntiTank: return "antiTank";
		case Gun::Category::AntiInfantry: return "antiInfantry";
		case Gun::Category::AntiAir: return "antiAir";
		}
	}

	static std::string gunSizeToString(Gun::Size& size) {
		switch (size)
		{
		default: return "INVALID SIZE";
		case Gun::Size::Small: return "small";
		case Gun::Size::Medium: return "medium";
		case Gun::Size::Large: return "large";
		case Gun::Size::BFG: return "bfg";
		}
	}

	static int typeStringToInt(std::string& type) {
		if (type == "basic") {
			return 0;
		}
		else if (type == "improved") {
			return 1;
		}
		else if (type == "advanced") {
			return 2;
		}
	}

	static Gun::Type stringToGunType(std::string& type) {
		switch (typeStringToInt(type))
		{
		default: break;
		case 0: return Gun::Type::Basic;
		case 1: return Gun::Type::Improved;
		case 2: return Gun::Type::Advanced;
		}
	}

	static int sizeStringToInt(std::string size) {
		if (size == "small") {
			return 0;
		}
		else if (size == "medium") {
			return 1;
		}
		else if (size == "large") {
			return 2;
		}
		else if (size == "bfg") {
			return 3;
		}
	}

	static Gun::Size stringToGunSize(std::string& size) {
		switch (sizeStringToInt(size))
		{
		default: break;
		case 0: return Gun::Size::Small;
		case 1: return Gun::Size::Medium;
		case 2: return Gun::Size::Large;
		case 3: return Gun::Size::BFG;
		}
	}


	static int stringNameToInt(std::string& name) {
		if (name == "smallCannon") {
			return 0;
		}
		else if (name == "mediumCannon") {
			return 1;
		}
		else if (name == "heavyCannon") {
			return 2;
		}
		else if (name == "superHeavyCannon") {
			return 3;
		}
		else if (name == "flamethrower") {
			return 4;
		}
		else if (name == "hmg") {
			return 5;
		}
		else if (name == "automaticCannon") {
			return 6;
		}
		else if (name == "highVelocitySmall" || name == "highVelocityMedium" || name == "highVelocityLarge") {
			return 7;
		}
		else if (name == "closeSupportGun") {
			return 8;
		}
		else if (name == "mediumHowitzer") {
			return 9;
		}
		else if (name == "rocketLauncher") {
			return 10;
		}
		else if (name == "heavyHowitzer") {
			return 11;
		}
		else if (name == "antiAir") {
			return 12;
		}
	}

	static Gun::Name stringNameToGunName(std::string& name) {
		switch (stringNameToInt(name))
		{
		default: break;		
		case 0: return Gun::Name::SmallCannon;
		case 1: return Gun::Name::MediumCannon;
		case 2: return Gun::Name::HeavyCannon;
		case 3: return Gun::Name::SuperHeavyCannon;
		case 4: return Gun::Name::FT;
		case 5: return Gun::Name::HMG;
		case 6: return Gun::Name::AutomaticCannon;
		case 7: return Gun::Name::HighVelocity;
		case 8: return Gun::Name::CloseSupportGun;
		case 9: return Gun::Name::MediumHowitzer;
		case 10: return Gun::Name::RockectLauncher;
		case 11: return Gun::Name::HeavyHowitzer;
		case 12: return Gun::Name::AntiAirGun;
		}
	}

	static std::vector<Gun> generateGunList();

	Gun::Category category;
	Gun::Size size;
	Gun::Name name;
	std::map<Type, Stats> statsByType;
	Stats stats;
	std::vector<std::string> roleAllowed;
};

