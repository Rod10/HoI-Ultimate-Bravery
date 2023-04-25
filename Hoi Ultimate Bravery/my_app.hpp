#include "app_base.hpp"

#include "gun.hpp"
#include "ressources.hpp"
#include "tank.hpp"
#include "turret.hpp"
#include "stats.hpp"
#include "utils.hpp"

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
            bool &windowOpen = gunCateogryWindowOpen.find(gunCategory)->second;
            //ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
            ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
            ImGui::Begin("Gun Category", &mainWindowOpen, ImGuiWindowFlags_NoCollapse);
            ImGui::Checkbox(MyApp::getLocalizedString(Utils::hash(Gun::gunCategoryToString(gunCategory).c_str())).c_str(), &windowOpen);
            ImGui::End();
        }
        ImGui::End();

        for (auto& [key, val] : gunCateogryWindowOpen)
        {
            if (val) {
                for (Gun gun : gunList) {
                    if (gun.category == key) {
                        Gun::Category cat = static_cast<Gun::Category>(gun.category);
                        auto catName = Gun::gunCategoryToString(cat);
                        auto hash = Utils::hash(catName.c_str());
                        auto stringToShow = MyApp::getLocalizedString(hash).c_str();
                        ImGui::Begin(stringToShow, &val);
                        ImGui::End();
                    }
                }
            }
        }
    }

private:
    bool mainWindowOpen = true;
    bool gunWindowCategoryOpen = true;
    std::vector<Gun> gunList = Gun::generateGunList();
    std::map<Gun::Category, bool> gunCateogryWindowOpen;
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