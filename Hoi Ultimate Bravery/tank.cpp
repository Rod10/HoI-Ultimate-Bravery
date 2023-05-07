#include "tank.hpp"

Tank::Version Tank::generatingRandomVersion(TankType::Type type)
{
    srand(time(0));
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

Tank Tank::generateRandomTank()
{
    TankType::Type tankType = static_cast<TankType::Type>(rand() % TankType::Type::Last);
    std::cout << "Tank Type: " << Tank::tankTypeToString(tankType) << std::endl;

    Tank::Version tankVersion = Tank::generatingRandomVersion(tankType);
    Stats tankStats = Tank::getStatsFromVersion(tankType, tankVersion);

    Turret turret = Turret::generatingRandomTurret(tankType);
    std::cout << "Turret Type: " << TurretType::turretTypeToString(turret.type) << std::endl;

    Gun gun = Gun::generateRandomGun(turret.allowedGun);
    Role::Type role = *Utils::select_randomly(gun.roleAllowed.begin(), gun.roleAllowed.end());

    std::array<SpecialModule, 4> specialModules = SpecialModule::generateSpecialModule();

    Suspension suspension = Suspension::generateRandomSuspension(tankType);

    Armor armor = Armor::generateRandomArmor();
    Engine engine = Engine::generateRandomEngine();
    return Tank(tankType, tankVersion, turret, gun, specialModules, suspension, armor, engine, tankStats, role);
}

Tank Tank::generateRandomTank(TankType::Type type)
{
    Tank::Version tankVersion = Tank::generatingRandomVersion(type);
    Stats tankStats = Tank::getStatsFromVersion(type, tankVersion);

    Turret turret = Turret::generatingRandomTurret(type);

    Gun gun = Gun::generateRandomGun(turret.allowedGun);
    Role::Type role = *Utils::select_randomly(gun.roleAllowed.begin(), gun.roleAllowed.end());

    std::array<SpecialModule, 4> specialModules = SpecialModule::generateSpecialModule();

    Suspension suspension = Suspension::generateRandomSuspension(type);

    Armor armor = Armor::generateRandomArmor();
    Engine engine = Engine::generateRandomEngine();
    return Tank(type, tankVersion, turret, gun, specialModules, suspension, armor, engine, tankStats, role);
}
