#pragma once
#include <iostream>

#include "Stats.hpp"

class Gun
{
public:
	enum Category {
		Cannon,
		/*Flamethrower,
		FastFiringAntiGround,
		AntiTank,
		AntiInfantry,
		AntiAir,*/
		Last
	};

	enum Size {
		Small,
		Medium,
		Large,
		BFG,
	};

	enum Type {
		Basic,
		Improved,
		Advanced
	};

	Gun(Gun::Category category,
		Gun::Size size,
		std::map<Gun::Type, Stats> statsByType) :
		category(category),
		size(size),
		statsByType(statsByType){}

	static std::string gunCategoryToString(Gun::Category& category) {
		switch (category) {
		default: return "INVALID CATEGORY";
		case Gun::Category::Cannon: return "cannon";
		//case Gun::Category::Flamethrower: return "flamethrower";
		//case Gun::Category::FastFiringAntiGround: return "fastFiringAntiGround";
		//case Gun::Category::AntiTank: return "antiTank";
		//case Gun::Category::AntiInfantry: return "antiInfantry";
		//case Gun::Category::AntiAir: return "antiAir";
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

	Gun::Category category;
	Gun::Size size;
	std::map<Type, Stats> statsByType;
	std::vector<std::string> roleAllowed;
};

