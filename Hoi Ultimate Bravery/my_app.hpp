#include "app_base.hpp"

#include "gun.hpp"
#include "ressources.hpp"
#include "special.hpp"
#include "stats.hpp"
#include "tank.hpp"
#include "turret.hpp"
#include "utils.hpp"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <json.hpp>
#include <locale>
#include <map>
#include <numbers>
#include <random>
#include <sstream>
#include <string>
#include <time.h>
using json = nlohmann::json;

class MyApp : public AppBase
{
public:
    MyApp()
    {}
    ~MyApp() = default;

    virtual void StartUp() final
    {
        std::ifstream infile("Assets/Data/Langages/en-en.csv");
        std::string line;
        std::vector<std::vector<std::string>> content;
        std::vector<std::string> row;
        while (std::getline(infile, line))
        {
            row.clear();
            std::stringstream iss(line);
            std::string token;
            char delimiter = ',';
            std::string value;
                while (std::getline(iss, value, ','))
                    row.push_back(value);
                content.push_back(row);
        }

        for (std::vector<std::string> pair : content) {
            int key = Utils::hash(pair[0].c_str());
            std::string translation = pair[1];
            localizedStrings.insert(std::pair<int, std::string>(key, translation));
        }

        for (int gunCategoryInt = Gun::Category::Cannon; gunCategoryInt != Gun::Category::Last; gunCategoryInt++) {
            Gun::Category gunCategory = static_cast<Gun::Category>(gunCategoryInt);
            gunCateogryWindowOpen.insert(std::pair<Gun::Category, bool>(gunCategory, false));
        }

        for (int gunNameInt = Gun::Name::SmallCannon; gunNameInt != Gun::Name::LastName; gunNameInt++) {
            Gun::Name gunName = static_cast<Gun::Name>(gunNameInt);
            gunNameWindowOpen.insert(std::pair<Gun::Name, bool>(gunName, false));
        }

        srand(time(0));
        Tank::Type tankType = static_cast<Tank::Type>(rand() % Tank::Type::Last);
        std::cout << "Tank Type: " << Tank::tankTypeToString(tankType) << std::endl;
        Turret turret = Turret::generatingRandomTurret(tankType);
        std::cout << "Turret Type: " << Turret::turretTypeToString(turret.type) << std::endl;
        std::vector<Gun> gunsCanBeUsed;        
        for (auto& [key, val] : gunList) {
            for (Gun gun : val) {
                if (std::find(turret.allowedGun.begin(), turret.allowedGun.end(), gun.size) != turret.allowedGun.end()) {
                    gunsCanBeUsed.push_back(gun);
                }
            }
        }

        Gun gun = *Utils::select_randomly(gunsCanBeUsed.begin(), gunsCanBeUsed.end());
        gun.stats = Utils::select_randomly(gun.statsByType.begin(), gun.statsByType.end())->second;
        gun.statsByType.clear();

        SpecialModule specialModules[4];

        for (auto& specialModule : specialModules) {
            specialModule.type = static_cast<SpecialModule::Type>(rand() % SpecialModule::Type::Last);
            std::cout << specialModule.type << std::endl;

            const std::string statsKey[13] = { "year", "speed", "reliability", "softAttack", "hardAttack", "piercing", "breakthrough", "airAttack", "productionCost", "armor", "defense", "entrenchment", "hardness" };
            json specialModuleStats;
            for (std::string el: statsKey) {
                for (auto& el : statsKey) {
                    if (specialModuleStats[el].is_null()) {
                        specialModuleStats[el] = 0;
                    }
                }
                Ressources ressources = Ressources(specialModuleStats["ressources"]);
                Stats stats = Stats(ressources, specialModuleStats);
                specialModule.stats = stats;
            }
        }

        Tank tank = Tank(tankType, turret, gun, specialModules);
    }

    virtual void Update() final
    {
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Main Window", &mainWindowOpen, 7 | ImGuiWindowFlags_NoInputs); // Create a window called "Hello, world!" and append into it.
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
        createLabelWithPosition("HoI Ultimate Bravery", MIDDLE);
        ImGui::PopStyleColor();

        for (int gunCategoryInt = Gun::Category::Cannon; gunCategoryInt != Gun::Category::Last; gunCategoryInt++)
        {
            Gun::Category gunCategory = static_cast<Gun::Category>(gunCategoryInt);
            auto catName = Gun::gunCategoryToString(gunCategory);
            auto hash = Utils::hash(catName.c_str());
            auto stringToShow = MyApp::getLocalizedString(hash);
            bool &windowOpen = gunCateogryWindowOpen.find(gunCategory)->second;
            auto size = ImGui::CalcTextSize(stringToShow.c_str()).x;
            ImGui::SetNextWindowPos(ImVec2(100.0f, 100.0f));
            ImGui::Begin("Gun Category", &mainWindowOpen, 7 | ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::Checkbox(MyApp::getLocalizedString(Utils::hash(Gun::gunCategoryToString(gunCategory).c_str())).c_str(), &windowOpen);
            ImGui::End();
        }
        ImGui::End();

        std::string stringToShow;
        for (auto& [key, val] : gunCateogryWindowOpen)
        {
            if (val) {
                auto& guns = gunList.find(key)->second;
                auto catName = Gun::gunCategoryToString(key);
                auto hash = Utils::hash(catName.c_str());
                stringToShow = MyApp::getLocalizedString(hash);
                ImGui::SetNextWindowPos(ImVec2(300.0f, 100.0f));
                ImGui::Begin(stringToShow.c_str(), &val, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
                createLabelWithPosition(stringToShow.c_str(), MIDDLE);
                for (Gun gun : guns) {
                    if (gun.category == key) {
                        auto gunNameString = Gun::gunNameToString(gun.name);
                        hash = Utils::hash(gunNameString.c_str());
                        stringToShow = MyApp::getLocalizedString(hash);
                        bool& windowOpen = gunNameWindowOpen.find(gun.name)->second;
                        ImGui::Checkbox(stringToShow.c_str(), &windowOpen);
                    }
                }
                ImGui::End();
            }
        }
    }

private:
    bool mainWindowOpen = true;
    bool gunWindowCategoryOpen = true;
    std::map<Gun::Category, std::vector<Gun>> gunList = Gun::generateGunList();
    std::map<Gun::Category, bool> gunCateogryWindowOpen;
    std::map<Gun::Name, bool> gunNameWindowOpen;
    std::unordered_map<int, std::string> localizedStrings;
    enum Position {
        LEFT = 000,
        MIDDLE = 500,
        RIGHT = 1000,
    };

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

    std::string getLocalizedString(int id) {
        return localizedStrings[id];
    }
};