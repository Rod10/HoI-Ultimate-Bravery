#include <fstream>
#include <iomanip>
#include <iostream>

#include "Cannon.hpp"

std::vector<Gun> Gun::generateGunList()
{
    const std::string statsKey[13] = { "year", "speed", "reliability", "softAttack", "hardAttack", "piercing", "breakthrough", "airAttack", "productionCost", "armor", "defense", "entrenchment", "hardness" };

    Gun::Size gunSize = Gun::Size::Small;
    Gun::Category cannonCategory;
    std::vector<std::string> roleAllowed;
    std::ifstream fC("Assets/Data/Cannon.json");
    json CannonsData = json::parse(fC);
    fC.close();
    json cannonStats;
    Stats stats;
    Ressources gunRessources;
    std::vector<Gun> gunList;
    std::map<Gun::Type, Stats> statsByType;
    for (int cannonCategoryInt = Gun::Category::Cannon; cannonCategoryInt != Gun::Category::Last; cannonCategoryInt++) {
        cannonCategory = static_cast<Gun::Category>(cannonCategoryInt);
        const json cannonCateData = CannonsData[Gun::gunCategoryToString(cannonCategory)];
        for (auto& el : cannonCateData.items()) {
            for (auto& data : cannonCateData[el.key()].items()) {
                if (data.key() == "size") {
                    std::string stringSize = data.value();
                    gunSize = Gun::stringToGunSize(stringSize);
                }
                if (data.key() == "type") {
                    statsByType.clear();
                    for (auto& type : cannonCateData[el.key()][data.key()].items()) {
                        cannonStats = type.value();
                        for (auto& el : statsKey) {
                            if (cannonStats[el].is_null()) {
                                cannonStats[el] = 0;
                            }
                        }
                        gunRessources = Ressources(cannonStats["ressources"]);
                        stats = Stats(gunRessources, cannonStats);
                        std::string stringType = type.key();
                        statsByType.insert(std::pair<Gun::Type, Stats>(Gun::stringToGunType(stringType), stats));
                    }
                    std::cout << "map clear" << std::endl;
                }
                if (data.key() == "roleAllowed") {
                    for (auto& role : data.value()) {
                        roleAllowed.push_back(role);
                    }
                }
            }
            gunList.push_back(Gun(cannonCategory, gunSize, statsByType));
        }
    }
    return gunList;
}
