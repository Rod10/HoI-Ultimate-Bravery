#pragma once
#include "gunsize.hpp"
#include "stats.hpp"
#include "turret.hpp"
#include "utils.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>

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
		HighVelocitySmall,
		HighVelocityMedium,
		HighVelocityLarge,
		CloseSupportGun,
		MediumHowitzer,
		RocketLauncher,
		HeavyHowitzer,
		AntiAirSmall,
		AntiAirMedium,
		LastName
	};

	Gun() {};

	Gun(Gun::Category category,
		Gun::Name name,
		GunSize::Size size,
		std::map<Gun::Type, Stats> statsByType) :
		category(category),
		name(name),
		size(size),
		statsByType(statsByType){}

	Gun(Gun::Category category,
		Gun::Name name,
		GunSize::Size size,
		Gun::Type type,
		Stats stats) :
		category(category),
		name(name),
		size(size),
		stats(stats),
		type(type) {}

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

	static std::string gunCategoryToString(const Gun::Category& category) {
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

	static std::string gunSizeToString(GunSize::Size& size) {
		switch (size)
		{
		default: return "INVALID SIZE";
		case GunSize::Size::Small: return "small";
		case GunSize::Size::Medium: return "medium";
		case GunSize::Size::Large: return "large";
		case GunSize::Size::BFG: return "bfg";
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

	static std::string typeToString(Type& type) {
		switch (type)
		{
		default: return "INVALID TYPE";
		case Basic: return "basic";
		case Improved: return "improved";
		case Advanced: return "advanced";
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

	static GunSize::Size stringToGunSize(std::string& size) {
		switch (sizeStringToInt(size))
		{
		default: break;
		case 0: return GunSize::Size::Small;
		case 1: return GunSize::Size::Medium;
		case 2: return GunSize::Size::Large;
		case 3: return GunSize::Size::BFG;
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
		else if (name == "highVelocitySmall") {
			return 7;
		}
		else if (name == "highVelocityMedium") {
			return 8;
		}
		else if (name == "highVelocityLarge") {
			return 9;
		}
		else if (name == "closeSupportGun") {
			return 10;
		}
		else if (name == "mediumHowitzer") {
			return 11;
		}
		else if (name == "rocketLauncher") {
			return 12;
		}
		else if (name == "heavyHowitzer") {
			return 13;
		}
		else if (name == "antiAirSmall") {
			return 14;
		}
		else if (name == "antiAirMedium") {
			return 15;
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
		case 7: return Gun::Name::HighVelocitySmall;
		case 8: return Gun::Name::HighVelocityMedium;
		case 9: return Gun::Name::HighVelocityLarge;
		case 10: return Gun::Name::CloseSupportGun;
		case 11: return Gun::Name::MediumHowitzer;
		case 12: return Gun::Name::RocketLauncher;
		case 13: return Gun::Name::HeavyHowitzer;
		case 14: return Gun::Name::AntiAirSmall;
		case 15: return Gun::Name::AntiAirMedium;
		}
	}

	static std::string gunNameToString(Gun::Name name) {
		switch (name)
		{
		default: break;
		case Gun::Name::SmallCannon: return "smallCannon";
		case Gun::Name::MediumCannon: return "mediumCannon";
		case Gun::Name::HeavyCannon: return "heavyCannon";
		case Gun::Name::SuperHeavyCannon: return "superHeavyCannon";
		case Gun::Name::FT: return "flamethrower";
		case Gun::Name::HMG: return "hmg";
		case Gun::Name::AutomaticCannon: return "automaticCannon";
		case Gun::Name::HighVelocitySmall: return "highVelocitySmall";
		case Gun::Name::HighVelocityMedium: return "highVelocityMedium";
		case Gun::Name::HighVelocityLarge: return "highVelocityLarge";
		case Gun::Name::CloseSupportGun: return "closeSupportGun";
		case Gun::Name::MediumHowitzer: return "mediumHowitzer";
		case Gun::Name::RocketLauncher: return "rocketLauncher";
		case Gun::Name::HeavyHowitzer: return "heavyHowitzer";
		case Gun::Name::AntiAirSmall: return "antiAirSmall";
		case Gun::Name::AntiAirMedium: return "antiAirMedium";
		}
	}

	static std::map<Gun::Category, std::vector<Gun>> generateGunList();
	static Gun generateRandomGun(std::vector<GunSize::Size> turret);
	static std::string getLongestTextByCate(Gun::Category category);

	Gun::Category category;
	GunSize::Size size;
	Gun::Type type;
	Gun::Name name;
	std::map<Type, Stats> statsByType;
	Stats stats;
	std::vector<std::string> roleAllowed;
};
