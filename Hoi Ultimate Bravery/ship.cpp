#include "ship.hpp"
Ship Ship::generateRandomShip(Hull::Type hull)
{
    srand(time(0));

    ShipType::Type shipType;
    if (hull == Hull::Type::Cruiser) {
        shipType = ShipType::intToShipType(rand() % (2 - 1 + 1) + 1);
    }
    else if (hull == Hull::Type::HeavyShip) {
        shipType = ShipType::intToShipType(rand() % (4 - 3 + 3) + 3);
    }
    else {
        shipType = ShipType::hullToShipType(hull);
    }
    ShipVersion::Version shipversion = Ship::getRandomVersion(shipType);

    //std::map<Module::Type, Module> fixedModule = Ship::generateFixedModule(type, shipversion);

    return Ship();
    /*
    Tank::Version tankVersion = Tank::generatingRandomVersion(type);
    Stats tankStats = Tank::getStatsFromVersion(type, tankVersion);

    Turret turret = Turret::generatingRandomTurret(type);

    Gun gun = Gun::generateRandomGun(turret.allowedGun);
    Role::Type role = *Utils::select_randomly(gun.roleAllowed.begin(), gun.roleAllowed.end());

    std::array<SpecialModule, 4> specialModules = SpecialModule::generateSpecialModule();

    Suspension suspension = Suspension::generateRandomSuspension(type);

    Armor armor = Armor::generateRandomArmor();
    Engine engine = Engine::generateRandomEngine();
    return Tank(type, tankVersion, turret, gun, specialModules, suspension, armor, engine, tankStats, role);*/
}

ShipVersion::Version Ship::getRandomVersion(ShipType::Type type) {
    srand(time(0));
    std::ifstream f("Assets/Data/Ship/Ship.json");
    json shipData = json::parse(f)[ShipType::shipTypeToString(type)];
    f.close();

    std::vector<std::string> shipKey;
    for (auto& el : shipData.items()) {
        shipKey.push_back(el.key());
    }
    int shipVersionInt = rand() % shipKey.size();
    ShipVersion::Version shipVersion = ShipVersion::shipVersionStringToVersion(shipKey[shipVersionInt]);
    return shipVersion;
}

std::map<Module::Type, Module> Ship::generateFixedModule(ShipType::Type type, ShipVersion::Version version) {
    std::map<Module::Type, Module> modules = {};
    if (type == ShipType::Destroyer) {
        modules.insert(std::pair < Module::Type, Module >(Module::Type::LightBattery, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::AntiAir, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::FireControl, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::RadarSonar, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Torpedo, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Engine, Module::generateModule(Module::Type::Engine, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
    }
    if (type == ShipType::LightCruiser || type == ShipType::HeavyCruiser) {
        modules.insert(std::pair < Module::Type, Module >(Module::Type::LightBattery, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::AntiAir, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::FireControl, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::RadarSonar, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Torpedo, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Engine, Module::generateModule(Module::Type::Engine, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Armor, Module()));
    }
    return modules;
}