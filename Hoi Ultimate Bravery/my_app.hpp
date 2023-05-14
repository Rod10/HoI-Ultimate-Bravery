#include "app_base.hpp"

#include "armor.hpp"
#include "country.hpp"
#include "engine.hpp"
#include "gun.hpp"
#include "settings.hpp"
#include "special.hpp"
#include "suspension.hpp"
#include "tank.hpp"
#include "tanktype.hpp"
#include "texture.hpp"
#include "turret.hpp"
#include "turrettype.hpp"
#include "utils.hpp"

#include "imgui_stdlib.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <filesystem>
#include <format>
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
    ~MyApp() {
        std::string src("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\history\\countries\\GER - Germany.txt");
        std::remove(src.c_str());
        std::string backUp("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\history\\countries\\GER - Germany.txt.back");
        if(std::rename(backUp.c_str(), src.c_str()) != 0) {
            perror("Error moving file");
        }
        else {
            std::cout << "File moved successfully" << std::endl;
        };
        src = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\common\\ideas\\GER.txt";
        std::remove(src.c_str());
        backUp = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\common\\ideas\\GER.txt.back";
        if(std::rename(backUp.c_str(), src.c_str()) != 0) {
            perror("Error moving file");
        }
        else {
            std::cout << "File moved successfully" << std::endl;
        };
    };

    virtual void StartUp() final
    {
        auto statsKey = Stats::getStatsKeyArray();

        /*std::ifstream infile("Assets/Data/Langages/en-en.csv");
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
        }*/

        for (int gunCategoryInt = Gun::Category::Cannon; gunCategoryInt != Gun::Category::Last; gunCategoryInt++) {
            Gun::Category gunCategory = static_cast<Gun::Category>(gunCategoryInt);
            gunCateogryWindowOpen.insert(std::pair<Gun::Category, bool>(gunCategory, false));
        }

        for (int gunNameInt = Gun::Name::SmallCannon; gunNameInt != Gun::Name::LastName; gunNameInt++) {
            Gun::Name gunName = static_cast<Gun::Name>(gunNameInt);
            gunNameWindowOpen.insert(std::pair<Gun::Name, bool>(gunName, false));
        }

        std::map<std::string, Texture> textureCategory;
        fileName = std::format("./Assets/Images/Background/tank_designer_bg.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        Texture texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureCategory.insert(std::pair<std::string, Texture>("tank_designer_bg", texture));

        fileName = std::format("./Assets/Images/Background/tank_name_bg.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureCategory.insert(std::pair<std::string, Texture>("tank_name_bg", texture));

        fileName = std::format("./Assets/Images/Background/tank_role_bg.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureCategory.insert(std::pair<std::string, Texture>("tank_role_bg", texture));

        fileName = std::format("./Assets/Images/Background/equipment_icon_bg.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        texture.my_image_width = 154;
        texture.my_image_height = 56;
        textureCategory.insert(std::pair<std::string, Texture>("tank_icon_bg", texture));

        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureCategory.insert(std::pair<std::string, Texture>("equipment_icon_bg", texture));

        fileName = std::format("./Assets/Images/Background/tank_blueprint_background.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureCategory.insert(std::pair<std::string, Texture>("tank_blueprint_background", texture));

        textures.insert(std::pair<std::string, std::map<std::string, Texture>>("background", textureCategory));
        textureCategory.clear();

        std::string path = "./Assets/Images/Blueprint/";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        textures.insert(std::pair<std::string, std::map<std::string, Texture>>("blueprint", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Modules/Cannon";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        path = "./Assets/Images/Modules/Turret";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        path = "./Assets/Images/Modules/Special";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        path = "./Assets/Images/Modules/Suspension";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        path = "./Assets/Images/Modules/Armor";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        path = "./Assets/Images/Modules/Engine";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        textures.insert(std::pair<std::string, std::map<std::string, Texture>>("modules", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Icon/Light";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        tankIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("light", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Icon/Medium";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        tankIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("medium", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Icon/Heavy";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        tankIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("heavy", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Icon/SuperHeavy";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        tankIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("superHeavy", textureCategory));
        textureCategory.clear();

        path = "./Assets/Images/Icon/Modern";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureCategory.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

        tankIconTextures.insert(std::pair<std::string, std::map<std::string, Texture>>("modern", textureCategory));
        textureCategory.clear();

        srand(time(0));
    }

    virtual void Update() final
    {
        ImGuiIO& io = ImGui::GetIO();
        ImFont* basicFont = io.Fonts->Fonts[0];
        ImFont* titleFont = io.Fonts->Fonts[1];
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::PushFont(titleFont);
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(59, 65, 57, 255));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor);
        ImGui::Begin("Main Window", &mainWindowOpen, 7 | ImGuiWindowFlags_NoInputs); // Create a window called "Hello, world!" and append into it.
        createLabelWithPosition("HoI Ultimate Bravery", MIDDLE);
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopFont();

        auto off = calculatePos(MIDDLE, "generate");

        // Main Menu Block
        if (mainMenuOpen) {
            ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, windowColor);
            ImGui::Begin("generate", &mainMenuOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::PopStyleColor();
            ImGui::PushFont(basicFont);
            ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
            if (createButtonlWithPosition("Generate", MIDDLE)) {
                mainMenuOpen = false;
                generateWindowOpen = true;
            }
            if (createButtonlWithPosition("Option", MIDDLE)) {
                mainMenuOpen = false;
                optionWindowOpen = true;
            }
            if (createButtonlWithPosition("Quit", MIDDLE)) {
                exit(1);
            }
            ImGui::PopStyleColor();
            ImGui::PopFont();
            ImGui::End();
        }
        // Main Menu Block

        // Generate Menu
        if (generateWindowOpen) {
            auto off = calculatePos(MIDDLE, "Tank: Light Medium Heavy Super Heavy Modern");
            ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, windowColor);
            ImGui::Begin("generate", &generateWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::PopStyleColor();
            createLabelWithPosition("Generate", MIDDLE);

            off = calculatePos(MIDDLE, "Country: ");
            createLabelWithPosition("Country: ", off, ImGui::GetCursorPosY() + 10.0f);
            ImGui::SameLine();
            static ImGuiComboFlags flags = 0;
            static int item_current_idx = 0; // Here we store our selection data as an index.
            const char* combo_preview_value = countryList[item_current_idx].name.c_str();  // Pass in the preview value visible before opening the combo (it could be anything)
            if (ImGui::BeginCombo("##", combo_preview_value, flags))
            {
                for (int n = 0; n < countryList.size(); n++)
                {
                    const bool is_selected = (item_current_idx == n);
                    if (ImGui::Selectable(countryList[n].name.c_str(), is_selected)) {
                        item_current_idx = n;
                        country = &countryList[n];
                    }

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);

            createLabelWithPosition("Tank: ", LEFT);
            ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
            ImGuiStyle& style = ImGui::GetStyle();
            float width = 0.0f;
            width += ImGui::CalcTextSize("Tank: ").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize("Light").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize("Medium").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize("Heavy").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize("Super Heavy").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize("Modern").x;
            AlignForWidth(width);
            ImGui::SameLine();
            if (ImGui::Button("Light")) {
                typeToShow = TankType::Type::Light;
                Tank tank = Tank::generateRandomTank(TankType::Type::Light);
                tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Light, tank));

                newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Light, generateNewStats(tank)));

                auto& icon = tankIconTextures.find(Tank::tankTypeToString(tank.type))->second;
                auto it = icon.cbegin();
                int random = rand() % icon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("light", it->first));

                designerWindowOpen = true;
                generateWindowOpen = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Medium")) {
                typeToShow = TankType::Type::Medium;
                Tank tank = Tank::generateRandomTank(TankType::Type::Medium);
                tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Medium, tank));

                newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Medium, generateNewStats(tank)));

                auto& icon = tankIconTextures.find(Tank::tankTypeToString(tank.type))->second;
                auto it = icon.cbegin();
                int random = rand() % icon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("medium", it->first));

                designerWindowOpen = true;
                generateWindowOpen = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Heavy")) {
                typeToShow = TankType::Type::Heavy;
                Tank tank = Tank::generateRandomTank(TankType::Type::Heavy);
                tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Heavy, tank));

                newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Heavy, generateNewStats(tank)));

                auto& icon = tankIconTextures.find(Tank::tankTypeToString(tank.type))->second;
                auto it = icon.cbegin();
                int random = rand() % icon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("heavy", it->first));

                designerWindowOpen = true;
                generateWindowOpen = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Super Heavy")) {
                typeToShow = TankType::Type::SuperHeavy;
                Tank tank = Tank::generateRandomTank(TankType::Type::SuperHeavy);
                tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::SuperHeavy, tank));

                newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::SuperHeavy, generateNewStats(tank)));

                auto& icon = tankIconTextures.find(Tank::tankTypeToString(tank.type))->second;
                auto it = icon.cbegin();
                int random = rand() % icon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("superHeavy", it->first));

                designerWindowOpen = true;
                generateWindowOpen = false;
            }
            ImGui::SameLine();
            if (ImGui::Button("Modern")) {
                typeToShow = TankType::Type::Modern;
                Tank tank = Tank::generateRandomTank(TankType::Type::Modern);
                tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Modern, tank));

                newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Modern, generateNewStats(tank)));

                auto& icon = tankIconTextures.find(Tank::tankTypeToString(tank.type))->second;
                auto it = icon.cbegin();
                int random = rand() % icon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("modern", it->first));

                designerWindowOpen = true;
                generateWindowOpen = false;
            }
            if (createButtonlWithPosition("Full Random", MIDDLE)) {
                Tank lightTank = Tank::generateRandomTank(TankType::Type::Light);
                tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Light, lightTank));

                Tank mediumTank = Tank::generateRandomTank(TankType::Type::Medium);
                tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Medium, mediumTank));

                Tank heavyTank = Tank::generateRandomTank(TankType::Type::Heavy);
                tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Heavy, heavyTank));

                Tank superHeavyTank = Tank::generateRandomTank(TankType::Type::SuperHeavy);
                tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::SuperHeavy, superHeavyTank));

                Tank modernTank = Tank::generateRandomTank(TankType::Type::Modern);
                tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Modern, modernTank));

                newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Light, generateNewStats(lightTank)));
                newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Medium, generateNewStats(mediumTank)));
                newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Heavy, generateNewStats(heavyTank)));
                newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::SuperHeavy, generateNewStats(superHeavyTank)));
                newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Modern, generateNewStats(modernTank)));

                auto& lightIcon = tankIconTextures.find(Tank::tankTypeToString(lightTank.type))->second;
                auto it = lightIcon.cbegin();
                int random = rand() % lightIcon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("light", it->first));

                auto& mediumIcon = tankIconTextures.find(Tank::tankTypeToString(mediumTank.type))->second;
                it = mediumIcon.cbegin();
                random = rand() % mediumIcon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("medium", it->first));

                auto& heavyIcon = tankIconTextures.find(Tank::tankTypeToString(heavyTank.type))->second;
                it = heavyIcon.cbegin();
                random = rand() % heavyIcon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("heavy", it->first));

                auto& superHeavyIcon = tankIconTextures.find(Tank::tankTypeToString(superHeavyTank.type))->second;
                it = superHeavyIcon.cbegin();
                random = rand() % superHeavyIcon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("superHeavy", it->first));

                auto& modernIcon = tankIconTextures.find(Tank::tankTypeToString(modernTank.type))->second;
                it = modernIcon.cbegin();
                random = rand() % modernIcon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("modern", it->first));

                allGenerationWindowOpen = true;
                generateWindowOpen = false;

            }

            if (createButtonlWithPosition("Back", MIDDLE)) {
                mainMenuOpen = true;
                generateWindowOpen = false;
            }
            ImGui::PopStyleColor();
            ImGui::End();
        }
        // Generate Menu

        //By Type
        if (designerWindowOpen) {
            generateTankDesignerWindow(tankList.find(typeToShow)->second);
            showStats();
            
            ImGui::SetCursorPosY(515.0f);
            ImGuiStyle& style = ImGui::GetStyle();
            float width = 0.0f;
            width += ImGui::CalcTextSize("Import into game").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize("Regenerate").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize("Back").x;
            width += style.ItemSpacing.x;
            AlignForWidth(width);
            if (ImGui::Button("Import into game")) {
                generateCountryFile();
                generateIdeaFile();
            }
            ImGui::SameLine();
            if (ImGui::Button("Regenerate")) {
                tankList.find(typeToShow)->second = Tank::generateRandomTank(typeToShow);
                newTankStats.find(typeToShow)->second = generateNewStats(tankList.find(typeToShow)->second);

                auto& icon = tankIconTextures.find(Tank::tankTypeToString(typeToShow))->second;
                auto it = icon.cbegin();
                int random = rand() % icon.size();
                std::advance(it, random);

                tankIconNames[Tank::tankTypeToString(typeToShow)] = it->first;
            }
            ImGui::SameLine();
            if (ImGui::Button("Back")) {
                generateWindowOpen = true;
                designerWindowOpen = false;
            }

            ImGui::PopStyleColor();
            ImGui::PopFont();
            ImGui::End();
        }
        //By Type

        //All Type
        if (allGenerationWindowOpen) {
            ImGui::Begin("generate", &designerWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
            int posMult = 250;
            for (auto& [type, tank] : tankList) {
                ImGui::SetNextWindowPos(ImVec2(posMult, 200.0f));
                ImGui::Begin(Tank::tankTypeToString(tank.type).c_str(), &designerWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
                createLabelWithPosition(Tank::tankTypeToString(tank.type).c_str(), MIDDLE);
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
                ImGuiIO& io = ImGui::GetIO();
                createLabelWithPosition(std::format("{0} {1}", Gun::gunNameToString(tank.gun.name), Gun::typeToString(tank.gun.type)).c_str(), LEFT);
                createLabelWithPosition(std::format("{0} {1}", TurretType::turretTypeToString(tank.turret.type), tank.turret.crew).c_str(), LEFT);
                createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[0].type).c_str(), LEFT);
                createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[1].type).c_str(), LEFT);
                createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[2].type).c_str(), LEFT);
                createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[3].type).c_str(), LEFT);
                createLabelWithPosition(Suspension::typeToString(tank.suspension.type).c_str(), LEFT);
                createLabelWithPosition(Armor::typeToString(tank.armor.type).c_str(), LEFT);
                createLabelWithPosition(Engine::typeToString(tank.engine.type).c_str(), LEFT);
                createLabelWithPosition(std::format("Armor: {0}", tank.armorLevel).c_str(), LEFT);
                createLabelWithPosition(std::format("Engine: {0}", tank.engineLevel).c_str(), LEFT);
                posMult += 250;
                ImGui::PopStyleColor();
                ImGui::End();
            }
            ImGui::SetCursorPosY(515.0f);
            ImGuiStyle& style = ImGui::GetStyle();
            ImGui::PushFont(basicFont);
            float width = 0.0f;
            width += ImGui::CalcTextSize("Import into game").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize("Regenerate").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize("Back").x;
            width += style.ItemSpacing.x;
            AlignForWidth(width);
            if (ImGui::Button("Import into game")) {
                /*generateCountryFile();*/std::vector<std::string> fileLines;

                std::ifstream  src("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\history\\countries\\GER - Germany.txt", std::ios::binary);
                std::ofstream  backUp("./Assets/Data/GER - Germany.txt.back", std::ios::binary);
                std::ofstream  newFile("./Assets/Data/GER - Germany.txt", std::ios::binary);
                std::string line;
                while (std::getline(src, line)) {
                    fileLines.push_back(line);
                }
                src.close();
                if (std::rename("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\history\\countries\\GER - Germany.txt",
                    "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\history\\countries\\GER - Germany.txt.back") != 0)
                    perror("Error moving file");
                else
                    std::cout << "File moved successfully" << std::endl;

                for (auto& line : fileLines) {
                    backUp << line << std::endl;
                }
                backUp.close();
                fileLines.insert(fileLines.begin() + 394, "ultimate_bravery");
                int linesToDeleteStart = 561;
                int linesToDeleteEnd = 638;
                int lineToDeleteCount = linesToDeleteEnd - linesToDeleteStart;

                std::vector<std::string> tempLine = fileLines;

                for (int i = 0; i < fileLines.size(); i++) {
                    if (i >= linesToDeleteStart && i <= linesToDeleteEnd && lineToDeleteCount != 0) {
                        fileLines.erase(fileLines.begin() + 561);
                        lineToDeleteCount--;
                    }
                }


                std::vector<std::string> templateLine;
                int counterTemplateLine = 0;

                std::ifstream templateFile("./Assets/Data/equipment_template.txt", std::ios::binary);
                int index;
                for (auto& [type, tank] : tankList) {
                    std::vector<std::string> replacementList{ "Test",
                        std::format("{0}_{1}_chassis_{2}", Tank::tankTypeToString(tankList.find(type)->second.type), Role::typeToString(tankList.find(type)->second.role), Tank::tankVersionToInt(tankList.find(type)->second.version)),
                        converterToGameName.find(Utils::hash(std::format("{0}_{1}", Gun::gunNameToString(tankList.find(type)->second.gun.name), Gun::typeToString(tankList.find(type)->second.gun.type)).c_str()))->second,
                        converterToGameName.find(Utils::hash(std::format("{0}_{1}", TurretType::turretTypeToString(tankList.find(type)->second.turret.type), tankList.find(type)->second.turret.crew).c_str()))->second,
                        converterToGameName.find(Utils::hash(Suspension::typeToString(tankList.find(type)->second.suspension.type).c_str()))->second,
                        converterToGameName.find(Utils::hash(Armor::typeToString(tankList.find(type)->second.armor.type).c_str()))->second,
                        converterToGameName.find(Utils::hash(Engine::typeToString(tankList.find(type)->second.engine.type).c_str()))->second,
                        converterToGameName.find(Utils::hash(SpecialModule::typeToString(tankList.find(type)->second.specialModules[0].type).c_str()))->second,
                        converterToGameName.find(Utils::hash(SpecialModule::typeToString(tankList.find(type)->second.specialModules[1].type).c_str()))->second,
                        converterToGameName.find(Utils::hash(SpecialModule::typeToString(tankList.find(type)->second.specialModules[2].type).c_str()))->second,
                        converterToGameName.find(Utils::hash(SpecialModule::typeToString(tankList.find(type)->second.specialModules[3].type).c_str()))->second,
                        std::to_string(tankList.find(type)->second.engineLevel),
                        std::to_string(tankList.find(type)->second.armorLevel),
                    };
                    std::vector<std::string> tokenList{ "%tankName%",
                        "%tankTypeVersion%",
                        "%gunName%",
                        "%turretName%",
                        "%suspensionName%",
                        "%armorName%",
                        "%engineName%",
                        "%specialName_1%",
                        "%specialName_2%",
                        "%specialName_3%",
                        "%specialName_4%",
                        "%engineUpgrade%",
                        "%armorUpgrade%" };
                    while (std::getline(templateFile, line)) {
                        for (int i = 0; i < tokenList.size(); i++) {
                            while ((index = line.find(tokenList[i])) != std::string::npos) {
                                line.replace(line.find(tokenList[i]), tokenList[i].length(), replacementList[i]);
                            }
                        }
                        templateLine.push_back(line);
                    }
                }

                for (int i = 0; i < fileLines.size(); i++) {
                    if (i >= linesToDeleteStart && counterTemplateLine < templateLine.size()) {
                        fileLines.insert(fileLines.begin() + i, templateLine[counterTemplateLine]);
                        counterTemplateLine++;
                    }
                }


                for (int i = 0; i < fileLines.size(); i++) {
                    newFile << fileLines[i] << std::endl;
                }
                newFile.close();
                /*if (std::rename("./Assets/Data/GER - Germany.txt",
                    "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\history\\countries\\GER - Germany.txt") != 0) {
                    perror("Error moving file");
                }
                else {
                    std::cout << "File moved successfully" << std::endl;
                };*/

                
                //generateIdeaFile();
            }
            ImGui::SameLine();
            if (ImGui::Button("Regenerate")) {
                /*tankList.find(typeToShow)->second = Tank::generateRandomTank(typeToShow);
                newTankStats.find(typeToShow)->second = generateNewStats(tankList.find(typeToShow)->second);

                auto& icon = tankIconTextures.find(Tank::tankTypeToString(typeToShow))->second;
                auto it = icon.cbegin();
                int random = rand() % icon.size();
                std::advance(it, random);

                tankIconNames[Tank::tankTypeToString(typeToShow)] = it->first;*/
            }
            ImGui::SameLine();
            if (ImGui::Button("Back")) {
                std::cout << "back" << std::endl;
                generateWindowOpen = true;
                allGenerationWindowOpen = false;
            }
            ImGui::PopFont();   
            ImGui::End();
        }
        //All Type

        // Options
        if (optionWindowOpen) {
            off = calculatePos(MIDDLE, 250);
            ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
            ImGui::Begin("options", &optionWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
            createLabelWithPosition("Options", MIDDLE);

            ImGui::Text("Game Path: ");
            ImGuiStyle& style = ImGui::GetStyle();
            float width = 0.0f;
            width += ImGui::CalcTextSize("Game Path: ").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize(settings.gamePath.data()).x;
            width += style.ItemSpacing.x;
            AlignForWidth(width);
            ImGui::SameLine();
            std::string *gamePath = &settings.gamePath;
            ImGui::InputText("##", gamePath);

            width = 0.0f;
            width += ImGui::CalcTextSize("Save").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize("Back").x;
            width += style.ItemSpacing.x;
            AlignForWidth(width);
            if (ImGui::Button("Save")) {
                json settingsFile;
                settingsFile["gamePath"] = *gamePath;
                std::ofstream file("Assets/Data/Settings.json");
                file << settingsFile;
            }
            ImGui::SameLine();
            if (ImGui::Button("Back")) {
                mainMenuOpen = true;
                optionWindowOpen = false;
            }
            ImGui::End();
        }
        // Options

        ImGui::End();
    }

