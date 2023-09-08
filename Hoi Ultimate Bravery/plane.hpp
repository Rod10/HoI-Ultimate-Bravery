#pragma once
#include "engine.hpp"
#include "planemodule.hpp"
#include "planerole.hpp"
#include "planetype.hpp"
#include "planeversion.hpp"

#include <unordered_map>
#include <time.h>

class Plane
{
public:
	Plane(PlaneRole::Role role,
		PlaneType::Type type,
		PlaneVersion::Version version,
		std::unordered_map<PlaneModule::Type, PlaneModule> fixed,
		std::unordered_map<PlaneModule::Type, PlaneModule> custom):
	role(role),
	type(type),
	version(version),
	fixed(fixed),
	custom(custom) {}

	PlaneRole::Role role;
	PlaneType::Type type;
	PlaneVersion::Version version;
	PlaneEngine engine;
	std::unordered_map<PlaneModule::Type, PlaneModule> fixed;
	std::unordered_map<PlaneModule::Type, PlaneModule> custom;

	static Plane generateRandomPlane(PlaneRole::Role role);
};

