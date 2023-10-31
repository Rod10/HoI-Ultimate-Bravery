#pragma once
#include "engine.hpp"
#include "planemodule.hpp"
#include "planerole.hpp"
#include "planetype.hpp"
#include "planeversion.hpp"

#include <time.h>
#include <vector>

class Plane
{
public:
	Plane() {};
	Plane(PlaneRole::Role role,
		PlaneType::Type type,
		PlaneVersion::Version version,
		PlaneEngine engine,
		std::unordered_map<PlaneModule::Type, PlaneModule> special,
		std::vector<PlaneModule> fixed):
	role(role),
	type(type),
	version(version),
	engine(engine),
	special(special),
	fixed(fixed) {}

	PlaneRole::Role role;
	PlaneType::Type type;
	PlaneVersion::Version version;
	PlaneEngine engine;
	std::unordered_map<PlaneModule::Type, PlaneModule> special;
	std::vector<PlaneModule> fixed;
	std::string iconName;

	static Plane generateRandomPlane(PlaneRole::Role role);

	static PlaneType::Type getTypeByRole(PlaneRole::Role role);
	static std::vector<PlaneModule> generateFixedModule(PlaneType::Type planeType, PlaneRole::Role role, PlaneVersion::Version version);
	static std::unordered_map<PlaneModule::Type, PlaneModule> generateSpecialModule(PlaneType::Type planeType, PlaneRole::Role role);
};

