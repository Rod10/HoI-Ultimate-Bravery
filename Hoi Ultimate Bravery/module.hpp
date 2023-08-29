#pragma once
#include "shiptype.hpp"
#include "shipversion.hpp"

#include <time.h>

class Module
{
public:
	enum Type {
		Engine,
		Armor,
		LightBattery,
		HeavyBattery,
		SecondaryBattery,
		AntiAir,
		Torpedo,
		RadarSonar,
		Snorkel,
		FireControl,
		AntiSubmarine,
		Mine,
		Aircraft,
		Fuel,
		Radar,
		Sonar,
		None,
		Last
	};

	enum Version {
		Basic,
		Early,
		Improved,
		Advanced,
		AutoLoader,
		SuperHeavy,
	};

	Module() {}
	Module(Type type, Version version) :
		type(type),
		version(version) {}

	Type type;
	Version version;

	static std::string moduleTypeToStringFile(Type type) {
		switch (type)
		{
		case Module::Engine: return "Engine";
		case Module::Armor: return "Armor";
		case Module::LightBattery: return "LightBattery";
		case Module::HeavyBattery: return "HeavyBattery";
		case Module::SecondaryBattery: return "SecondaryBattery";
		case Module::AntiAir: return "AntiAir";
		case Module::Torpedo: return "Torpedo";
		case Module::RadarSonar: return "RadarSonar";
		case Module::Snorkel: return "Snorkel";
		case Module::FireControl: return "FireControl";
		case Module::AntiSubmarine: return "AntiSubmarine";
		case Module::Mine: return "Mine";
		case Module::Aircraft: return "Aircraft";
		case Module::Fuel: return "Fuel";
		case Module::Radar: return "Radar";
		case Module::Sonar: return "Sonar";
		case Module::None:
			break;
		default:
			break;
		}
	}

	static Module::Version intToVersion(int type) {
		switch (type)
		{
		case 0: return Early;
		case 1: return Basic;
		case 2: return Improved;
		case 3: return Advanced;
		case 4: return AutoLoader;
		case 5: return SuperHeavy;
		default:
			break;
		}
	}

	static Module generateModule(Type moduleType, ShipType::Type type, ShipVersion::Version version);
};

