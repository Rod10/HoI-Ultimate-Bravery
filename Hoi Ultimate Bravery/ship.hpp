#pragma once
#include "module.hpp"
#include "shiptype.hpp"
#include "shipversion.hpp"
#include "Stats.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "hull.hpp"

class Ship
{
public:

	Ship() {}
	Ship(Hull::Type hull, ShipType::Type type, ShipVersion::Version version, std::unordered_map<Module::Type, Module> customModule, std::unordered_map<Module::Type, Module> fixedModule) :
	hull(hull),
	type(type),
	version(version),
	customModule(customModule),
	fixedModule(fixedModule) {}

	Hull::Type hull;
	ShipType::Type type;
	ShipVersion::Version version;
	std::unordered_map<Module::Type, Module> customModule;
	std::unordered_map<Module::Type, Module> fixedModule;
	Stats stats;

	static ShipVersion::Version getRandomVersion(Hull::Type hull, ShipType::Type type);
	static std::unordered_map<Module::Type, Module> generateFixedModule(ShipType::Type type, ShipVersion::Version version);
	static std::unordered_map<Module::Type, Module> generateCustomModule(ShipType::Type type, ShipVersion::Version version);
	static Ship generateRandomShip(Hull::Type hull);
};

