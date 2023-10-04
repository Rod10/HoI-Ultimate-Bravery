#include "module.hpp"

Module Module::generateModule(Type moduleType, ShipType::Type shipType, ShipVersion::Version shipVersion)
{
    srand(time(0));

    if (moduleType == None) {
        return generateNone(moduleType);
    }

    if (moduleType == Type::RadarSonar) {
        moduleType = static_cast<Type>(rand() % (Type::Sonar - Type::Radar + 1) + Type::Radar);
    }
    std::ifstream f(std::format("Assets/Data/Ship/{0}.json", Module::moduleTypeToStringFile(moduleType)));
    json module = json::parse(f);
    f.close();

    std::vector<std::string> moduleNameKey;
    for (auto& el : module.items()) {
        if (el.key().find(ShipType::shipTypeToString(shipType)) != std::string::npos) {
            moduleNameKey.push_back(el.key());
        }
    }
    std::string moduleName = *Utils::select_randomly(moduleNameKey.begin(), moduleNameKey.end());
    
    std::vector<std::string> moduleKey;
    for (auto& el : module[moduleName].items()) {
        moduleKey.push_back(el.key());
    }

    if (moduleType == Type::LightBattery || moduleType == Type::SecondaryBattery || moduleType == Type::Mine) {
        std::vector<std::string> moduleVersion;
        std::string moduleSubType = *Utils::select_randomly(moduleKey.begin(), moduleKey.end());
        Module::SubType subType = Module::stringToSubType(moduleSubType);

        for (auto& el : module[moduleName][moduleSubType].items()) {
            moduleVersion.push_back(el.key());
        }
        std::string moduleVersionString = *Utils::select_randomly(moduleVersion.begin(), moduleVersion.end());
        Module::Version version = Module::stringToVersion(moduleVersionString);

        return Module(moduleType, subType, version);
    }

    std::string moduleVersionInt = *Utils::select_randomly(moduleKey.begin(), moduleKey.end());
    Module::Version version = Module::stringToVersion(moduleVersionInt);
    return Module(moduleType, version);
}

Module Module::generateNone(Type type)
{
    return Module(type);
}

Module Module::generateNone(Type type, SubType subType)
{
    return Module(type, subType);
}
