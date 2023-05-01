#include "armor.hpp"

Armor Armor::generateRandomArmor() {
    auto statsKey = Stats::getStatsKeyArray();

    Armor::Type type = static_cast<Armor::Type>(rand() % Armor::Type::Last);

    std::ifstream f("Assets/Data/Armor.json");
    json armorData = json::parse(f)[Armor::typeToString(type)]["stats"];
    f.close();

    for (auto& el : statsKey) {
        if (armorData[el].is_null()) {
            armorData[el] = 0.0f;
        }
    }
    Ressources ressources;
    Stats stats = Stats(ressources, armorData);
    return Armor(type, stats);
}
