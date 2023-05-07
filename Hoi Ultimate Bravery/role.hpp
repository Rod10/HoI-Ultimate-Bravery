#pragma once
#include <iostream>
#include <string>
class Role
{
public:
	enum Type {
		Tank,
		Artillery,
		AntiAir,
		TankDestroyer,
		FlameTank,
		Last
	};

	static std::string typeToString(Type role) {
		switch (role) {
		case Tank: return "tank";
		case Artillery: return "tank_artillery";
		case AntiAir: return "tank_aa";
		case TankDestroyer: return "tank_destroyer";
		case FlameTank: return "tank";
		}
	}
	
	static int stringToInt(std::string role) {
		if (role == "tank") return 0;
		if (role == "spArtillery") return 1;
		if (role == "spAA") return 2;
		if (role == "tankDestroyer") return 3;
		if (role == "flameTank") return 4;
	}

	static Type stringToType(std::string role) {
		switch(stringToInt(role)) {
		case 0: return Tank;
		case 1: return Artillery;
		case 2: return AntiAir;
		case 3: return TankDestroyer;
		case 4: return FlameTank;
		}
	}
};

