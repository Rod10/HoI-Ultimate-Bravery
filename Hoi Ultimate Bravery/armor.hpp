#pragma once
#include "ressources.hpp"
#include "stats.hpp"
#include "tankstats.hpp"
#include "utils.hpp"

#include <fstream>
#include <iostream>
#include <string>
class Armor {
public: 
	enum Type {
		Cast,
		Riveted,
		Welded,
		Last
	};
	
	Armor();
	Armor(
		Type type,
		TankStats stats
	) : 
		type(type),
		stats(stats) {}

	static std::string typeToString(Type type) {
		switch (type) {
		default: return "INVALID TYPE";
		case Cast: return "cast";
		case Riveted: return "riveted";
		case Welded: return "welded";
		}
	}

	static Armor generateRandomArmor();

	Type type;
	TankStats stats;
};

