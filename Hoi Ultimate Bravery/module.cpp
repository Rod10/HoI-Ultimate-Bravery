#include "module.hpp"

Module Module::generateModule(Type moduleType, ShipType::Type shipType, ShipVersion::Version shipVersion)
{
    srand(time(0));
    std::ifstream f(std::format("Assets/Data/Ship/{0}.json", Module::moduleTypeToStringFile(moduleType)));
    json moduleData = json::parse(f)[ShipType::shipTypeToString(shipType)];
    f.close();

    std::vector<std::string> moduleKey;
    for (auto& el : moduleData.items()) {
        moduleKey.push_back(el.key());
    }
    int moduleVersionInt = rand() % moduleKey.size();
    Module::Version version = Module::intToVersion(moduleVersionInt);
    return Module(moduleType, version);
}
