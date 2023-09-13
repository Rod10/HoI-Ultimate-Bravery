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
	Plane(PlaneRole::Role role,
		PlaneType::Type type,
		PlaneVersion::Version version,
		PlaneEngine engine,
		std::unordered_map<PlaneModule::Type, PlaneModule> fixed,
		std::vector<PlaneModule> custom):
	role(role),
	type(type),
	version(version),
	engine(engine),
	fixed(fixed),
	custom(custom) {}

	PlaneRole::Role role;
	PlaneType::Type type;
	PlaneVersion::Version version;
	PlaneEngine engine;
	std::unordered_map<PlaneModule::Type, PlaneModule> fixed;
	std::vector<PlaneModule> custom;

	static Plane generateRandomPlane(PlaneRole::Role role);

	static PlaneType::Type getTypeByRole(PlaneRole::Role role);
	static std::vector<PlaneModule> generateCustomModule(PlaneType::Type planeType, PlaneRole::Role role, PlaneVersion::Version version);
	static std::unordered_map<PlaneModule::Type, PlaneModule> generateFixedModule(PlaneType::Type planeType, PlaneRole::Role role);
};

