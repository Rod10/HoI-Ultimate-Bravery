#include "plane.hpp"

Plane Plane::generateRandomPlane(PlaneRole::Role role)
{
	srand(time(0));

	PlaneType::Type type = getTypeByRole(role);

	PlaneVersion::Version version = PlaneVersion::generateRandom(type);
	PlaneEngine engine = PlaneEngine::generateRandom(type);
	std::unordered_map<PlaneModule::Type, PlaneModule> fixed = generateFixedModule(type, role);
	std::vector<PlaneModule> custom = generateCustomModule(type, role, version);

	return Plane(role, type, version, engine, fixed, custom);
}

PlaneType::Type Plane::getTypeByRole(PlaneRole::Role role) {
	switch (role)
	{
	case PlaneRole::Fighter: return PlaneType::Small;
	case PlaneRole::CAS: return PlaneType::Small;
	case PlaneRole::NavalBombing: return static_cast<PlaneType::Type>(rand() % PlaneType::Last);
	case PlaneRole::TacticalBombing: return PlaneType::Medium;
	case PlaneRole::StrategicBombing: return PlaneType::Large;
	case PlaneRole::Last:
		break;
	default:
		break;
	}
}

std::unordered_map<PlaneModule::Type, PlaneModule> Plane::generateFixedModule(PlaneType::Type planeType, PlaneRole::Role role) {
	std::unordered_map<PlaneModule::Type, PlaneModule> fixedModules;
	/*auto fun = [](std::vector<PlaneModule::Type> typeList) {
		srand(time(0));
		return typeList[static_cast<PlaneModule::Type>(rand() % typeList.size())];
	};
	auto module = fun({ PlaneModule::Type::Armor, PlaneModule::Type::Defense, PlaneModule::Type::Electronics, PlaneModule::Type::Fuel, PlaneModule::Type::SpecialModule });
	fixedModules.push_back(std::pair<PlaneModule::Type, PlaneModule>(module, PlaneModule::generateRandom(planeType, role, module)));
	module = fun({ PlaneModule::Type::Armor, PlaneModule::Type::Defense, PlaneModule::Type::Electronics, PlaneModule::Type::Fuel, PlaneModule::Type::SpecialModule });
	fixedModules.push_back(std::pair<PlaneModule::Type, PlaneModule>(module, PlaneModule::generateRandom(planeType, role, module)));
	module = fun({ PlaneModule::Type::Armor, PlaneModule::Type::Defense, PlaneModule::Type::Electronics, PlaneModule::Type::Fuel, PlaneModule::Type::SpecialModule });
	fixedModules.push_back(std::pair<PlaneModule::Type, PlaneModule>(module, PlaneModule::generateRandom(planeType, role, module)));*/

	return fixedModules;
}

std::vector<PlaneModule> Plane::generateCustomModule(PlaneType::Type planeType, PlaneRole::Role role, PlaneVersion::Version version) {
	std::vector<PlaneModule> customModules;
	auto fun = [](std::vector<PlaneModule::Type> typeList, PlaneType::Type planeType, PlaneRole::Role role) {
		srand(time(0));
		auto type = *Utils::select_randomly(typeList.begin(), typeList.end());
		return PlaneModule::generateRandom(planeType, role, type);
	};

	if (role == PlaneRole::Fighter) {
		if(version == PlaneVersion::InterWar) {
			customModules.push_back(fun({ PlaneModule::Type::Gun }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Gun, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
		if(version == PlaneVersion::Basic) {
			customModules.push_back(fun({ PlaneModule::Type::Gun }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Gun, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
		if(version == PlaneVersion::Improved) {
			customModules.push_back(fun({ PlaneModule::Type::Gun }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Gun, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Gun, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
		if(version == PlaneVersion::Advanced) {
			customModules.push_back(fun({ PlaneModule::Type::Gun }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Gun, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Gun, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Gun, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
		if(version == PlaneVersion::Modern) {
			customModules.push_back(fun({ PlaneModule::Type::Gun }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Gun, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Gun, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Gun, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
	}

	if (role == PlaneRole::CAS || role == PlaneRole::TacticalBombing || role == PlaneRole::StrategicBombing ) {
		if(version == PlaneVersion::InterWar) {
			auto module = fun({ PlaneModule::Type::Bomb }, planeType, role);
			customModules.push_back(fun({ PlaneModule::Type::Bomb }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Bomb, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
		if(version == PlaneVersion::Basic) {
			customModules.push_back(fun({ PlaneModule::Type::Bomb }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Bomb, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
		if(version == PlaneVersion::Improved) {
			customModules.push_back(fun({ PlaneModule::Type::Bomb }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Bomb, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Bomb, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
		if(version == PlaneVersion::Advanced) {
			customModules.push_back(fun({ PlaneModule::Type::Bomb }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Bomb, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Bomb, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Bomb, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
		if(version == PlaneVersion::Modern) {
			customModules.push_back(fun({ PlaneModule::Type::Bomb }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Bomb, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Bomb, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Bomb, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
	}

	if (role == PlaneRole::NavalBombing ) {
		if(version == PlaneVersion::InterWar) {
			customModules.push_back(fun({ PlaneModule::Type::Torpedo }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Torpedo, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
		if(version == PlaneVersion::Basic) {
			customModules.push_back(fun({ PlaneModule::Type::Torpedo }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Torpedo, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
		if(version == PlaneVersion::Improved) {
			customModules.push_back(fun({ PlaneModule::Type::Torpedo }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Torpedo, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Torpedo, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
		if(version == PlaneVersion::Advanced) {
			customModules.push_back(fun({ PlaneModule::Type::Torpedo }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Torpedo, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Torpedo, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(fun({ PlaneModule::Type::Torpedo, PlaneModule::Type::None }, planeType, role));
			customModules.push_back(PlaneModule::generateNone(PlaneModule::Type::None));
		}
	}

	return customModules;
}