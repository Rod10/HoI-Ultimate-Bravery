#include "app_base.hpp"
#include "tank.hpp"
#include "turret.hpp"
#include "Stats.hpp"
#include "utils.hpp"
#include "Cannon.hpp"
#include "Ressources.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <json.hpp>
#include <map>
#include <numbers>
#include <random>
#include <time.h>
using json = nlohmann::json;

class MyApp : public AppBase
{
public:
    bool mainWindowOpen = true;
    enum Position {
        LEFT = 000,
        MIDDLE = 500,
        RIGHT = 1000,
    };

    MyApp()
    {
        srand(time(0));
        Tank::Type tankType = static_cast<Tank::Type>(rand() % Tank::Type::Last);
        std::cout << "Tank Type: " << Tank::tankTypeToString(tankType) << std::endl;

        //Turret
        /*auto turretAllowed = Tank::getAllowedTurret(tankType);
        Turret::Type turretType = *Utils::select_randomly(turretAllowed.begin(), turretAllowed.end());
        std::ifstream fT("Assets/Data/Turret.json");
        json data = json::parse(fT);
        fT.close();
        json turretJson = data[Turret::turretTypeToString(turretType)]["crew"];
        std::cout << "Turret Type: " << Turret::turretTypeToString(turretType) << std::endl;
        std::vector<std::string> turretCrew;
        for (auto& el : turretJson.items()) {
            turretCrew.push_back(el.key().c_str());
        }
        std::string crew = *Utils::select_randomly(turretCrew.begin(), turretCrew.end());
        json turretData = turretJson[crew];
        std::vector<Gun::Size> allowedGun;
        for (auto& el : turretData["allowedGun"].items()) {
            allowedGun.push_back(static_cast<Gun::Size>(std::stoi(el.key())));
        }

        //Turret Stats
        json turretStats = turretData["stats"];
        Ressources ressources = Ressources();
        const std::string statsKey[13] = { "year", "speed", "reliability", "softAttack", "hardAttack", "piercing", "breakthrough", "airAttack", "productionCost", "armor", "defense", "entrenchment", "hardness" };
        for (auto& el : statsKey) {
            if (turretStats[el].is_null()) {
                turretStats[el] = 0;
            }
        }
        Stats stats = Stats(ressources, turretStats);

        Turret turret = Turret(turretType, std::stoi(crew), allowedGun, stats);*/

        Turret turret = Turret::generatingRandomTurret(tankType);
        const std::string statsKey[13] = { "year", "speed", "reliability", "softAttack", "hardAttack", "piercing", "breakthrough", "airAttack", "productionCost", "armor", "defense", "entrenchment", "hardness" };

        //CannonList
        Gun::Size gunSize = Gun::Size::Small;
        Gun::Category cannonCategory;
        std::vector<std::string> roleAllowed;
        std::ifstream fC("Assets/Data/Cannon.json");
        json CannonsData = json::parse(fC);
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
                            std::cout << el.key() << ": " << type.key() << std::endl;
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

                //TODO: Afficher GunCategory
            }
        }
        fC.close();
    }
    ~MyApp() = default;

    virtual void StartUp() final
    {

    }

    virtual void Update() final
    {
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Main Window", &mainWindowOpen, 7); // Create a window called "Hello, world!" and append into it.
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
        createLabelWithPosition("HoI Ultimate Bravery", MIDDLE);
        ImGui::PopStyleColor();
        ImGui::End();
    }

    void createLabelWithPosition(const char* label, Position position)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * (position / 1000.f);
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        return ImGui::Text(label);
    }

private:
};