#pragma once
#include "Stats.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>
#include <vector>
class ShipVersion
{
public:
	enum Version {
		Early,
		Basic,
		Improved,
		Advanced,
		Torpedo,
		Panzerschiff,
		CoastalDefense,
		SuperHeavy,
		ConvertedBattleship,
		ConvertedCruiser,
		Cruiser,
		Midged,
		PreDreadnought,
		Last
	};

	static ShipVersion::Version shipVersionStringToVersion(std::string version) {
		if (version == "early") return Early;
		if (version == "basic") return Basic;
		if (version == "improved") return Improved;
		if (version == "advanced") return Advanced;
		if (version == "torpedo") return Torpedo;
		if (version == "panzerschiff") return Panzerschiff;
		if (version == "coastalDefense") return CoastalDefense;
		if (version == "superHeavy") return SuperHeavy;
		if (version == "convertedBattleship") return ConvertedBattleship;
		if (version == "convertedCruiser") return ConvertedCruiser;
		if (version == "cruiser") return Cruiser;
		if (version == "midged") return Midged;
		if (version == "preDreadnought") return PreDreadnought;
	}

	static std::string versionToFileString(Version version) {
		switch (version)
		{
		case ShipVersion::Early: return "Early";
		case ShipVersion::Basic: return "Basic";
		case ShipVersion::Improved: return "Improved";
		case ShipVersion::Advanced: return "Advanced";
		case ShipVersion::Torpedo: return "Torpedo";
		case ShipVersion::Panzerschiff: return "Ship_hull_panzerschiff";
		case ShipVersion::CoastalDefense: return "Ship_hull_cruiser_coastal_defense_ship";
		case ShipVersion::SuperHeavy: return "Heavy_battleship";
		case ShipVersion::ConvertedBattleship:return "Ship_hull_carrier_conversion_ca";
		case ShipVersion::ConvertedCruiser: return "Ship_hull_carrier_conversion_ca";
		case ShipVersion::Cruiser: return "Ship_hull_cruiser";
		case ShipVersion::Midged: return "Ship_hull_midget";
		case ShipVersion::PreDreadnought: return "PreDreadnought";
		case ShipVersion::Last:
			break;
		default:
			break;
		}
	}

	static std::string versionToYear(Version version) {
		switch (version)
		{
		case ShipVersion::Early: return "1918";
		case ShipVersion::Basic: return "1936";
		case ShipVersion::Improved: return "1940";
		case ShipVersion::Advanced: return "1944";
		case ShipVersion::CoastalDefense: return "Coastal Defense";
		case ShipVersion::Torpedo: return "Torpedo";
		case ShipVersion::Panzerschiff: return "Panzerschiff";
		case ShipVersion::PreDreadnought: return "PreDreadnought";
		default:
			break;
		}
	}
};