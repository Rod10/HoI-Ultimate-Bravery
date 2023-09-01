#include "special.hpp"

std::array<SpecialModule, 4> SpecialModule::generateSpecialModule() {
    auto statsKey = Stats::getStatsKeyArray();

    std::array<SpecialModule, 4> specialModules;

    std::vector<SpecialModule::Type> specialModuleType = {
        SpecialModule::Type::BasicRadio,
        SpecialModule::Type::ImprovedRadio,
        SpecialModule::Type::AdvancedRadio,
        SpecialModule::Type::MachineGuns,
        SpecialModule::Type::Amphibious,
        SpecialModule::Type::ArmorSkirts,
        SpecialModule::Type::AutoLoader,
        SpecialModule::Type::DozerBlade,
        SpecialModule::Type::Maintenance,
        SpecialModule::Type::ExtraAmmo,
        SpecialModule::Type::SloppedArmor,
        SpecialModule::Type::SmokeLauncher,
        SpecialModule::Type::Adaptor,
        SpecialModule::Type::Stabilizer,
        SpecialModule::Type::WetAmmo
    };

    std::ifstream fT("Assets/Data/Tank/Specials.json");
    json data = json::parse(fT);
    fT.close();

    bool hasAlreadyARadio = false;
    for (auto& specialModule : specialModules) {
        specialModule.type = *Utils::select_randomly(specialModuleType.begin(), specialModuleType.end());
        std::string specialModuleName = specialModule.typeToString(specialModule.type);
        json moduleData = data[specialModuleName];
        if (moduleData["onlyOne"] == true) {
            auto it = find(specialModuleType.begin(), specialModuleType.end(), static_cast<SpecialModule::Type>(specialModule.type));
            int index = it - specialModuleType.begin();
            specialModuleType.erase(specialModuleType.begin() + index);
        }
        if (specialModule.type == SpecialModule::BasicRadio
            || specialModule.type == SpecialModule::ImprovedRadio
            || specialModule.type == SpecialModule::AdvancedRadio) {
            specialModuleType.erase(specialModuleType.begin(), specialModuleType.begin() + 3);
        }
        json moduleStats = moduleData["stats"];
        for (auto& el : statsKey) {
            if (moduleStats[el].is_null()) {
                moduleStats[el] = 0.0f;
            }
        }
        Ressources moduleRessources = Ressources(moduleStats["ressources"]);
        specialModule.stats = Stats(moduleRessources, moduleStats);
    }

    return specialModules;
}