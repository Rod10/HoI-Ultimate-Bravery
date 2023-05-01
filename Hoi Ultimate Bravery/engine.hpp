#pragma once
#include "ressources.hpp"
#include "stats.hpp"
#include "utils.hpp"

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