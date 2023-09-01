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
		case ShipVersion::Torpedo:
			break;
		case ShipVersion::Panzerschiff:
			break;
		case ShipVersion::CoastalDefense:
			break;
		case ShipVersion::SuperHeavy:
			break;
		case ShipVersion::ConvertedBattleship:
			break;
		case ShipVersion::ConvertedCruiser:
			break;
		case ShipVersion::Cruiser:
			break;
		case ShipVersion::Midged:
			break;
		case ShipVersion::PreDreadnought:
			break;
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
		default:
			break;
		}
	}

	/*
	enum DestroyerVersion {
		Early,
		Basic,
		Improved,
		Advanced,
		DDLast
	};

	enum CruiserVersion {
		Early,
		Basic,
		Improved,
		Advanced,
		Torpedo,
		Panzerschiff,
		CoastalDefense,
		CALast
	};

	enum HeavyShipVersion {
		PreDreadnought,
		Early,
		Basic,
		Improved,
		Advanced,
		SuperHeavy,
		BBLast
	};

	enum CarrierVersion {
		Basic,
		Improved,
		Advanced,
		ConvertedBattleship,
		ConvertedCruiser,
		CVLast
	};

	enum SubmarineVersion {
		Early,
		Basic,
		Improved,
		Advanced,
		Cruiser,
		Midged,
		SSLast
	};*/

	/*static auto getRandomVersion(ShipType::Type type) {
		srand(time(0));
		switch (type)
		{
		case ShipType::Destroyer:
			return static_cast<ShipVersion::DestroyerVersion>(rand() % ShipVersion::DestroyerVersion::Last);
		case ShipType::Cruiser:
			return static_cast<ShipVersion::CruiserVersion>(rand() % ShipVersion::CruiserVersion::Last);
		case ShipType::HeavyShip:
			return static_cast<ShipVersion::HeavyShipVersion>(rand() % ShipVersion::HeavyShipVersion::Last);
		case ShipType::Carrier:
			return static_cast<ShipVersion::DestroyerVersion>(rand() % ShipVersion::CarrierVersion::Last);
		case ShipType::Submarine:
			return static_cast<ShipVersion::DestroyerVersion>(rand() % ShipVersion::SubmarineVersion::Last);
		default:
			break;
		}
	}*/
};