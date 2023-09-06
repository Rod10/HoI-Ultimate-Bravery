#include "ship.hpp"
Ship Ship::generateRandomShip(Hull::Type hull)
{
    srand(time(0));

    ShipType::Type shipType;
    if (hull == Hull::Type::Cruiser) {
        shipType = ShipType::intToShipType(rand() % (2 - 1 + 1) + 1);
    }
    else if (hull == Hull::Type::HeavyShip) {
        shipType = ShipType::intToShipType(rand() % (5 - 3 + 1) + 3);
    }
    else {
        shipType = ShipType::hullToShipType(hull);
    }
    ShipVersion::Version shipversion = Ship::getRandomVersion(hull, shipType);

    std::unordered_map<Module::Type, Module> fixedModule = Ship::generateFixedModule(shipType, shipversion);
    std::unordered_map<Module::Type, Module> customModule = Ship::generateCustomModule(shipType, shipversion);

    return Ship(hull, shipType, shipversion, customModule, fixedModule);
}

ShipVersion::Version Ship::getRandomVersion(Hull::Type hull, ShipType::Type type) {
    srand(time(0));
    std::ifstream f("Assets/Data/Ship/Ship.json");
    json shipData;
    if (type == ShipType::Type::SuperHeavyBattleship) {
        shipData = json::parse(f)["superHeavy"];
    }
    else shipData = json::parse(f)[Hull::typeToString(hull)];
    f.close();

    std::vector<std::string> shipKey;
    for (auto& el : shipData.items()) {
        shipKey.push_back(el.key());
    }
    int shipVersionInt = rand() % shipKey.size();
    ShipVersion::Version shipVersion = ShipVersion::shipVersionStringToVersion(shipKey[shipVersionInt]);
    return shipVersion;
}

