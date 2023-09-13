#pragma once
#include "planetype.hpp"
#include "Ressources.hpp"
#include "utils.hpp"

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

	static std::string versionToYear(Version version) {
		switch (version)
		{
		case PlaneVersion::InterWar: return "1933";
		case PlaneVersion::Basic: return "1936";
		case PlaneVersion::Improved: return "1939";
		case PlaneVersion::Advanced: return "1942";
		case PlaneVersion::Modern: return "1945";
		case PlaneVersion::Last:
			break;
		default:
			break;
		}
	}

	static std::string versionToFileString(Version version) {
		switch (version)
		{
		case PlaneVersion::InterWar: return "4";
		case PlaneVersion::Basic: return "3";
		case PlaneVersion::Improved: return "2";
		case PlaneVersion::Advanced: return "1";
		case PlaneVersion::Modern: return "0";
		case PlaneVersion::Last:
			break;
		default:
			break;
		}
	}

	static Version generateRandom(PlaneType::Type type);
};

