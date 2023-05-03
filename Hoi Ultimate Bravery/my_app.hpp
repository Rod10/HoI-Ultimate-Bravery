#include "app_base.hpp"

#include "armor.hpp"
#include "engine.hpp"
#include "gun.hpp"
#include "special.hpp"
#include "suspension.hpp"
#include "tank.hpp"
#include "tanktype.hpp"
#include "texture.hpp"
#include "turret.hpp"
#include "turrettype.hpp"
#include "utils.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <filesystem>
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
        auto statsKey = Stats::getStatsKeyArray();

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

        fileName = std::format("./Assets/Images/tank_designer_bg.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        Texture texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureMap.insert(std::pair<std::string, Texture>("tank_designer_bg", texture));

        fileName = std::format("./Assets/Images/tank_name_bg.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureMap.insert(std::pair<std::string, Texture>("tank_name_bg", texture));

        fileName = std::format("./Assets/Images/tank_role_bg.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureMap.insert(std::pair<std::string, Texture>("tank_role_bg", texture));

        fileName = std::format("./Assets/Images/equipment_icon_bg.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        texture.my_image_width = 154;
        texture.my_image_height = 56;
        textureMap.insert(std::pair<std::string, Texture>("tank_icon_bg", texture));

        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureMap.insert(std::pair<std::string, Texture>("equipment_icon_bg", texture));

        fileName = std::format("./Assets/Images/tank_blueprint_background.png");
        ret = Utils::LoadTextureFromFile(fileName.c_str(), &my_image_texture, &my_image_width, &my_image_height);
        IM_ASSERT(ret);
        texture = Texture(my_image_width, my_image_height, my_image_texture);
        textureMap.insert(std::pair<std::string, Texture>("tank_blueprint_background", texture));

        std::string path = "./Assets/Images/Cannon";
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            const std::string imagePath = entry.path().string();
            ret = Utils::LoadTextureFromFile(imagePath.c_str(), &my_image_texture, &my_image_width, &my_image_height);
            IM_ASSERT(ret);
            texture = Texture(my_image_width, my_image_height, my_image_texture);

            std::string base_filename = imagePath.substr(imagePath.find_last_of("/\\") + 1);
            std::string::size_type const p(base_filename.find_last_of('.'));
            std::string file_without_extension = base_filename.substr(0, p);

            textureMap.insert(std::pair<std::string, Texture>(file_without_extension, texture));
        }

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
                lightWindowOpen = true;
                generateWindowOpen = false;
            }
            ImGui::SameLine();
            ImGui::Button("Medium");
            ImGui::SameLine();
            ImGui::Button("Heavy");
            ImGui::SameLine();
            ImGui::Button("Super Heavy");
            ImGui::SameLine();
            ImGui::Button("Modern");
            createButtonlWithPosition("Full Random", MIDDLE);

            if (createButtonlWithPosition("Back", MIDDLE)) {
                mainMenuOpen = true;
                generateWindowOpen = false;
            }
            ImGui::PopStyleColor();
            ImGui::End();
        }
        // Generate Menu

        //light Tank
        if (lightWindowOpen) {
            generateTankDesignerWindow(lightTank);

            ImGuiIO& io = ImGui::GetIO();
            ImFont* basicFont = io.Fonts->Fonts[2];

            auto off = calculatePos(MIDDLE, 1092);
            ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
            ImGui::SetNextWindowSize(ImVec2(1108, 569));
            ImGui::Begin("Light Tank", &lightWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
            ImGui::PushFont(basicFont);
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 61.0f);
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 30.0f);
            ImGui::Text("Light Tank");
            ImGui::PopStyleColor();
            ImGui::PopFont();

            std::string fileName = std::format("{0}_{1}", Gun::gunNameToString(lightTank.gun.name), Gun::typeToString(lightTank.gun.type));
            Texture texture = textureMap.find(fileName)->second;
            ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));

            ImGui::End();
        }
        //light Tank

        ImGui::End();
    }

private:
    Tank lightTank = Tank::generateRandomTank(TankType::Type::Light);

    const float TITLE_HEIGHT = 24.0f;
    const float TANK_NAME_HEIGHT = 63.0f;
    const float TANK_ROLE_HEIGHT = 106.0f;
    const float TANK_MODULE_HEIGHT = 155.0f;
    const float TANK_MODULE_HEIGHT_2 = 455.0f;

    bool mainWindowOpen = true;
    bool mainMenuOpen = true;
    bool generateWindowOpen = false;
    bool optionWindowOpen = false;
    bool lightWindowOpen = false;

    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;
    std::string fileName;
    bool ret;
    std::map<std::string, Texture> textureMap;

    std::map<Gun::Category, std::vector<Gun>> gunList = Gun::generateGunList();
    std::map<Gun::Category, bool> gunCateogryWindowOpen;
    std::map<Gun::Name, bool> gunNameWindowOpen;

    std::unordered_map<int, std::string> localizedStrings;
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

    void generateTankDesignerWindow(Tank tank) {
        ImGuiIO& io = ImGui::GetIO();
        ImFont* basicFont = io.Fonts->Fonts[0];
        ImFont* titleFont = io.Fonts->Fonts[1];
        Texture texture = textureMap.find("tank_designer_bg")->second;
        auto off = calculatePos(MIDDLE, texture.my_image_width);
        ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
        ImGui::Begin(Tank::tankTypeToString(tank.type).c_str(), &lightWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PushFont(titleFont);
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
        ImGui::SetCursorPosY(TITLE_HEIGHT);
        createLabelWithPosition("Equipment Designer", MIDDLE);
        ImGui::PopFont();
        ImGui::PopStyleColor();

        ImGui::SetCursorPosY(TANK_NAME_HEIGHT);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 20.0f);
        texture = textureMap.find("tank_name_bg")->second;
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));

        ImGui::SetCursorPosY(TANK_NAME_HEIGHT + (texture.my_image_height / 2.5));
        ImGui::SetCursorPosX(texture.my_image_width + 50.0f);
        texture = textureMap.find("tank_icon_bg")->second;
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));

        ImGui::SetCursorPosY(TANK_ROLE_HEIGHT);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 20.0f);
        texture = textureMap.find("tank_role_bg")->second;
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));

        texture = textureMap.find("equipment_icon_bg")->second;
        for (int i = 0; i <= 5; i++) {
            ImGui::SetCursorPosY(TANK_MODULE_HEIGHT);
            if (i == 0) {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15.0f);
            }
            else {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (texture.my_image_width * i) + (13.0f - (i * 3)));
            }
            ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
        }

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 4.0f);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 16.0f);
        texture = textureMap.find("tank_blueprint_background")->second;
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));

        texture = textureMap.find("equipment_icon_bg")->second;
        for (int i = 0; i <= 2; i++) {
            if (i == 0) {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 15.0f);
            }
            else {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (texture.my_image_width * i) + (12.0f - (i * 3)));
            }
            ImGui::SetCursorPosY(TANK_MODULE_HEIGHT_2);
            ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
        }

        ImGui::SetCursorPosX(MIDDLE - 100.0f);
        ImGui::SetCursorPosY(TANK_MODULE_HEIGHT_2);
        ImGui::Text("Engine");
        ImGui::SetCursorPosX(MIDDLE - 20.0f);
        ImGui::SetCursorPosY(TANK_MODULE_HEIGHT_2);
        ImGui::Text("Armor");

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 45.0f);
        if (createButtonlWithPosition("Back", MIDDLE)) {
            generateWindowOpen = true;
            lightWindowOpen = false;
        }
        ImGui::End();
    }
};