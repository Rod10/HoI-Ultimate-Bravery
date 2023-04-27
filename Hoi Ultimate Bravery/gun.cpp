#include <fstream>
#include <iomanip>
#include <iostream>

#include "gun.hpp"

std::map<Gun::Category, std::vector<Gun>> Gun::generateGunList()
{
    auto statsKey = Stats::getStatsKeyArray();

    Gun::Size gunSize = Gun::Size::Small;
    Gun::Category gunCategory;
    Gun::Name gunName;
    std::vector<std::string> roleAllowed;
    std::ifstream fC("Assets/Data/Cannon.json");
    json GunData = json::parse(fC);
    fC.close();
    json gunStats;
    Stats stats;
    Ressources gunRessources;
    std::vector<Gun> gunList;
    std::map<Gun::Category, std::vector<Gun>> catList;
    std::map<Gun::Type, Stats> statsByType;
    Gun gun;
    for (int gunCategoryInt = Gun::Category::Cannon; gunCategoryInt != Gun::Category::Last; gunCategoryInt++) {
        gunList.clear();
        gunCategory = static_cast<Gun::Category>(gunCategoryInt);
        const json gunCateData = GunData[Gun::gunCategoryToString(gunCategory)];
        for (auto& el : gunCateData.items()) {
            std::string gunNameString = el.key();
            gunName = Gun::stringNameToGunName(gunNameString);
            for (auto& data : gunCateData[el.key()].items()) {
                if (data.key() == "size") {
                    std::string stringSize = data.value();
                    gunSize = Gun::stringToGunSize(stringSize);
                }
                if (data.key() == "type") {
                    statsByType.clear();
                    for (auto& type : gunCateData[el.key()][data.key()].items()) {
                        gunStats = type.value();
                        for (auto& el : statsKey) {
                            if (gunStats[el].is_null()) {
                                gunStats[el] = 0.0f;
                            }
                        }
                        gunRessources = Ressources(gunStats["ressources"]);
                        stats = Stats(gunRessources, gunStats);
                        std::string stringType = type.key();
                        statsByType.insert(std::pair<Gun::Type, Stats>(Gun::stringToGunType(stringType), stats));
                    }
                }
                if (data.key() == "roleAllowed") {
                    for (auto& role : data.value()) {
                        roleAllowed.push_back(role);
                    }
                }
            }
            gunList.push_back(Gun(gunCategory, gunName, gunSize, statsByType));
        }
        catList.insert(std::pair<Gun::Category, std::vector<Gun>>(gunCategory, gunList));
    }
    return catList;
}

std::string Gun::getLongestTextByCate(Gun::Category category)
{
    const std::string string[6] = { "superHeavyCannon", "flamethrowers", "fastFiringAntiGround", "highVelocityMedium" ,"closeSupportGun", "antiAirMedium" };
    return string[category];
}
