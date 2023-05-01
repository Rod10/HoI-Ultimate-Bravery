#include "turret.hpp"

Turret Turret::generatingRandomTurret(int tankTypeInt)
{
    TankType::Type tankType = TankType::intToTankType(tankTypeInt);
    std::vector<TurretType::Type> turretAllowed = TurretType::getAllowedTurret(tankType);
    TurretType::Type turretType = *Utils::select_randomly(turretAllowed.begin(), turretAllowed.end());
    std::ifstream fT("Assets/Data/Turret.json");
    json data = json::parse(fT);
    fT.close();
    json turretJson = data[TurretType::turretTypeToString(turretType)]["crew"];
    std::vector<std::string> turretCrew;
    for (auto& el : turretJson.items()) {
        turretCrew.push_back(el.key().c_str());
    }
    std::string crew = *Utils::select_randomly(turretCrew.begin(), turretCrew.end());
    json turretData = turretJson[crew];
    std::vector<GunSize::Size> allowedGun;
    for (auto& el : turretData["allowedGun"].items()) {
        allowedGun.push_back(static_cast<GunSize::Size>(std::stoi(el.key())));
    }

    //Turret Stats
    json turretStats = turretData["stats"];
    Ressources ressources = Ressources();

    auto statsKey = Stats::getStatsKeyArray();
    for (auto& el : statsKey) {
        if (turretStats[el].is_null()) {
            turretStats[el] = 0.0f;
        }
    }
    Stats stats = Stats(ressources, turretStats);

    Turret turret = Turret(turretType, std::stoi(crew), allowedGun, stats);
    return turret;
}
