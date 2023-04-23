#include "app_base.hpp"
#include "tank.hpp"
#include "Stats.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <numbers>
#include <random>
#include <time.h>
using json = nlohmann::json;

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

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
        std::cout << Tank::tankTypeToString(tankType) << std::endl;

        auto turretAllowed = Tank::getAllowedTurret(tankType); 
        Turret::Type turretType = *select_randomly(turretAllowed.begin(), turretAllowed.end());
        std::ifstream f("Assets/Data/Turret.json");
        json data = json::parse(f);
        json turretJson = data[Turret::turretTypeToString(turretType)]["crew"];
        std::cout << Turret::turretTypeToString(turretType) << std::endl;
        std::vector<std::string> turretCrew;
        for (auto& el : turretJson.items()) {
            turretCrew.push_back(el.key().c_str());
        }
        std::string crew = *select_randomly(turretCrew.begin(), turretCrew.end());
        json turretData = turretJson[crew];
        std::vector<Cannon::Size> allowedGun;
        for (auto& el : turretData["allowedGun"].items()) {
            allowedGun.push_back(static_cast<Cannon::Size>(std::stoi(el.key())));
        }
        json statsData = turretData["stats"];
        Ressources ressources = Ressources();
        Stats stats = Stats<Turret>(ressources, statsData);
        Turret turret = Turret(turretType, std::stoi(crew), allowedGun, stats);

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