#include "planemodule.hpp"

PlaneModule PlaneModule::generateRandom(PlaneType::Type planeType, PlaneRole::Role role, PlaneModule::Type type)
{
	srand(time(0));

	std::ifstream f(std::format("Assets/Data/Plane/{0}.json", PlaneModule::typeToFileString(type)));
	json module = json::parse(f);
	f.close();

	std::vector<std::string> moduleSubTypeKey;
	for (auto& el : module.items()) {
		moduleSubTypeKey.push_back(el.key());
	}
	int moduleSubTypeInt = rand() % moduleSubTypeKey.size();
	std::string subModuleName = moduleSubTypeKey[moduleSubTypeInt];
	PlaneModule::SubType subType = PlaneModule::stringToSubType(subModuleName);

	std::vector<std::string> numberKey;
	for (auto& el : module[subModuleName].items()) {
		numberKey.push_back(el.key());
	}
	int numberInt = rand() % numberKey.size();
	int number = std::stoi(numberKey[numberInt]);
	std::string numberString = numberKey[numberInt];

	std::vector<std::string> versionKey;
	for (auto& el : module[subModuleName][numberString].items()) {
		versionKey.push_back(el.key());
	}
	int versionInt = rand() % versionKey.size();
	PlaneModule::Version version = PlaneModule::stringToVersion(versionKey[versionInt]);

	return PlaneModule(type, subType, version, number);

	return PlaneModule();
}

PlaneModule PlaneModule::generateNone(int i)
{
	return PlaneModule(i);
}
