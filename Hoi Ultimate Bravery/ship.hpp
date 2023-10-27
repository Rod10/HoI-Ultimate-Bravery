#pragma once
#include "hull.hpp"
#include "module.hpp"
#include "shiptype.hpp"
#include "shipversion.hpp"
#include "Stats.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class Ship
{
public:

	Ship() {}
	Ship(Hull::Type hull, 
		ShipType::Type type,
		ShipVersion::Version version,
		std::vector<Module> customModule,
		std::vector<Module> fixedModule) :
	hull(hull),
	type(type),
	version(version),
	customModule(customModule),
	fixedModule(fixedModule) {}

	Hull::Type hull;
	ShipType::Type type;
	ShipVersion::Version version;
	std::vector<Module> customModule;
	std::vector<Module> fixedModule;
	Stats stats;
	std::string iconName;

	static ShipVersion::Version getRandomVersion(Hull::Type hull, ShipType::Type type);
	static std::vector<Module> generateFixedModule(ShipType::Type type, ShipVersion::Version version);
	static std::vector<Module> generateCustomModule(ShipType::Type type, ShipVersion::Version version);
	static Ship generateRandomShip(Hull::Type hull);
};

