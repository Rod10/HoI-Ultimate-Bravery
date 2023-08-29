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

	Hull hull;
	ShipType::Type type;
	ShipVersion::Version version;
	std::map<Module::Type, Module> customModule;
	std::map<Module::Type, Module> fixedModule;
	Stats stats;

	static ShipVersion::Version getRandomVersion(ShipType::Type type);
	static std::map<Module::Type, Module> generateFixedModule(ShipType::Type type, ShipVersion::Version version);
	// TODO pass lamda to get random type
	static std::map<Module::Type, Module> generateCustomModule(ShipType::Type type, ShipVersion::Version version);
	static Ship generateRandomShip(Hull::Type hull);
};

