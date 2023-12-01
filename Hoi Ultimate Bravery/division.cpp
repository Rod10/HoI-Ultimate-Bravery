#include "division.hpp"

Division Division::generateRandom()
{
	int width = Utils::getRandomInt(Constant::MIN_COMBAT_WIDTH, Constant::MAX_COMBAT_WIDTH);
	int actualWidth = 0;
	int supportNumber = Utils::getRandomInt(0, 5);
	std::vector<Support> support;
	std::vector<UnitSubType::Support> supportVector;
	std::vector<RegimentType::Type> regimentTypeVector;
	UnitSubType::Support prevType;
	for (int i = 0; i < UnitSubType::Support::SLast; i++) {
		supportVector.push_back(static_cast<UnitSubType::Support>(i));
	}
	for (int i = 0; i < RegimentType::Type::Last; i++) {
		if (i != RegimentType::Support) {
			regimentTypeVector.push_back(static_cast<RegimentType::Type>(i));
		}
	}
	for (int i = 0; i < supportNumber; i++) {
		UnitSubType::Support supportType = *Utils::select_randomly(supportVector.begin(), supportVector.end());
		if (i != 0){
			while (supportType == prevType) {
				supportType = *Utils::select_randomly(supportVector.begin(), supportVector.end());
			}
		}
		prevType = supportType;
		std::ifstream f("Assets/Data/Unit/support.json");
		json module = json::parse(f)[UnitSubType::supportTypeToString(supportType)];
		f.close();
		std::string name = module["name"];
		support.push_back(Support(RegimentType::Support, name, supportType, 0));
	}

	std::vector<std::vector<Unit>> regimentList;
	for (int regimentNumber = 0; regimentNumber <= 4; regimentNumber++ && actualWidth <= width) {
		RegimentType::Type regimentType = *Utils::select_randomly(regimentTypeVector.begin(), regimentTypeVector.end());
		std::vector<Unit> regiment;
		for (int unitNumber = 0; unitNumber <= 4; unitNumber++) {
			srand(time(0));
			std::ifstream f(std::format("Assets/Data/Unit/{0}.json", RegimentType::regimentTypeToFileString(regimentType)));
			json file = json::parse(f);
			f.close();    
			std::vector<std::string> unitNameKey;
			for (auto& el : file.items()) {
				unitNameKey.push_back(el.key());
			}
			std::string unitTypeName = *Utils::select_randomly(unitNameKey.begin(), unitNameKey.end());
			UnitSubType::Type unitType = UnitSubType::stringToType(unitTypeName);
			std::string name = file[unitTypeName]["name"];
			int unitWidth = file[unitTypeName]["width"];
			if (actualWidth + unitWidth <= width) {
				actualWidth += unitWidth;
				regiment.push_back(Unit(regimentType, name, unitType, unitWidth));
			}
		}
		regimentList.push_back(regiment);
	}
	return Division("", support, regimentList, width);
}
