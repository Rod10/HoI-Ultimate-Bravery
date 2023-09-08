#include "plane.hpp"

Plane Plane::generateRandomPlane(PlaneRole::Role role)
{
	srand(time(0));

	PlaneType::Type type;
	if (role == PlaneRole::CAS || role == PlaneRole::Fighter) {
		type = PlaneType::Small;
	}
	else if (role == PlaneRole::TacticalBombing) {
		type = PlaneType::Medium;
	}
	else if (role == PlaneRole::StrategicBombing) {
		type = PlaneType::Large;
	}
	else if (role == PlaneRole::NavalBombing) {
		type = static_cast<PlaneType::Type>(rand() % PlaneType::Last);
	}

	PlaneVersion::Version version = PlaneVersion::generateRandom(type);
	PlaneEngine engine = PlaneEngine::generateRandom(type);
	std::unordered_map<PlaneModule::Type, PlaneModule> fixed = generateFixedModule(type, role);
	std::unordered_map<PlaneModule::Type, PlaneModule> custom = generateCustomModule(type, role, version);

	return Plane(role, type, version, fixed, custom);
}

std::unordered_map<PlaneModule::Type, PlaneModule> generateFixedModule(PlaneType::Type planeType, PlaneRole::Role role) {
	std::unordered_map<PlaneModule::Type, PlaneModule> fixedModules;
	auto fun = [](std::vector<PlaneModule::Type> typeList) {
		srand(time(0));
		return typeList[static_cast<PlaneModule::Type>(rand() % typeList.size())];
	};
	auto module = fun({ PlaneModule::Type::Armor, PlaneModule::Type::Defense, PlaneModule::Type::Electronic, PlaneModule::Type::Fuel, PlaneModule::Type::SpecialModule });
	fixedModules.insert(std::pair<PlaneModule::Type, PlaneModule>(module, PlaneModule::generateRandom(planeType, role, module)));
	module = fun({ PlaneModule::Type::Armor, PlaneModule::Type::Defense, PlaneModule::Type::Electronic, PlaneModule::Type::Fuel, PlaneModule::Type::SpecialModule });
	fixedModules.insert(std::pair<PlaneModule::Type, PlaneModule>(module, PlaneModule::generateRandom(planeType, role, module)));
	module = fun({ PlaneModule::Type::Armor, PlaneModule::Type::Defense, PlaneModule::Type::Electronic, PlaneModule::Type::Fuel, PlaneModule::Type::SpecialModule });
	fixedModules.insert(std::pair<PlaneModule::Type, PlaneModule>(module, PlaneModule::generateRandom(planeType, role, module)));

	return fixedModules;
}
std::unordered_map<PlaneModule::Type, PlaneModule> generateCustomModule(PlaneType::Type planeType, PlaneRole::Role role, PlaneVersion::Version version) {
	std::unordered_map<PlaneModule::Type, PlaneModule> customModules;
	auto fun = [](std::vector<PlaneModule::Type> typeList) {
		srand(time(0));
		return typeList[static_cast<PlaneModule::Type>(rand() % typeList.size())];
	};

	if (role == PlaneRole::Fighter) {
		if(version == PlaneVersion::InterWar) {
			auto module = fun({ PlaneModule::Type::Gun });
			customModules.insert(std::pair<PlaneModule::Type, PlaneModule>(module, PlaneModule::generateRandom(planeType, role, module)));
			module = fun({ PlaneModule::Type::Gun });
			customModules.insert(std::pair<PlaneModule::Type, PlaneModule>(module, PlaneModule::generateRandom(planeType, role, module)));
			customModules.insert(std::pair<PlaneModule::Type, PlaneModule>(PlaneModule::Type::None , PlaneModule::generateNone()));
			customModules.insert(std::pair<PlaneModule::Type, PlaneModule>(PlaneModule::Type::None , PlaneModule::generateNone()));
			customModules.insert(std::pair<PlaneModule::Type, PlaneModule>(PlaneModule::Type::None , PlaneModule::generateNone()));
		}
	}

	return customModules;
}