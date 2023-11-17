#pragma once
#include <string>
class RegimentType {
public:
	enum Type {
		Infantry,
		MobileBattalions,
		CombatSupportBattalions,
		MobileCombatSupportBattalions,
		Tank,
		Support,
		Last
	};

	static std::string regimentTypeToFileString(Type type) {
		switch (type)
		{
		case RegimentType::Infantry: return "infantry";
		case RegimentType::MobileBattalions: return "mobilebattalion";
		case RegimentType::CombatSupportBattalions: return "combatsupportbattalion";
		case RegimentType::MobileCombatSupportBattalions: return "mobilesupportcombatbattalion";
		case RegimentType::Tank: return "tank";
		case RegimentType::Support: return "support";
		case RegimentType::Last:
			break;
		default:
			break;
		}
	}
};

