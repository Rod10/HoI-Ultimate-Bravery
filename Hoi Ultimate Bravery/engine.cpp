#include "engine.hpp"

Engine Engine::generateRandomEngine()
{
    srand(time(0));
    auto statsKey = Stats::getStatsKeyArray();

    Engine::Type type = static_cast<Engine::Type>(rand() % Engine::Type::Last);

    std::ifstream f("Assets/Data/Tank/Engine.json");
    json armorData = json::parse(f)[Engine::typeToString(type)]["stats"];
    f.close();

    for (auto& el : statsKey) {
        if (armorData[el].is_null()) {
            armorData[el] = 0.0f;
        }
    }
    Ressources ressources;
    Stats stats = Stats(ressources, armorData);
    return Engine(type, stats);
}
