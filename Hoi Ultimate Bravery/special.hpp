#pragma once
#include "stats.hpp"

class SpecialModule {
public: 
	enum Type {
		BasicRadio,
		ImprovedRadio,
		AdvancedRadio,
		MachineGuns,
		Amphibious,
		ArmorSkirts,
		AutoLoader,
		DozerBlade,
		Maintenance,
		ExtraAmmo,
		SloppedArmor,
		SmokeLauncher,
		Adaptor,
		Stabilizer,
		WetAmmo,
	};

	static std::string typeToString(Type& type) {
		switch (type) {
		case BasicRadio: return "basicRadio";
		case ImprovedRadio: return "improvedRadio";
		case AdvancedRadio: return "advancedRadio";
		case MachineGuns: return "machineGuns";
		case Amphibious: return "amphibious";
		case ArmorSkirts: return "armorSkirts";
		case AutoLoader: return "autoLoader";
		case DozerBlade: return "dozerBlade";
		case Maintenance: return "maintenance";
		case ExtraAmmo: return "extraAmmo";
		case SloppedArmor: return "sloppedArmor";
		case SmokeLauncher: return "smokeLauncher";
		case Adaptor: return "adaptor";
		case Stabilizer: return "stabilizer";
		case WetAmmo: return "wetAmmo";
		}
	}

	static int typeStringToInt(std::string type) {
		if (type == "basicRadio") return 0;
		else if (type == "improvedRadio") return 1;
		else if (type == "advancedRadio") return 2;
		else if (type == "machineGuns") return 3;
		else if (type == "amphibious") return 4;
		else if (type == "armorSkirts") return 5;
		else if (type == "autoLoader") return 6;
		else if (type == "dozerBlade") return 7;
		else if (type == "maintenance") return 8;
		else if (type == "extraAmmo") return 9;
		else if (type == "sloppedArmor") return 10;
		else if (type == "smokeLauncher") return 11;
		else if (type == "adaptor") return 12;
		else if (type == "stabilizer") return 13;
		else if (type == "wetAmmo") return 14;
	}

	static Type stringTypeToType(std::string& type) {
		switch (typeStringToInt(type)) {
		case 0: return BasicRadio;
		case 1: return ImprovedRadio;
		case 2: return AdvancedRadio;
		case 3: return MachineGuns;
		case 4: return Amphibious;
		case 5: return ArmorSkirts;
		case 6: return AutoLoader;
		case 7: return DozerBlade;
		case 8: return Maintenance;
		case 9: return ExtraAmmo;
		case 10: return SloppedArmor;
		case 11: return SmokeLauncher;
		case 12: return Adaptor;
		case 13: return Stabilizer;
		case 14: return WetAmmo;
		}
	}

	Type type;
	Stats stats;
	std::string name;
};
