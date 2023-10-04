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

    std::vector<Module> fixedModule = Ship::generateFixedModule(shipType, shipversion);
    std::vector<Module> customModule = Ship::generateCustomModule(shipType, shipversion);

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
    std::string shipVersionInt = *Utils::select_randomly(shipKey.begin(), shipKey.end());
    ShipVersion::Version shipVersion = ShipVersion::shipVersionStringToVersion(shipVersionInt);
    return shipVersion;
}

std::vector<Module> Ship::generateFixedModule(ShipType::Type type, ShipVersion::Version version) {
    std::vector<Module> modules = {};
    if (type == ShipType::Destroyer) {
        modules.push_back(Module::generateModule(Module::Type::LightBattery, type, version));
        modules.push_back(Module::generateModule(Module::Type::AntiAir, type, version));
        modules.push_back(Module::generateModule(Module::Type::FireControl, type, version));
        modules.push_back(Module::generateModule(Module::Type::RadarSonar, type, version));
        modules.push_back(Module::generateModule(Module::Type::Torpedo, type, version));
        modules.push_back(Module::generateModule(Module::Type::Engine, type, version));
        modules.push_back(Module::generateNone(Module::Type::Armor, Module::SubType::Empty));
    }
    if (type == ShipType::LightCruiser) {
        modules.push_back(Module::generateModule(Module::Type::LightBattery, type, version));
        modules.push_back(Module::generateModule(Module::Type::AntiAir, type, version));
        modules.push_back(Module::generateModule(Module::Type::FireControl, type, version));
        modules.push_back(Module::generateModule(Module::Type::RadarSonar, type, version));
        modules.push_back(Module::generateModule(Module::Type::Engine, type, version));
        modules.push_back(Module::generateModule(Module::Type::SecondaryBattery, type, version));
        modules.push_back(Module::generateModule(Module::Type::Armor, type, version));
    }
    if (type == ShipType::HeavyCruiser) {
        modules.push_back(Module::generateModule(Module::Type::HeavyBattery, type, version));
        modules.push_back(Module::generateModule(Module::Type::AntiAir, type, version));
        modules.push_back(Module::generateModule(Module::Type::FireControl, type, version));
        modules.push_back(Module::generateModule(Module::Type::RadarSonar, type, version));
        modules.push_back(Module::generateModule(Module::Type::Engine, type, version));
        modules.push_back(Module::generateModule(Module::Type::SecondaryBattery, type, version));
        modules.push_back(Module::generateModule(Module::Type::Armor, type, version));
    }
    if (type == ShipType::Battlecruiser) {
        modules.push_back(Module::generateModule(Module::Type::HeavyBattery, type, version));
        modules.push_back( Module::generateModule(Module::Type::AntiAir, type, version));
        modules.push_back(Module::generateModule(Module::Type::FireControl, type, version));
        modules.push_back(Module::generateModule(Module::Type::RadarSonar, type, version));
        modules.push_back(Module::generateModule(Module::Type::Engine, type, version));
        modules.push_back(Module::generateModule(Module::Type::SecondaryBattery, type, version));
        modules.push_back(Module::generateModule(Module::Type::Armor, type, version));
    }
    if (type == ShipType::Battleship) {
        modules.push_back(Module::generateModule(Module::Type::HeavyBattery, type, version));
        modules.push_back(Module::generateModule(Module::Type::AntiAir, type, version));
        modules.push_back(Module::generateModule(Module::Type::FireControl, type, version));
        modules.push_back(Module::generateModule(Module::Type::RadarSonar, type, version));
        modules.push_back(Module::generateModule(Module::Type::Engine, type, version));
        modules.push_back(Module::generateModule(Module::Type::SecondaryBattery, type, version));
        modules.push_back(Module::generateModule(Module::Type::Armor, type, version));
    }
    if (type == ShipType::SuperHeavyBattleship) {
        modules.push_back(Module::generateModule(Module::Type::HeavyBattery, type, version));
        modules.push_back(Module::generateModule(Module::Type::AntiAir, type, version));
        modules.push_back(Module::generateModule(Module::Type::FireControl, type, version));
        modules.push_back(Module::generateModule(Module::Type::RadarSonar, type, version));
        modules.push_back(Module::generateModule(Module::Type::Engine, type, version));
        modules.push_back(Module::generateModule(Module::Type::SecondaryBattery, type, version));
        modules.push_back(Module::generateModule(Module::Type::Armor, type, version));
    }
    if (type == ShipType::Carrier) {
        modules.push_back(Module::generateModule(Module::Type::Aircraft, type, version));
        modules.push_back(Module::generateModule(Module::Type::Aircraft, type, version));
        modules.push_back(Module::generateModule(Module::Type::AntiAir, type, version));
        modules.push_back(Module::generateModule(Module::Type::RadarSonar, type, version));
        modules.push_back(Module::generateModule(Module::Type::Engine, type, version));
        modules.push_back(Module::generateModule(Module::Type::SecondaryBattery, type, version));
        modules.push_back(Module::generateNone(Module::Type::Armor, Module::SubType::Empty));
    }
    if (type == ShipType::Submarine) {
        modules.push_back(Module::generateModule(Module::Type::Torpedo, type, version));
        modules.push_back(Module::generateModule(Module::Type::Engine, type, version));
        modules.push_back(Module::generateNone(Module::Type::Armor, Module::SubType::Empty));
        modules.push_back(Module::generateNone(Module::Type::SecondaryBattery, Module::SubType::Empty));
        modules.push_back(Module::generateNone(Module::Type::RadarSonar, Module::SubType::Empty));
        modules.push_back(Module::generateNone(Module::Type::FireControl, Module::SubType::Empty));
        modules.push_back(Module::generateNone(Module::Type::AntiAir, Module::SubType::Empty));
    }
    return modules;
}

