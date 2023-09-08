#pragma once
#include "planetype.hpp"
#include "Ressources.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
class PlaneVersion
{
public:
	enum Version {
		InterWar,
		Basic,
		Improved,
		Advanced,
		Modern,
		Last
	};

	static std::string versionToString(Version version) {
		switch (version)
		{
		case PlaneVersion::InterWar: return "interWar";
		case PlaneVersion::Basic: return "basic";
		case PlaneVersion::Improved: return "improved";
		case PlaneVersion::Advanced: return "advanced";
		case PlaneVersion::Modern: return "modern";
		default:
			break;
		}
	}
	
	static Version stringToVersion(std::string version) {
		if (version == "interWar") return InterWar;
		if (version == "basic") return Basic;
		if (version == "improved") return Improved;
		if (version == "advanced") return Advanced;
		if (version == "modern") return Modern;
	}

	static Version generateRandom(PlaneType::Type type);
};

