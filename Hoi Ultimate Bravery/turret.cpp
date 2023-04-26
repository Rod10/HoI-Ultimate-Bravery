#include <fstream>
#include <iostream>

#include "utils.hpp"
#include "tank.hpp"
#include "turret.hpp"

Turret Turret::generatingRandomTurret(int tankTypeInt)
{
    Tank::Type tankType = Tank::intToTankType(tankTypeInt);
    std::vector<Turret::Type> turretAllowed = Tank::getAllowedTurret(tankType);
    Turret::Type turretType = *Utils::select_randomly(turretAllowed.begin(), turretAllowed.end());
    std::ifstream fT("Assets/Data/Turret.json");
    json data = json::parse(fT);
    fT.close();
    json turretJson = data[Turret::turretTypeToString(turretType)]["crew"];
    std::vector<std::string> turretCrew;
    for (auto& el : turretJson.items()) {
        turretCrew.push_back(el.key().c_str());
    }
    std::string crew = *Utils::select_randomly(turretCrew.begin(), turretCrew.end());
    json turretData = turretJson[crew];
    std::vector<Gun::Size> allowedGun;
    for (auto& el : turretData["allowedGun"].items()) {
        allowedGun.push_back(static_cast<Gun::Size>(std::stoi(el.key())));
    }

    //Turret Stats
    json turretStats = turretData["stats"];
    Ressources ressources = Ressources();
    const std::string statsKey[13] = { "year", "speed", "reliability", "softAttack", "hardAttack", "piercing", "breakthrough", "airAttack", "productionCost", "armor", "defense", "entrenchment", "hardness" };
    for (auto& el : statsKey) {
        if (turretStats[el].is_null()) {
            turretStats[el] = 0;
        }
    }
    Stats stats = Stats(ressources, turretStats);

    Turret turret = Turret(turretType, std::stoi(crew), allowedGun, stats);
    return turret;
}
