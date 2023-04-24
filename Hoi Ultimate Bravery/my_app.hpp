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
        Turret turret = Turret::generatingRandomTurret(tankType);
        auto test = Gun::generateGunList();
        std::cout << "gun list generated" << std::endl;
        //TODO: Afficher GunCategoryfa
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