std::unordered_map<Module::Type, Module> Ship::generateFixedModule(ShipType::Type type, ShipVersion::Version version) {
    std::unordered_map<Module::Type, Module> modules = {};
    if (type == ShipType::Destroyer) {
        modules.insert(std::pair < Module::Type, Module >(Module::Type::LightBattery, Module::generateModule(Module::Type::LightBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::AntiAir, Module::generateModule(Module::Type::AntiAir, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::FireControl, Module::generateModule(Module::Type::FireControl, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::RadarSonar, Module::generateModule(Module::Type::RadarSonar, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Torpedo, Module::generateModule(Module::Type::Torpedo, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Engine, Module::generateModule(Module::Type::Engine, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
    }
    if (type == ShipType::LightCruiser) {
        modules.insert(std::pair < Module::Type, Module >(Module::Type::LightBattery, Module::generateModule(Module::Type::LightBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::AntiAir, Module::generateModule(Module::Type::AntiAir, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::FireControl, Module::generateModule(Module::Type::FireControl, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::RadarSonar, Module::generateModule(Module::Type::RadarSonar, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Engine, Module::generateModule(Module::Type::Engine, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::SecondaryBattery, Module::generateModule(Module::Type::SecondaryBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Armor, Module::generateModule(Module::Type::Armor, type, version)));
    }
    if (type == ShipType::HeavyCruiser) {
        modules.insert(std::pair < Module::Type, Module >(Module::Type::HeavyBattery, Module::generateModule(Module::Type::HeavyBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::AntiAir, Module::generateModule(Module::Type::AntiAir, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::FireControl, Module::generateModule(Module::Type::FireControl, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::RadarSonar, Module::generateModule(Module::Type::RadarSonar, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Engine, Module::generateModule(Module::Type::Engine, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::SecondaryBattery, Module::generateModule(Module::Type::SecondaryBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Armor, Module::generateModule(Module::Type::Armor, type, version)));
    }
    if (type == ShipType::Battlecruiser) {
        modules.insert(std::pair < Module::Type, Module >(Module::Type::HeavyBattery, Module::generateModule(Module::Type::HeavyBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::AntiAir, Module::generateModule(Module::Type::AntiAir, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::FireControl, Module::generateModule(Module::Type::FireControl, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::RadarSonar, Module::generateModule(Module::Type::RadarSonar, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Engine, Module::generateModule(Module::Type::Engine, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::SecondaryBattery, Module::generateModule(Module::Type::SecondaryBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Armor, Module::generateModule(Module::Type::Armor, type, version)));
    }
    if (type == ShipType::Battleship) {
        modules.insert(std::pair < Module::Type, Module >(Module::Type::HeavyBattery, Module::generateModule(Module::Type::HeavyBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::AntiAir, Module::generateModule(Module::Type::AntiAir, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::FireControl, Module::generateModule(Module::Type::FireControl, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::RadarSonar, Module::generateModule(Module::Type::RadarSonar, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Engine, Module::generateModule(Module::Type::Engine, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::SecondaryBattery, Module::generateModule(Module::Type::SecondaryBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Armor, Module::generateModule(Module::Type::Armor, type, version)));
    }
    if (type == ShipType::SuperHeavyBattleship) {
        modules.insert(std::pair < Module::Type, Module >(Module::Type::HeavyBattery, Module::generateModule(Module::Type::HeavyBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::AntiAir, Module::generateModule(Module::Type::AntiAir, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::FireControl, Module::generateModule(Module::Type::FireControl, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::RadarSonar, Module::generateModule(Module::Type::RadarSonar, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Engine, Module::generateModule(Module::Type::Engine, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::SecondaryBattery, Module::generateModule(Module::Type::SecondaryBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Armor, Module::generateModule(Module::Type::Armor, type, version)));
    }
    if (type == ShipType::Carrier) {
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Aircraft, Module::generateModule(Module::Type::Aircraft, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Aircraft, Module::generateModule(Module::Type::Aircraft, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::AntiAir, Module::generateModule(Module::Type::AntiAir, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::RadarSonar, Module::generateModule(Module::Type::RadarSonar, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Engine, Module::generateModule(Module::Type::Engine, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::SecondaryBattery, Module::generateModule(Module::Type::SecondaryBattery, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module::generateModule(Module::Type::Armor, type, version)));
    }
    if (type == ShipType::Submarine) {
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Torpedo, Module::generateModule(Module::Type::Torpedo, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::Engine, Module::generateModule(Module::Type::Engine, type, version)));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
    }
    return modules;
}

std::unordered_map<Module::Type, Module> Ship::generateCustomModule(ShipType::Type type, ShipVersion::Version version){
    std::unordered_map<Module::Type, Module> modules = {};
    auto fun = [](std::vector<Module::Type> typeList) {
        srand(time(0));
        return typeList[static_cast<Module::Type>(rand() % typeList.size())];
    };
    if (type == ShipType::Destroyer) {
        if (version == ShipVersion::Early) {
            auto module = fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::AntiAir, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::AntiAir, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        } else if (version == ShipVersion::Basic) {
            auto module = fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::AntiAir, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::AntiAir, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        } else if (version == ShipVersion::Improved) {
            auto module = fun({ Module::LightBattery, Module::Type::AntiAir, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::Mine, Module::Type::AntiAir, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::Mine, Module::Type::AntiAir, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        } else if (version == ShipVersion::Advanced) {
            auto module = fun({ Module::LightBattery, Module::Type::AntiAir, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::Mine, Module::Type::AntiAir, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::Mine, Module::Type::AntiAir, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::Mine, Module::Type::AntiAir, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
    }

    if (type == ShipType::LightCruiser) {
        if (version == ShipVersion::Early) {
            auto module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery,  Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Basic) {
            auto module = fun({ Module::AntiAir, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Improved) {
            auto module = fun({ Module::AntiAir, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::LightBattery, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::LightBattery, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Advanced) {
            auto module = fun({ Module::AntiAir, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::LightBattery, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::LightBattery, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
    }

    if (type == ShipType::HeavyCruiser) {
        if (version == ShipVersion::Early) {
            auto module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery,  Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Basic) {
            auto module = fun({ Module::AntiAir, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Improved) {
            auto module = fun({ Module::AntiAir, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::HeavyBattery, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::HeavyBattery, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Advanced) {
            auto module = fun({ Module::AntiAir, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::HeavyBattery, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::HeavyBattery, Module::Type::AntiSubmarine });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
    }

    if (type == ShipType::Battlecruiser || type == ShipType::Battleship) {
        if (version == ShipVersion::PreDreadnought) {
            auto module = fun({ Module::AntiAir });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::SecondaryBattery, Module::Torpedo });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Early) {
            auto module = fun({ Module::AntiAir, Module::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Basic) {
            auto module = fun({ Module::AntiAir, Module::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::HeavyBattery, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::HeavyBattery, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::HeavyBattery, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Improved) {
            auto module = fun({ Module::AntiAir, Module::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::HeavyBattery, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::HeavyBattery, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::HeavyBattery, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Advanced) {
            auto module = fun({ Module::AntiAir, Module::HeavyBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::HeavyBattery, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::HeavyBattery, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::HeavyBattery, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::AntiAir, Module::Aircraft, Module::HeavyBattery, Module::SecondaryBattery });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
    }

    if (type == ShipType::SuperHeavyBattleship) {
        auto module = fun({ Module::AntiAir, Module::HeavyBattery });
        modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
        module = fun({ Module::AntiAir, Module::HeavyBattery });
        modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
        module = fun({ Module::AntiAir, Module::SecondaryBattery });
        modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
        module = fun({ Module::AntiAir, Module::SecondaryBattery });
        modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
        module = fun({ Module::AntiAir, Module::SecondaryBattery });
        modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
        module = fun({ Module::AntiAir, Module::Aircraft, Module::SecondaryBattery, Module::HeavyBattery });
        modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
        module = fun({ Module::AntiAir, Module::Aircraft, Module::SecondaryBattery, Module::HeavyBattery });
        modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
    }

    if (type == ShipType::Carrier) {
        if (version == ShipVersion::Basic) {
            auto module = fun({ Module::SecondaryBattery, Module::Armor, Module::Aircraft });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Improved) {
            auto module = fun({ Module::SecondaryBattery, Module::Armor, Module::Aircraft });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::SecondaryBattery, Module::Armor, Module::Aircraft });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Advanced) {
            auto module = fun({ Module::SecondaryBattery, Module::Armor, Module::Aircraft });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::SecondaryBattery, Module::Armor, Module::Aircraft });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::SecondaryBattery, Module::Armor, Module::Aircraft });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::ConvertedBattleship) {
            auto module = fun({ Module::SecondaryBattery, Module::Armor, Module::Aircraft });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::ConvertedCruiser) {
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
    }

    if (type == ShipType::Submarine) {
        if (version == ShipVersion::Early) {
            auto module = fun({ Module::Mine, Module::Torpedo });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Basic) {
            auto module = fun({ Module::Mine, Module::Torpedo });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Improved) {
            auto module = fun({ Module::Mine, Module::Torpedo });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::Snorkel, Module::Radar });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::Mine, Module::Torpedo });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Advanced) {
            auto module = fun({ Module::Mine, Module::Torpedo });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::Snorkel, Module::Radar });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::Mine, Module::Torpedo });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Midged) {
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
        else if (version == ShipVersion::Cruiser) {
            auto module = fun({ Module::Mine, Module::Torpedo, Module::Aircraft, Module::Fuel });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::Snorkel, Module::Radar });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            module = fun({ Module::Mine, Module::Torpedo, Module::Aircraft, Module::Fuel });
            modules.insert(std::pair < Module::Type, Module >(module, Module::generateModule(module, type, version)));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
            modules.insert(std::pair < Module::Type, Module >(Module::Type::None, Module()));
        }
    }
    return modules;
}