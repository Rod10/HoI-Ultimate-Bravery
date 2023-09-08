#pragma once
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
	Country() {};
	Country(std::string name,
		std::string tag,
		int countryPosIdea,
		int linesToDeleteStart,
		int linesToDeleteEnd,
		int ideaPosIdea) :
		name(name),
		tag(tag),
		countryPosIdea(countryPosIdea),
		linesToDeleteStart(linesToDeleteStart),
		linesToDeleteEnd(linesToDeleteEnd),
		ideaPosIdea(ideaPosIdea),
		tankList(tankList) {
		lineToDeleteCount = linesToDeleteEnd - linesToDeleteStart;
	}
	static std::vector<Country> generateCountryList();

	std::string name;
	std::string tag;
	int countryPosIdea;
	int linesToDeleteStart;
	int linesToDeleteEnd;
	int lineToDeleteCount;
	int ideaPosIdea;
	std::map<TankType::Type, Tank> tankList;
	std::unordered_map<TankType::Type, Stats> newTankStats;
	std::map<Hull::Type, Ship> shipList;
	std::unordered_map<Hull::Type, Stats> newShipStats;
	std::map < PlaneRole::Role, Plane > planeList;
	std::map < PlaneRole::Role, Stats > newPlaneStats;
};

