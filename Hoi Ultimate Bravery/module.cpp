#include "module.hpp"

Module Module::generateModule(Type moduleType, ShipType::Type shipType, ShipVersion::Version shipVersion)
{
    srand(time(0));
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
    int moduleNameInt = rand() % moduleNameKey.size();
    std::string moduleName = moduleNameKey[moduleNameInt];
    
    std::vector<std::string> moduleKey;
    for (auto& el : module[moduleName].items()) {
        moduleKey.push_back(el.key());
    }

    if (moduleType == Type::LightBattery || moduleType == Type::SecondaryBattery) {
        std::vector<std::string> moduleVersion;
        int moduleSubType = rand() % moduleKey.size();
        Module::SubType subType = Module::stringToSubType(moduleKey[moduleSubType]);

        for (auto& el : module[moduleName][moduleKey[moduleSubType]].items()) {
            moduleVersion.push_back(el.key());
        }
        int moduleVersionInt = rand() % moduleVersion.size();
        Module::Version version = Module::intToVersion(moduleVersionInt);

        return Module(moduleType, subType, version);
    }

    int moduleVersionInt = rand() % moduleKey.size();
    Module::Version version = Module::intToVersion(moduleVersionInt);
    return Module(moduleType, version);
}
