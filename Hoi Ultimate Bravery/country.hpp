#pragma once
#include "countriesSettings.hpp"
#include "json.hpp"
#include "hull.hpp"
#include "plane.hpp"
#include "ship.hpp"
#include "shiptype.hpp"
#include "shipversion.hpp"
#include "tank.hpp"
#include "tanktype.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using json = nlohmann::json;

class Country
{
public:
	Country(std::string name,
		std::string tag,
		CountriesSettings coutriesSettings,
		int ideaPosIdea,
		bool major) :
		name(name),
		tag(tag),
		ideaPosIdea(ideaPosIdea),
		coutriesSettings(coutriesSettings),
		tankList(tankList),
		major(major) {}
	static std::vector<Country> generateCountryList();

	std::string name;
	std::string tag;
	int ideaPosIdea;
	CountriesSettings coutriesSettings;
	bool major;

	std::map<TankType::Type, Tank> tankList;
	std::unordered_map<TankType::Type, Stats> newTankStats;
	std::map<Hull::Type, Ship> shipList;
	std::unordered_map<Hull::Type, Stats> newShipStats;
	std::map < PlaneRole::Role, Plane > planeList;
	std::unordered_map < PlaneRole::Role, Stats > newPlaneStats;
};