private:
    TankType::Type typeToShow;
    std::map<TankType::Type, Tank> tankList;
    std::unordered_map<TankType::Type, Stats> newTankStats;
    std::vector<std::string> tankModule = { "gun", "turret", "suspension", "engine", "armor" };
    std::vector<Country> countryList = Country::generateCountryList();
    Country* country;
    Settings settings;

    const float TITLE_HEIGHT = 24.0f;
    const float TANK_NAME_HEIGHT = 63.0f;
    const float TANK_ROLE_HEIGHT = 106.0f;
    const float TANK_MODULE_HEIGHT = 155.0f;
    const float TANK_MODULE_HEIGHT_2 = 455.0f;
    const float BASE_STATS_POS = 720.0f;
    const float COMBAT_STATS_POS = 895.0f;
    const float MISC_STATS_POS = 910.0f;

    bool mainWindowOpen = true;
    bool mainMenuOpen = true;
    bool generateWindowOpen = false;
    bool optionWindowOpen = false;
    bool designerWindowOpen = false;
    bool allGenerationWindowOpen = false;

    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    std::string fileName;
    bool ret;
    std::map<std::string, std::map<std::string, Texture>> textures;
    std::map<std::string, std::map<std::string, Texture>> tankIconTextures;
    std::map<std::string, std::string> tankIconNames;

    std::map<Gun::Category, std::vector<Gun>> gunList = Gun::generateGunList();
    std::map<Gun::Category, bool> gunCateogryWindowOpen;
    std::map<Gun::Name, bool> gunNameWindowOpen;

    std::unordered_map<int, std::string> localizedStrings = Utils::loadTranslation("Assets/Data/Langages/en-en.csv");
    std::unordered_map<int, std::string> converterToGameName = Utils::loadTranslation("Assets/Data/converter.csv");

    enum Position {
        LEFT = 000,
        MIDDLE = 500,
        RIGHT = 1000,
    };

    ImVec4 backgroundColor = ImVec4(0.831f, 0.902f, 0.945f, 1.00f);
    ImVec4 windowColor = ImVec4(0.149f, 0.137f, 0.125f, 1.00f);
    ImVec4 buttonColor = ImVec4(0.231f, 0.255f, 0.224f, 1.00f);

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

    void createLabelWithPosition(const char* label, Position position, ImGuiInputTextFlags_ flag)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * (position / 1000.f);
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        return ImGui::Text(label, flag);
    }

    void createLabelWithPosition(const char* label, float x, float y)
    {
        ImGui::SetCursorPosY(y);
        ImGui::SetCursorPosX(x - ImGui::CalcTextSize(label).x);
        return ImGui::Text(label);
    }

    void createTitleWithPosition(const char* label, float x, float y)
    {
        ImGui::SetCursorPosY(y);
        ImGui::SetCursorPosX(x);
        return ImGui::Text(label);
    }

    bool createButtonlWithPosition(const char* label, Position position)
    {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * (position / 1000.f);
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

        return ImGui::Button(label);
    }

    float calculatePos(Position position, std::string text) {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = ImGui::CalcTextSize(text.c_str()).x - style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * (position / 1000.f);
        return off;
    }

    float calculatePos(Position position, int width) {
        ImGuiStyle& style = ImGui::GetStyle();

        float size = width - style.FramePadding.x * 2.0f;
        float avail = ImGui::GetContentRegionAvail().x;

        float off = (avail - size) * (position / 1000.f);
        return off;
    }

    std::string getLocalizedString(int id) {
        return localizedStrings[id];
    }

    void AlignForWidth(float width, float alignment = 0.5f)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        float avail = ImGui::GetContentRegionAvail().x;
        float off = (avail - width) * alignment;
        if (off > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
    }

    void setImage(float y, float x, std::string type, std::string name) {
        ImGui::SetCursorPosY(y);
        ImGui::SetCursorPosX(x);
        Texture texture = textures.find(type)->second.find(name)->second;
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
    }

    void setIcon(float y, float x, std::string type, std::string name) {
        ImGui::SetCursorPosY(y);
        ImGui::SetCursorPosX(x);
        Texture texture = tankIconTextures.find(type)->second.find(name)->second;
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
    }

    void generateTankDesignerWindow(Tank tank) {
        ImGuiIO& io = ImGui::GetIO();
        ImFont* basicFont = io.Fonts->Fonts[0];
        ImFont* titleFont = io.Fonts->Fonts[1];
        ImFont* textFont = io.Fonts->Fonts[2];
        ImFont* TitleStatsFont = io.Fonts->Fonts[3];
        ImFont* statsFont = io.Fonts->Fonts[4];
        Texture texture = textures.find("background")->second.find("tank_designer_bg")->second;
        auto off = calculatePos(MIDDLE, texture.my_image_width);
        ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
        ImGui::Begin(Tank::tankTypeToString(tank.type).c_str(), &designerWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PushFont(titleFont);
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
        ImGui::SetCursorPosY(TITLE_HEIGHT);
        createLabelWithPosition("Equipment Designer", MIDDLE);
        ImGui::PopFont();
        ImGui::PopStyleColor();

        setImage(TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "tank_name_bg");

        setImage(79.8, 329, "background", "tank_icon_bg");

        setImage(TANK_ROLE_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "tank_role_bg");

        for (int i = 0; i <= 5; i++) {
            float x = ImGui::GetCursorPosX() + (76 * i) + (13.0f - (i * 3));
            if (i == 0) {
                x = 23.0f;
            }
            setImage(TANK_MODULE_HEIGHT, x, "background", "equipment_icon_bg");
        }

        setImage(ImGui::GetCursorPosY() - 4.0f, ImGui::GetCursorPosX() + 16.0f, "background", "tank_blueprint_background");

        texture = textures.find("background")->second.find("equipment_icon_bg")->second;
        for (int i = 0; i <= 2; i++) {
            float x = ImGui::GetCursorPosX() + (76 * i) + (12.0f - (i * 3));
            if (i == 0) {
                x = 23.0f;
            }
            setImage(TANK_MODULE_HEIGHT_2, x, "background", "equipment_icon_bg");
        }
        ImGui::PushFont(TitleStatsFont);
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
        createTitleWithPosition("Base Stats", MIDDLE + 60.0f, TITLE_HEIGHT + 29.0f);
        createTitleWithPosition("Combat Stats", MIDDLE + 235.0f, TITLE_HEIGHT + 29.0f);
        createTitleWithPosition("Misc. Stats", MIDDLE + 410.0f, TITLE_HEIGHT + 29.0f);
        ImGui::PopFont();

        //Base Stats 
        ImGui::PushFont(statsFont);
        createTitleWithPosition("Max Speed:", MIDDLE + 60.0f, TITLE_HEIGHT + 60.0f);
        createTitleWithPosition("Reliability:", MIDDLE + 60.0f, TITLE_HEIGHT + 80.0f);
        createTitleWithPosition("Supply use:", MIDDLE + 60.0f, TITLE_HEIGHT + 100.0f);
        //Base Stats 

        //Combat Stats 
        createTitleWithPosition("Soft attack:", MIDDLE + 235.0f, TITLE_HEIGHT + 60.0f);
        createTitleWithPosition("Hard attack:", MIDDLE + 235.0f, TITLE_HEIGHT + 80.0f);
        createTitleWithPosition("Piercing:", MIDDLE + 235.0f, TITLE_HEIGHT + 100.0f);
        createTitleWithPosition("Hardness:", MIDDLE + 235.0f, TITLE_HEIGHT + 120.0f);
        createTitleWithPosition("Armor:", MIDDLE + 235.0f, TITLE_HEIGHT + 140.0f);
        createTitleWithPosition("Breakthrough:", MIDDLE + 235.0f, TITLE_HEIGHT + 160.0f);
        createTitleWithPosition("Defense:", MIDDLE + 235.0f, TITLE_HEIGHT + 180.0f);
        createTitleWithPosition("Air attack:", MIDDLE + 235.0f, TITLE_HEIGHT + 200.0f);
        //Combat Stats

        //Misc. Stats
        createTitleWithPosition("Fuel Capacity:", MIDDLE + 410.0f, TITLE_HEIGHT + 60.0f);
        createTitleWithPosition("Fuel Usage:", MIDDLE + 410.0f, TITLE_HEIGHT + 80.0f);
        createTitleWithPosition("Suppression:", MIDDLE + 410.0f, TITLE_HEIGHT + 100.0f);
        createTitleWithPosition("Reconnaissance:", MIDDLE + 410.0f, TITLE_HEIGHT + 120.0f);
        createTitleWithPosition("Entrenchment:", MIDDLE + 410.0f, TITLE_HEIGHT + 140.0f);
        //Misc. Stats

        ImGui::PopFont();
        ImGui::PopStyleColor();

        ImGui::PushFont(textFont);
        createTitleWithPosition("Engine", MIDDLE - 100.0f, TANK_MODULE_HEIGHT_2);
        createTitleWithPosition("Armor", MIDDLE - 20.0f, TANK_MODULE_HEIGHT_2);
        ImGui::PopFont();

        ImGui::End();
    }

    Stats getStats(Tank tank, std::string module) {
        switch (tank.tankModuleToInt(module)) {
        case 0: return Stats(tank.gun.stats);
        case 1: return Stats(tank.turret.stats);
        case 2: return Stats(tank.suspension.stats);
        case 3: return Stats(tank.armor.stats);
        case 4: return Stats(tank.engine.stats);
        }
    }

    Stats generateNewStats(Tank tank) {
        Stats stats;
        Stats newStats = tank.stats;

        for (auto& module : tankModule) {
            stats = getStats(tank, module);
            newStats += stats;
        }

        //Add Stats of special modules
        for (const SpecialModule& module : tank.specialModules) {
            newStats += module.stats;
        }
        //Add Stats of special modules

        // Base Stats
        float totalSpeedP = newStats.speedP + (tank.engineLevel * 10) + (tank.armorLevel * -5.0);
        float reliabilityP = newStats.reliabilityP + (tank.engineLevel * -1.5) + (tank.armorLevel * 1.5);
        float speedf = newStats.speed + (newStats.speed * (totalSpeedP / 100));
        newStats.speed = speedf;

        float reliabilityf = newStats.reliability + reliabilityP;
        newStats.reliability = reliabilityf;
        //Base Stats

        //Combat Stats
        float softAttackF = newStats.softAttack + (newStats.softAttack * (newStats.softAttackP / 100));
        newStats.softAttack = softAttackF;

        float hardAttackF = newStats.hardAttack + (newStats.hardAttack * (newStats.hardAttackP / 100));
        newStats.hardAttack = hardAttackF;

        float piercingF = newStats.piercing + (newStats.piercing * (newStats.piercingP / 100));
        newStats.piercing = piercingF;

        float hardnessF = newStats.hardness + (newStats.hardness * (newStats.hardnessP / 100));
        newStats.hardness = hardnessF;

        float totalArmorP = newStats.armorP + (tank.armorLevel * 8.5);
        float armorF = newStats.armor + (newStats.armor * (totalArmorP / 100));
        newStats.armor = armorF;

        float totalBreakthroughF = newStats.breakthrough + tank.armorLevel * 1.2;
        float breakthroughF = totalBreakthroughF + (totalBreakthroughF * (newStats.breakthroughP / 100));
        newStats.breakthrough = breakthroughF;

        float defenseF = newStats.defense + (newStats.defense * (newStats.defenseP / 100));
        newStats.defense = defenseF;

        float airAttackF = newStats.airAttack + (newStats.airAttack * (newStats.airAttackP / 100));
        newStats.airAttack = airAttackF;
        //Combat Stats
        return newStats;
    }

    void showStats() {
        ImGuiIO& io = ImGui::GetIO();
        ImFont* basicFont = io.Fonts->Fonts[2];
        ImFont* statsFont = io.Fonts->Fonts[4];

        auto off = calculatePos(MIDDLE, 1092);
        ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
        ImGui::SetNextWindowSize(ImVec2(1108, 569));
        ImGui::Begin("Light Tank", &designerWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
        ImGui::PushFont(basicFont);
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 61.0f);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 30.0f);
        ImGui::Text(Tank::tankTypeToString(tankList.find(typeToShow)->second.type).c_str());

        setIcon(ImGui::GetCursorPosY() - 20.0f, ImGui::GetCursorPosX() + 325.0f, Tank::tankTypeToString(tankList.find(typeToShow)->second.type), tankIconNames.find(Tank::tankTypeToString(typeToShow))->second);

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 25.0f);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 30.0f);
        ImGui::Text(Tank::tankVersionToString(tankList.find(typeToShow)->second.version).c_str());

        std::string fileName = std::format("{0}_{1}", Gun::gunNameToString(tankList.find(typeToShow)->second.gun.name), Gun::typeToString(tankList.find(typeToShow)->second.gun.type));
        setImage(TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 22.0f, "modules", fileName);

        fileName = std::format("{0}_turret_{1}", TurretType::turretTypeToString(tankList.find(typeToShow)->second.turret.type), tankList.find(typeToShow)->second.turret.crew);
        setImage(TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 88.0f, "modules", fileName);

        fileName = std::format("{0}", SpecialModule::typeToString(tankList.find(typeToShow)->second.specialModules[0].type));
        setImage(TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 170.0f, "modules", fileName);

        fileName = std::format("{0}", SpecialModule::typeToString(tankList.find(typeToShow)->second.specialModules[1].type));
        setImage(TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 240.0f, "modules", fileName);

        fileName = std::format("{0}", SpecialModule::typeToString(tankList.find(typeToShow)->second.specialModules[2].type));
        setImage(TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 315.0f, "modules", fileName);

        fileName = std::format("{0}", SpecialModule::typeToString(tankList.find(typeToShow)->second.specialModules[3].type));
        setImage(TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 390.0f, "modules", fileName);

        setImage(ImGui::GetCursorPosY() - 4.0f, ImGui::GetCursorPosX() + 16.0f, "blueprint", std::format("ger_{0}_tank_blueprint", Tank::tankTypeToString(typeToShow)));

        fileName = std::format("{0}", Suspension::typeToString(tankList.find(typeToShow)->second.suspension.type));
        setImage(TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 22.5f, "modules", fileName);

        fileName = std::format("{0}", Armor::typeToString(tankList.find(typeToShow)->second.armor.type));
        setImage(TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 100.0f, "modules", fileName);

        fileName = std::format("{0}", Engine::typeToString(tankList.find(typeToShow)->second.engine.type));
        setImage(TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 165.0f, "modules", fileName);

        off = calculatePos(MIDDLE, std::to_string(tankList.find(typeToShow)->second.engineLevel).c_str());
        createLabelWithPosition(std::to_string(tankList.find(typeToShow)->second.engineLevel).c_str(), off - 130.0f, TANK_MODULE_HEIGHT_2 + 20.0f);

        off = calculatePos(MIDDLE, std::to_string(tankList.find(typeToShow)->second.armorLevel).c_str());
        createLabelWithPosition(std::to_string(tankList.find(typeToShow)->second.armorLevel).c_str(), off - 55.0f, TANK_MODULE_HEIGHT_2 + 20.0f);

        ImGui::PushFont(statsFont);
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));

        //Base stats
        std::string speed = std::format("{:.1f} km/h", newTankStats.find(typeToShow)->second.speed);
        createLabelWithPosition(speed.c_str(), BASE_STATS_POS, TITLE_HEIGHT + 60.0f);

        std::string reliability = std::format("{:.1f}", newTankStats.find(typeToShow)->second.reliability);
        createLabelWithPosition(reliability.c_str(), BASE_STATS_POS, TITLE_HEIGHT + 80.0f);

        std::string supplyUse = std::format("{:.2f}", newTankStats.find(typeToShow)->second.supplyUse);
        createLabelWithPosition(supplyUse.c_str(), BASE_STATS_POS, TITLE_HEIGHT + 100.0f);
        //Base stats

        //Combat stats
        std::string softAttack = std::format("{:.2f}", newTankStats.find(typeToShow)->second.softAttack);
        createLabelWithPosition(softAttack.c_str(), COMBAT_STATS_POS, TITLE_HEIGHT + 60.0f);

        std::string hardAttack = std::format("{:.2f}", newTankStats.find(typeToShow)->second.hardAttack);
        createLabelWithPosition(hardAttack.c_str(), COMBAT_STATS_POS, TITLE_HEIGHT + 80.0f);

        std::string piercing = std::format("{:.2f}", newTankStats.find(typeToShow)->second.piercing);
        createLabelWithPosition(piercing.c_str(), COMBAT_STATS_POS, TITLE_HEIGHT + 100.0f);

        std::string hardness = std::format("{:.2f}", newTankStats.find(typeToShow)->second.hardness);
        createLabelWithPosition(hardness.c_str(), COMBAT_STATS_POS, TITLE_HEIGHT + 120.0f);

        std::string armor = std::format("{:.2f}", newTankStats.find(typeToShow)->second.armor);
        createLabelWithPosition(armor.c_str(), COMBAT_STATS_POS, TITLE_HEIGHT + 140.0f);

        std::string breakthrough = std::format("{:.2f}", newTankStats.find(typeToShow)->second.breakthrough);
        createLabelWithPosition(breakthrough.c_str(), COMBAT_STATS_POS, TITLE_HEIGHT + 160.0f);

        std::string defense = std::format("{:.2f}", newTankStats.find(typeToShow)->second.defense);
        createLabelWithPosition(defense.c_str(), COMBAT_STATS_POS, TITLE_HEIGHT + 180.0f);

        std::string airAttack = std::format("{:.2f}", newTankStats.find(typeToShow)->second.airAttack);
        createLabelWithPosition(airAttack.c_str(), COMBAT_STATS_POS, TITLE_HEIGHT + 200.0f);
        //Combat stats

        //Misc Stats
        std::string fuelCapacity = std::format("{:.2f}", newTankStats.find(typeToShow)->second.fuelCapacity);
        createLabelWithPosition(fuelCapacity.c_str(), 1060.0f, TITLE_HEIGHT + 60.0f);

        std::string fuelUsage = std::format("{:.2f}", newTankStats.find(typeToShow)->second.fuelUsage);
        createLabelWithPosition(fuelUsage.c_str(), 1060.0f, TITLE_HEIGHT + 80.0f);

        //TODO research suppression value
        createLabelWithPosition("???", 1060.0f, TITLE_HEIGHT + 100.0f);

        //TODO research reconnaissance value
        createLabelWithPosition("???", 1060.0f, TITLE_HEIGHT + 120.0f);

        std::string entrenchment = std::format("{:.2f}", newTankStats.find(typeToShow)->second.entrenchment);
        createLabelWithPosition(entrenchment.c_str(), 1060.0f, TITLE_HEIGHT + 140.0f);
        //Misc Stats

        ImGui::PopStyleColor();
        ImGui::PopFont();
    }

    void generateCountryFile() {
        std::vector<std::string> fileLines;

        std::ifstream  src("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\history\\countries\\GER - Germany.txt", std::ios::binary);
        std::ofstream  backUp("./Assets/Data/GER - Germany.txt.back", std::ios::binary);
        std::ofstream  newFile("./Assets/Data/GER - Germany.txt", std::ios::binary);
        std::string line;
        while (std::getline(src, line)) {
            fileLines.push_back(line);
        }
        src.close();
        if (std::rename("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\history\\countries\\GER - Germany.txt",
            "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\history\\countries\\GER - Germany.txt.back") != 0)
            perror("Error moving file");
        else
            std::cout << "File moved successfully" << std::endl;

        for (auto& line : fileLines) {
            backUp << line << std::endl;
        }
        backUp.close();
        fileLines.insert(fileLines.begin() + 394, "ultimate_bravery");
        int linesToDeleteStart = 561;
        int linesToDeleteEnd = 638;
        int lineToDeleteCount = linesToDeleteEnd - linesToDeleteStart;

        std::vector<std::string> tempLine = fileLines;

        for (int i = 0; i < fileLines.size(); i++) {
            if (i >= linesToDeleteStart && i <= linesToDeleteEnd && lineToDeleteCount != 0) {
                fileLines.erase(fileLines.begin() + 561);
                lineToDeleteCount--;
            }
        }


        std::vector<std::string> templateLine;
        int counterTemplateLine = 0;

        std::ifstream templateFile("./Assets/Data/equipment_template.txt", std::ios::binary);
        int index;
        std::vector<std::string> replacementList{ "Test",
            std::format("{0}_{1}_chassis_{2}", Tank::tankTypeToString(tankList.find(typeToShow)->second.type), Role::typeToString(tankList.find(typeToShow)->second.role), Tank::tankVersionToInt(tankList.find(typeToShow)->second.version)),
            converterToGameName.find(Utils::hash(std::format("{0}_{1}", Gun::gunNameToString(tankList.find(typeToShow)->second.gun.name), Gun::typeToString(tankList.find(typeToShow)->second.gun.type)).c_str()))->second,
            converterToGameName.find(Utils::hash(std::format("{0}_{1}", TurretType::turretTypeToString(tankList.find(typeToShow)->second.turret.type), tankList.find(typeToShow)->second.turret.crew).c_str()))->second,
            converterToGameName.find(Utils::hash(Suspension::typeToString(tankList.find(typeToShow)->second.suspension.type).c_str()))->second,
            converterToGameName.find(Utils::hash(Armor::typeToString(tankList.find(typeToShow)->second.armor.type).c_str()))->second,
            converterToGameName.find(Utils::hash(Engine::typeToString(tankList.find(typeToShow)->second.engine.type).c_str()))->second,
            converterToGameName.find(Utils::hash(SpecialModule::typeToString(tankList.find(typeToShow)->second.specialModules[0].type).c_str()))->second,
            converterToGameName.find(Utils::hash(SpecialModule::typeToString(tankList.find(typeToShow)->second.specialModules[1].type).c_str()))->second,
            converterToGameName.find(Utils::hash(SpecialModule::typeToString(tankList.find(typeToShow)->second.specialModules[2].type).c_str()))->second,
            converterToGameName.find(Utils::hash(SpecialModule::typeToString(tankList.find(typeToShow)->second.specialModules[3].type).c_str()))->second,
            std::to_string(tankList.find(typeToShow)->second.engineLevel),
            std::to_string(tankList.find(typeToShow)->second.armorLevel),
        };
        std::vector<std::string> tokenList{ "%tankName%",
            "%tankTypeVersion%",
            "%gunName%",
            "%turretName%",
            "%suspensionName%",
            "%armorName%",
            "%engineName%",
            "%specialName_1%",
            "%specialName_2%",
            "%specialName_3%",
            "%specialName_4%",
            "%engineUpgrade%",
            "%armorUpgrade%" };
        while (std::getline(templateFile, line)) {
            for (int i = 0; i < tokenList.size(); i++) {
                while ((index = line.find(tokenList[i])) != std::string::npos) {
                    //std::cout << index->c_str() << std::endl;
                    line.replace(line.find(tokenList[i]), tokenList[i].length(), replacementList[i]);
                }
            }
            templateLine.push_back(line);
        }

        for (int i = 0; i < fileLines.size(); i++) {
            if (i >= linesToDeleteStart && counterTemplateLine < templateLine.size()) {
                fileLines.insert(fileLines.begin() + i, templateLine[counterTemplateLine]);
                counterTemplateLine++;
            }
        }


        for (int i = 0; i < fileLines.size(); i++) {
            newFile << fileLines[i] << std::endl;
        }
        newFile.close();
        if (std::rename("./Assets/Data/GER - Germany.txt",
            "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\history\\countries\\GER - Germany.txt") != 0) {
            perror("Error moving file");
        }
        else {
            std::cout << "File moved successfully" << std::endl;
        };
    }

    void generateIdeaFile() {
        std::vector<std::string> fileLines;

        std::ifstream  src("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\common\\ideas\\GER.txt", std::ios::binary);
        std::ofstream  backUp("./Assets/Data/GER.txt.back", std::ios::binary);
        std::ofstream  newFile("./Assets/Data/GER.txt", std::ios::binary);
        std::string line;
        while (std::getline(src, line)) {
            fileLines.push_back(line);
        }
        src.close();
        if (std::rename("C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\common\\ideas\\GER.txt",
            "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\common\\ideas\\GER.txt.back") != 0)
            perror("Error moving file");
        else
            std::cout << "File moved successfully" << std::endl;

        for (auto& line : fileLines) {
            backUp << line << std::endl;
        }
        backUp.close();
        int linesToAddStart = 3;
        int counterTemplateLine = 0;
        std::vector<std::string> newLines;
        std::ifstream ideaFile("./Assets/Data/idea.txt", std::ios::binary);
        while (std::getline(ideaFile, line)) {
            newLines.push_back(line);
        }
        for (int i = 0; i < fileLines.size(); i++) {
            if (i >= linesToAddStart && counterTemplateLine < newLines.size()) {
                fileLines.insert(fileLines.begin() + i, newLines[counterTemplateLine]);
                counterTemplateLine++;
            }
        }

        for (int i = 0; i < fileLines.size(); i++) {
            newFile << fileLines[i] << std::endl;
        }
        newFile.close();
        if (std::rename("./Assets/Data/GER.txt",
            "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Hearts of Iron IV\\common\\ideas\\GER.txt") != 0) {
            perror("Error moving file");
        }
        else {
            std::cout << "File moved successfully" << std::endl;
        };

    }
};