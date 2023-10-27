#include "armor.hpp"

Armor Armor::generateRandomArmor() {
    auto statsKey = TankStats::getStatsKeyArray();

    std::vector<Armor::Type> armorType;
    for (int i = 0; i < Armor::Type::Last; i++) {
        armorType.push_back(static_cast<Armor::Type>(i));
    }

    auto type = *Utils::select_randomly(armorType.begin(), armorType.end());

    std::ifstream f("Assets/Data/Tank/Armor.json");
    json armorData = json::parse(f)[Armor::typeToString(type)]["stats"];
    f.close();

    for (auto& el : statsKey) {
        if (armorData[el].is_null()) {
            armorData[el] = 0.0f;
        }
    }
    Ressources ressources;
    TankStats stats = TankStats(ressources, armorData);
    return Armor(type, stats);
}
