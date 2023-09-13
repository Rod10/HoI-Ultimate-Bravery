#include "planemodule.hpp"

PlaneModule PlaneModule::generateRandom(PlaneType::Type planeType, PlaneRole::Role role, PlaneModule::Type type)
{
	srand(time(0));

    if (type == None) {
        return PlaneModule::generateNone(type);
    }

	std::ifstream f(std::format("Assets/Data/Plane/{0}.json", PlaneModule::typeToFileString(type)));
	json module = json::parse(f);
	f.close();

    std::vector<std::string> typeKey;
    for (auto& el : module.items()) {
        if (el.key().find(PlaneType::typeToString(planeType)) != std::string::npos) {
            typeKey.push_back(el.key());
        }
    }
    std::string typeNameString = *Utils::select_randomly(typeKey.begin(), typeKey.end());

    std::vector<std::string> moduleNameKey;
    for (auto& el : module[typeNameString].items()) {
        moduleNameKey.push_back(el.key());
    }
    std::string moduleName = *Utils::select_randomly(moduleNameKey.begin(), moduleNameKey.end());
    PlaneModule::SubType subType = PlaneModule::stringToSubType(moduleName);

    if (type == PlaneModule::Type::Gun || type == PlaneModule::Type::Defense) {
        std::vector<std::string> numberKey;
        for (auto& el : module[typeNameString][moduleName].items()) {
            numberKey.push_back(el.key());
        }
        std::string number = *Utils::select_randomly(numberKey.begin(), numberKey.end());

        std::vector<std::string> versionKey;
        for (auto& el : module[typeNameString][moduleName][number].items()) {
            versionKey.push_back(el.key());
        }
        std::string versionString = *Utils::select_randomly(versionKey.begin(), versionKey.end());

        PlaneModule::Version version = PlaneModule::stringToVersion(versionString);

        return PlaneModule(type, subType, version, std::stoi(number));
    }

    std::vector<std::string> versionKey;
    for (auto& el : module[typeNameString][moduleName].items()) {
        versionKey.push_back(el.key());
    }
    std::string versionString = *Utils::select_randomly(versionKey.begin(), versionKey.end());

    PlaneModule::Version version = PlaneModule::stringToVersion(versionString);

    return PlaneModule(type, subType, version);
}

PlaneModule PlaneModule::generateNone(PlaneModule::Type type)
{
	return PlaneModule(type);
}
