#pragma once
#include "planetype.hpp"
#include "ressources.hpp"
#include "stats.hpp"
#include "utils.hpp"

#include <format>
#include <fstream>
#include <iostream>
#include <string>

class Engine {
public:
	enum Type {
		Diesel,
		Gas,
		Gasoline,
		PetrolElectric,
		Last
	};

	Engine();
	Engine(
		Type type,
		Stats stats
	) : 
		type(type),
		stats(stats) {}

	static std::string typeToString(Type& type) {
		switch (type)
		{
		default: return "INVALID TYPE";
		case Diesel: return "diesel";
		case Gas: return "gas";
		case Gasoline: return "gasoline";
		case PetrolElectric: return "petrolElectric";
		}
	}

	static Engine generateRandomEngine();

	Type type;
	Stats stats;
};

class PlaneEngine {
public:

	enum Type {
		Prop,
		Jet,
		Rocket,
		TLast
	};

	enum Version {
		Early,
		Basic,
		Improved,
		Advanced,
		VLast
	};

	PlaneEngine() {};
	PlaneEngine(PlaneEngine::Type type,
		PlaneEngine::Version version,
		int number) : 
	type(type),
	version(version),
	number(number) {};

	PlaneEngine::Type type;
	PlaneEngine::Version version;
	int number;

	static PlaneEngine::Type stringToType(std::string type) {
		if (type == "prop") return Prop;
		if (type == "jet") return Jet;
		if (type == "rocket") return Rocket;
	}

	static PlaneEngine::Version stringToVersion(std::string version) {
		if (version == "early") return Early;
		if (version == "basic") return Basic;
		if (version == "improved") return Improved;
		if (version == "advanced") return Advanced;
	}
	
	static std::string engineToImageString(PlaneEngine engine) {
		switch (engine.type)
		{
		case Prop: return std::format("Airplane_engine_{0}_{1}", (engine.version + 1), engine.number);
		case Jet: return std::format("Airplane_jet_engine_{0}", engine.number);
		case Rocket: return std::format("Airplane_rocket_engine_{0}", (engine.version + 1));
		default:
			break;
		}
	}

	static PlaneEngine generateRandom(PlaneType::Type type);
};