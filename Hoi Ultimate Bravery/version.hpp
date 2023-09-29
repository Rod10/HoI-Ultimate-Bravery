#pragma once
#include <string>
class Version
{
	enum version {
		InterWar,
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
		Modern,
	};

	static std::string versionToString(version version) {
		switch (version)
		{
		case Version::InterWar: return "interWar";
		case Version::Basic: return "basic";
		case Version::Improved: return "improved";
		case Version::Advanced: return "advanced";
		case Version::Torpedo: return "torpedo";
		case Version::Panzerschiff: return "panzerschiff";
		case Version::CoastalDefense: return "coastalDefense";
		case Version::SuperHeavy: return "superHeavy";
		case Version::ConvertedBattleship: return "convertedBattleship";
		case Version::ConvertedCruiser: return "convertedCruiser";
		case Version::Cruiser: return "cruiser";
		case Version::Midged: return "midget";
		case Version::PreDreadnought: return "preDreadnought";
		case Version::Modern: return "modern";
		default: return "INVALID VERSION";
		}
	}

	static version stringToVersion(version version) {

	}
};

