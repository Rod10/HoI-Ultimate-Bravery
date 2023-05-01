#include "tank.hpp"

Tank::Version Tank::generatingRandomVersion(TankType::Type type)
{
    std::ifstream f("Assets/Data/Tank.json");
    json tankData = json::parse(f)[Tank::tankTypeToString(type)];
    f.close();

    std::vector<std::string> tankKey;
    for (auto& el : tankData.items()) {
        tankKey.push_back(el.key());
    }
    int tankVersionInt = rand() % tankKey.size();
    Tank::Version tankVersion = Tank::tankVersionStringToVersion(tankKey[tankVersionInt]);
    return tankVersion;
}

Stats Tank::getStatsFromVersion(TankType::Type type, Tank::Version version)
{
    std::ifstream f("Assets/Data/Tank.json");
    json tankData = json::parse(f)[Tank::tankTypeToString(type)];
    f.close();
    auto statsKey = Stats::getStatsKeyArray();
    json tankStatsData = tankData[Tank::tankVersionToString(version)]["stats"];
    for (auto& el : statsKey) {
        if (tankStatsData[el].is_null()) {
            tankStatsData[el] = 0.0f;
        }
    }
    Ressources ressources = tankStatsData["ressources"];
    Stats tankStats = Stats(ressources, tankStatsData);
    return tankStats;
}
