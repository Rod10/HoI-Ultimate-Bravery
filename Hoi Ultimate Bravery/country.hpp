#pragma once
#include "countriesSettings.hpp"
#include "division.hpp"
#include "json.hpp"
#include "hull.hpp"
#include "plane.hpp"
#include "ship.hpp"
#include "shiptype.hpp"
#include "shipversion.hpp"
#include "tank.hpp"
#include "tankstats.hpp"
#include "tanktype.hpp"
#include "unittype.hpp"

#include <any>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
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
		major(major) {

		// Insertion of UnitType
		units.insert(std::pair<UnitType::Type, std::map<Hull::Type, std::vector<std::any>>>(
			UnitType::Ship, {
				{Hull::Type::Destroyer, {}},
				{Hull::Type::Cruiser, {}},
				{Hull::Type::HeavyShip, {}},
				{Hull::Type::Carrier, {}},
				{Hull::Type::Submarine, {}},
			}
		));
		units.insert(std::pair<UnitType::Type, std::map<TankType::Type, std::vector<std::any>>>(
			UnitType::Tank, {
				{TankType::Light, {}},
				{TankType::Medium, {}},
				{TankType::Heavy, {}},
				{TankType::SuperHeavy, {}},
				{TankType::Modern, {}},
			}
		));
		units.insert(std::pair<UnitType::Type, std::map<PlaneRole::Role, std::vector<std::any>>>(
			UnitType::Plane, {
				{PlaneRole::Fighter, {}},
				{PlaneRole::CAS, {}},
				{PlaneRole::NavalBombing, {}},
				{PlaneRole::TacticalBombing, {}},
				{PlaneRole::StrategicBombing, {}},
			}
		));
		units.insert(std::pair<UnitType::Type, std::vector<Division>>(
			{UnitType::Division, {}}
		));

		imports.insert(std::pair<UnitType::Type, std::map<Hull::Type, bool>>(
			UnitType::Ship, {
				{Hull::Type::Destroyer, false},
				{Hull::Type::Cruiser, false},
				{Hull::Type::HeavyShip, false},
				{Hull::Type::Carrier, false},
				{Hull::Type::Submarine, false},
			}
		));
		imports.insert(std::pair<UnitType::Type, std::map<TankType::Type, bool>>(
			UnitType::Tank, {
				{TankType::Light, false},
				{TankType::Medium, false},
				{TankType::Heavy, false},
				{TankType::SuperHeavy, false},
				{TankType::Modern, false},
			}
		));
		imports.insert(std::pair<UnitType::Type, std::map<PlaneRole::Role, bool>>(
			UnitType::Plane, {
				{PlaneRole::Fighter, false},
				{PlaneRole::CAS, false},
				{PlaneRole::NavalBombing, false},
				{PlaneRole::TacticalBombing, false},
				{PlaneRole::StrategicBombing, false},
			}
		));
		imports.insert(std::pair<UnitType::Type, std::vector<bool>>(
			{ UnitType::Division, {false} }
		));
	}
	static std::vector<Country> generateCountryList();
	void setNewUnits(UnitType::Type unitType, Ship unit);
	void setNewUnits(UnitType::Type unitType, Tank unit);
	void setNewUnits(UnitType::Type unitType, Plane unit);
	void setNewUnits(UnitType::Type unitType, Division unit);
	void setNewUnits(UnitType::Type unitType, Division unit, int column);
	Ship getShipByHull(int type);
	std::tuple<Tank, TankStats> getTankByType(int type);
	Plane getPlaneByRole(int type);
	Division* getDivisionByIndex(int column);

	std::map<Hull::Type, std::vector<std::any>>& getHullList();
	std::map<TankType::Type, std::vector<std::any>>& getTankList();
	std::map<PlaneRole::Role, std::vector<std::any>>& getPlaneList();

	int getShipHullListSize(int type);
	int getTankTypeListSize(int type);
	int getPlaneRoleListSize(int type);
	int getDivisionListSize();

	void setImport(UnitType::Type unitType, Hull::Type hull, bool value);
	void setImport(UnitType::Type unitType, TankType::Type type, bool value);
	void setImport(UnitType::Type unitType, PlaneRole::Role role, bool value);
	void setImport(UnitType::Type unitType, int index, bool value);
	bool getImport(UnitType::Type unitType, Hull::Type hull);
	bool getImport(UnitType::Type unitType, TankType::Type type);
	bool getImport(UnitType::Type unitType, PlaneRole::Role role);
	bool getImport(UnitType::Type unitType, int number);

	bool checkIfListIsEmpty(UnitType::Type unitType);

	std::string name;
	std::string tag;
	int ideaPosIdea;
	CountriesSettings coutriesSettings;
	bool major;

	std::map<UnitType::Type, std::any> units;
	std::map<UnitType::Type, std::any> imports;
};

class CountryList {
protected:
	CountryList(std::vector<Country> list) :
		list_(list) {}
	static CountryList* countryList_;
	std::vector<Country> list_;
public:
	CountryList(CountryList& other) = delete;
	void operator=(const CountryList&) = delete;
	static CountryList* GetInstance();
	std::vector<Country>* getList();
};