std::vector<Module> Ship::generateCustomModule(ShipType::Type type, ShipVersion::Version version){
    std::vector<Module> modules = {};
    auto fun = [](std::vector<Module::Type> typeList, ShipType::Type shipType, ShipVersion::Version shipVersion) {
        srand(time(0));
        auto moduleType = *Utils::select_randomly(typeList.begin(), typeList.end());
        return Module::generateModule(moduleType, shipType, shipVersion);
    };

    if (type == ShipType::Destroyer) {
        if (version == ShipVersion::Early) {
            modules.push_back(fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::AntiAir, Module::Type::AntiSubmarine, Module::Type::None }, type, version));
            modules.push_back(fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::AntiAir, Module::Type::AntiSubmarine, Module::Type::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        } else if (version == ShipVersion::Basic) {
            modules.push_back(fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::AntiAir, Module::Type::AntiSubmarine, Module::Type::None }, type, version));
            modules.push_back(fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::AntiAir, Module::Type::AntiSubmarine, Module::Type::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        } else if (version == ShipVersion::Improved) {
            modules.push_back(fun({ Module::LightBattery, Module::Type::AntiAir, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::Mine, Module::Type::AntiAir, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::Mine, Module::Type::AntiAir, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        } else if (version == ShipVersion::Advanced) {
            modules.push_back(fun({ Module::LightBattery, Module::Type::AntiAir, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::Mine, Module::Type::AntiAir, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::Mine, Module::Type::AntiAir, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(fun({ Module::LightBattery, Module::Type::Torpedo, Module::Type::Mine, Module::Type::AntiAir, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
    }

    if (type == ShipType::LightCruiser) {
        if (version == ShipVersion::Early) {
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery,  Module::Type::LightBattery }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Basic) {
            modules.push_back(fun({ Module::AntiAir, Module::Type::LightBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::LightBattery }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Improved) {
            modules.push_back(fun({ Module::AntiAir, Module::Type::LightBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::LightBattery, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::LightBattery, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Advanced) {
            modules.push_back(fun({ Module::AntiAir, Module::Type::LightBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::LightBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::LightBattery, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::LightBattery, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
    }

    if (type == ShipType::HeavyCruiser) {
        if (version == ShipVersion::Early) {
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery,  Module::Type::HeavyBattery }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Basic) {
            modules.push_back(fun({ Module::AntiAir, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Improved) {
            modules.push_back(fun({ Module::AntiAir, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::HeavyBattery, Module::None, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::HeavyBattery, Module::None, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Advanced) {
            modules.push_back(fun({ Module::AntiAir, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Aircraft, Module::Type::SecondaryBattery, Module::Type::Torpedo, Module::Type::HeavyBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::HeavyBattery, Module::None, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Type::Mine, Module::Type::Aircraft, Module::Type::HeavyBattery, Module::None, Module::Type::AntiSubmarine }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
    }

    if (type == ShipType::Battlecruiser || type == ShipType::Battleship) {
        if (version == ShipVersion::PreDreadnought) {
            modules.push_back(fun({ Module::AntiAir }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Early) {
            modules.push_back(fun({ Module::AntiAir, Module::HeavyBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::HeavyBattery }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Basic) {
            modules.push_back(fun({ Module::AntiAir, Module::HeavyBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::HeavyBattery, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::HeavyBattery, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::HeavyBattery, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Improved) {
            modules.push_back(fun({ Module::AntiAir, Module::HeavyBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::HeavyBattery, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::HeavyBattery, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::HeavyBattery, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::HeavyBattery }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Advanced) {
            modules.push_back(fun({ Module::AntiAir, Module::HeavyBattery }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::HeavyBattery, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::HeavyBattery, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::HeavyBattery, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::HeavyBattery, Module::SecondaryBattery, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
    }

    if (type == ShipType::SuperHeavyBattleship) {
        modules.push_back(fun({ Module::AntiAir, Module::HeavyBattery }, type, version));
        modules.push_back(fun({ Module::AntiAir, Module::HeavyBattery }, type, version));
        modules.push_back(fun({ Module::AntiAir, Module::SecondaryBattery, Module::None }, type, version));
        modules.push_back(fun({ Module::AntiAir, Module::SecondaryBattery, Module::None }, type, version));
        modules.push_back(fun({ Module::AntiAir, Module::SecondaryBattery, Module::None }, type, version));
        modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::SecondaryBattery, Module::None, Module::HeavyBattery }, type, version));
        modules.push_back(fun({ Module::AntiAir, Module::Aircraft, Module::None, Module::SecondaryBattery, Module::None, Module::HeavyBattery }, type, version));
    }

    if (type == ShipType::Carrier) {
        if (version == ShipVersion::Basic) {
            modules.push_back(fun({ Module::SecondaryBattery, Module::None, Module::Armor, Module::Aircraft, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Improved) {
            modules.push_back(fun({ Module::SecondaryBattery, Module::None, Module::Armor, Module::Aircraft, Module::None }, type, version));
            modules.push_back(fun({ Module::SecondaryBattery, Module::None, Module::Armor, Module::Aircraft, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Advanced) {
            modules.push_back(fun({ Module::SecondaryBattery, Module::None, Module::Armor, Module::Aircraft, Module::None }, type, version));
            modules.push_back(fun({ Module::SecondaryBattery, Module::None, Module::Armor, Module::Aircraft, Module::None }, type, version));
            modules.push_back(fun({ Module::SecondaryBattery, Module::None, Module::Armor, Module::Aircraft, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::ConvertedBattleship) {
            modules.push_back(fun({ Module::SecondaryBattery, Module::None, Module::Armor, Module::Aircraft, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::ConvertedCruiser) {
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
    }

    if (type == ShipType::Submarine) {
        if (version == ShipVersion::Early) {
            modules.push_back(fun({ Module::Mine, Module::Torpedo, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Basic) {
            modules.push_back(fun({ Module::Mine, Module::Torpedo }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Improved) {
            modules.push_back(fun({ Module::Mine, Module::Torpedo, Module::None }, type, version));
            modules.push_back(fun({ Module::Snorkel, Module::Radar, Module::None }, type, version));
            modules.push_back(fun({ Module::Mine, Module::Torpedo, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Advanced) {
            modules.push_back(fun({ Module::Mine, Module::Torpedo, Module::None }, type, version));
            modules.push_back(fun({ Module::Snorkel, Module::Radar, Module::None }, type, version));
            modules.push_back(fun({ Module::Mine, Module::Torpedo, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Midget) {
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
        else if (version == ShipVersion::Cruiser) {
            modules.push_back(fun({ Module::Mine, Module::Torpedo, Module::Aircraft, Module::None, Module::Fuel, Module::None }, type, version));
            modules.push_back(fun({ Module::Snorkel, Module::Radar }, type, version));
            modules.push_back(fun({ Module::Mine, Module::Torpedo, Module::Aircraft, Module::None, Module::Fuel, Module::None }, type, version));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
            modules.push_back(Module::generateNone(Module::Type::None));
        }
    }
    return modules;
}