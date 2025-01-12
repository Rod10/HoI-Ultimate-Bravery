#include "engine.hpp"

Engine Engine::generateRandomEngine()
{
    srand(time(0));
    auto statsKey = TankStats::getStatsKeyArray();

    std::vector<Engine::Type> engineType;
    for (int i = 0; i < Engine::Type::Last; i++) {
        engineType.push_back(static_cast<Engine::Type>(i));
    }

    auto type = *Utils::select_randomly(engineType.begin(), engineType.end());

    std::ifstream f("Assets/Data/Tank/Engine.json");
    json armorData = json::parse(f)[Engine::typeToString(type)]["stats"];
    f.close();

    for (auto& el : statsKey) {
        if (armorData[el].is_null()) {
            armorData[el] = 0.0f;
        }
    }
    Ressources ressources;
    TankStats stats = TankStats(ressources, armorData);
    return Engine(type, stats);
}

PlaneEngine PlaneEngine::generateRandom(PlaneType::Type type)
{
    srand(time(0));
    std::ifstream f("Assets/Data/Plane/Engine.json");
    json engineData = json::parse(f)[PlaneType::typeToString(type)];
    f.close();

    std::vector<std::string> engineKey;
    for (auto& el : engineData.items()) {
        engineKey.push_back(el.key());
    }
    std::string engineTypeString = *Utils::select_randomly(engineKey.begin(), engineKey.end());
    PlaneEngine::Type engineType = PlaneEngine::stringToType(engineTypeString);
    
    std::vector<std::string> engineNumberKey;
    for (auto& el : engineData[engineTypeString].items()) {
        engineNumberKey.push_back(el.key());
    }
    std::string engineNumberString= *Utils::select_randomly(engineNumberKey.begin(), engineNumberKey.end());
    int engineNumber =  std::stoi(engineNumberString);
    
    std::vector<std::string> engineVersionKey;
    for (auto& el : engineData[engineTypeString][engineNumberString].items()) {
        engineVersionKey.push_back(el.key());
    }
    std::string engineVersionString = *Utils::select_randomly(engineVersionKey.begin(), engineVersionKey.end());
    PlaneEngine::Version version = PlaneEngine::stringToVersion(engineVersionString);

    return PlaneEngine(engineType, version, engineNumber);
}
