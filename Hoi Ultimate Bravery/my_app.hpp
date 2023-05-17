#include "app_base.hpp"

#include "armor.hpp"
#include "country.hpp"
#include "engine.hpp"
#include "gun.hpp"
#include "renderer.hpp"
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
        Renderer::createLabelWithPosition("HoI Ultimate Bravery", Constant::Position::MIDDLE);
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopFont();

        auto off = Renderer::calculatePos(Constant::Position::MIDDLE, "generate");

        // Main Menu Block
        if (mainMenuOpen) {
            ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, windowColor);
            ImGui::Begin("generate", &mainMenuOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::PopStyleColor();
            ImGui::PushFont(basicFont);
            ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
            if (Renderer::createButtonWithPosition("Generate", Constant::Position::MIDDLE)) {
                mainMenuOpen = false;
                generateWindowOpen = true;
            }
            if (Renderer::createButtonWithPosition("Option", Constant::Position::MIDDLE)) {
                mainMenuOpen = false;
                optionWindowOpen = true;
            }
            if (Renderer::createButtonWithPosition("Quit", Constant::Position::MIDDLE)) {
                exit(1);
            }
            ImGui::PopStyleColor();
            ImGui::PopFont();
            ImGui::End();
        }
        // Main Menu Block

        // Generate Menu
        if (generateWindowOpen) {
            auto off = Renderer::calculatePos(Constant::Position::MIDDLE, "Tank: Light Medium Heavy Super Heavy Modern");
            ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, windowColor);
            ImGui::Begin("generate", &generateWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
            ImGui::PopStyleColor();
            Renderer::createLabelWithPosition("Generate", Constant::Position::MIDDLE);

            off = Renderer::calculatePos(Constant::Position::MIDDLE, "Country: ");
            Renderer::createLabelWithPosition("Country: ", off, ImGui::GetCursorPosY() + 10.0f);
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

            Renderer::createLabelWithPosition("Tank: ", Constant::Position::LEFT);
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

                std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(tank.type));
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

                std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(tank.type));
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

                std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(tank.type));
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

                std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(tank.type));
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

                std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(tank.type));
                auto it = icon.cbegin();
                int random = rand() % icon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("modern", it->first));

                designerWindowOpen = true;
                generateWindowOpen = false;
            }
            if (Renderer::createButtonWithPosition("Full Random", Constant::Position::MIDDLE)) {
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

                std::map<std::string, Texture> lightIcon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(lightTank.type));
                auto it = lightIcon.cbegin();
                int random = rand() % lightIcon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("light", it->first));

                std::map<std::string, Texture> mediumIcon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(mediumTank.type));
                it = mediumIcon.cbegin();
                random = rand() % mediumIcon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("medium", it->first));

                std::map<std::string, Texture> heavyIcon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(heavyTank.type));
                it = heavyIcon.cbegin();
                random = rand() % heavyIcon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("heavy", it->first));

                std::map<std::string, Texture> superHeavyIcon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(superHeavyTank.type));
                it = superHeavyIcon.cbegin();
                random = rand() % superHeavyIcon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("superHeavy", it->first));

                std::map<std::string, Texture> modernIcon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(modernTank.type));
                it = modernIcon.cbegin();
                random = rand() % modernIcon.size();
                std::advance(it, random);

                tankIconNames.insert(std::pair<std::string, std::string>("modern", it->first));

                allGenerationWindowOpen = true;
                generateWindowOpen = false;

            }

            if (Renderer::createButtonWithPosition("Back", Constant::Position::MIDDLE)) {
                mainMenuOpen = true;
                generateWindowOpen = false;
            }
            ImGui::PopStyleColor();
            ImGui::End();
        }
        // Generate Menu

        //By Type
        if (designerWindowOpen) {
            Renderer::renderTankDesignerWindow(designerWindowOpen, tankList.find(typeToShow)->second);
            Renderer::renderStats(designerWindowOpen, tankList.find(typeToShow)->second, tankIconNames, newTankStats);
            
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
                generateCountryFile(tankList.find(typeToShow)->second);
                //generateIdeaFile();
            }
            ImGui::SameLine();
            if (ImGui::Button("Regenerate")) {
                tankList.find(typeToShow)->second = Tank::generateRandomTank(typeToShow);
                newTankStats.find(typeToShow)->second = generateNewStats(tankList.find(typeToShow)->second);

                std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(typeToShow));
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
                Renderer::createLabelWithPosition(Tank::tankTypeToString(tank.type).c_str(), Constant::Position::MIDDLE);
                ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
                ImGuiIO& io = ImGui::GetIO();
                Renderer::createLabelWithPosition(std::format("{0} {1}", Gun::gunNameToString(tank.gun.name), Gun::typeToString(tank.gun.type)).c_str(), Constant::Position::LEFT);
                Renderer::createLabelWithPosition(std::format("{0} {1}", TurretType::turretTypeToString(tank.turret.type), tank.turret.crew).c_str(), Constant::Position::LEFT);
                Renderer::createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[0].type).c_str(), Constant::Position::LEFT);
                Renderer::createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[1].type).c_str(), Constant::Position::LEFT);
                Renderer::createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[2].type).c_str(), Constant::Position::LEFT);
                Renderer::createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[3].type).c_str(), Constant::Position::LEFT);
                Renderer::createLabelWithPosition(Suspension::typeToString(tank.suspension.type).c_str(), Constant::Position::LEFT);
                Renderer::createLabelWithPosition(Armor::typeToString(tank.armor.type).c_str(), Constant::Position::LEFT);
                Renderer::createLabelWithPosition(Engine::typeToString(tank.engine.type).c_str(), Constant::Position::LEFT);
                Renderer::createLabelWithPosition(std::format("Armor: {0}", tank.armorLevel).c_str(), Constant::Position::LEFT);
                Renderer::createLabelWithPosition(std::format("Engine: {0}", tank.engineLevel).c_str(), Constant::Position::LEFT);
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
            
                std::vector<std::string> templateLine;

                int index;
                for (auto& [type, tank] : tankList) {
                    std::string line;
                    std::ifstream templateFile("./Assets/Data/equipment_template.txt", std::ios::binary);
                    int counterTemplateLine = 0;
                    std::cout << Tank::tankTypeToString(tank.type) << std::endl;
                    std::vector<std::string> replacementList{ "Test",
                        std::format("{0}_{1}_chassis_{2}", Tank::tankTypeToString(tank.type), Role::typeToString(tank.role), Tank::tankVersionToInt(tank.version)),
                        converterToGameName.find(Utils::hash(std::format("{0}_{1}", Gun::gunNameToString(tank.gun.name), Gun::typeToString(tank.gun.type)).c_str()))->second,
                        converterToGameName.find(Utils::hash(std::format("{0}_{1}", TurretType::turretTypeToString(tank.turret.type), tank.turret.crew).c_str()))->second,
                        converterToGameName.find(Utils::hash(Suspension::typeToString(tank.suspension.type).c_str()))->second,
                        converterToGameName.find(Utils::hash(Armor::typeToString(tank.armor.type).c_str()))->second,
                        converterToGameName.find(Utils::hash(Engine::typeToString(tank.engine.type).c_str()))->second,
                        converterToGameName.find(Utils::hash(SpecialModule::typeToString(tank.specialModules[0].type).c_str()))->second,
                        converterToGameName.find(Utils::hash(SpecialModule::typeToString(tank.specialModules[1].type).c_str()))->second,
                        converterToGameName.find(Utils::hash(SpecialModule::typeToString(tank.specialModules[2].type).c_str()))->second,
                        converterToGameName.find(Utils::hash(SpecialModule::typeToString(tank.specialModules[3].type).c_str()))->second,
                        std::to_string(tank.engineLevel),
                        std::to_string(tank.armorLevel),
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
                    templateFile.close();
                }
            
            }
            ImGui::SameLine();
            if (ImGui::Button("Regenerate")) {}
            ImGui::SameLine();
            if (ImGui::Button("Back")) {
                generateWindowOpen = true;
                allGenerationWindowOpen = false;
            }
            ImGui::PopFont();   
            ImGui::End();
        }
        //All Type

        // Options
        if (optionWindowOpen) {
            off = Renderer::calculatePos(Constant::Position::MIDDLE, 250);
            ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
            ImGui::Begin("options", &optionWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
            Renderer::createLabelWithPosition("Options", Constant::Position::MIDDLE);

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
    Country* country = &countryList[0];
    Settings settings;

    bool mainWindowOpen = true;
    bool mainMenuOpen = true;
    bool generateWindowOpen = false;
    bool optionWindowOpen = false;
    bool designerWindowOpen = false;
    bool allGenerationWindowOpen = false;

    std::map<std::string, std::string> tankIconNames;

    std::map<Gun::Category, std::vector<Gun>> gunList = Gun::generateGunList();
    std::map<Gun::Category, bool> gunCateogryWindowOpen;
    std::map<Gun::Name, bool> gunNameWindowOpen;

    std::unordered_map<int, std::string> localizedStrings = Utils::loadTranslation("Assets/Data/Langages/en-en.csv");
    std::unordered_map<int, std::string> converterToGameName = Utils::loadTranslation("Assets/Data/converter.csv");

    ImVec4 backgroundColor = ImVec4(0.831f, 0.902f, 0.945f, 1.00f);
    ImVec4 windowColor = ImVec4(0.149f, 0.137f, 0.125f, 1.00f);
    ImVec4 buttonColor = ImVec4(0.231f, 0.255f, 0.224f, 1.00f);

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

    void generateCountryFile(Tank tank) {
        std::vector<std::string> fileLines;

        std::string gamePath = settings.getGamepath();
        std::string fileName = std::format("{0} - {1}.txt", country->tag, country->name);
        std::string filePath = std::format("{0}\\history\\countries\\{1}", gamePath, fileName);
        std::string backupFilePath = std::format("{0}\\history\\countries\\{1}", gamePath, fileName);
        
        std::ifstream  src(std::format("{0}\\history\\countries\\{1}", gamePath, fileName), std::ios::binary);
        std::ofstream  backUp(std::format("/Assets/Data/{0}.back", fileName), std::ios::binary);
        std::ofstream  newFile(std::format("/Assets/Data/{0}", fileName), std::ios::binary);
        std::string line;
        while (std::getline(src, line)) {
            fileLines.push_back(line);
        }
        src.close();
        if (std::rename(filePath.c_str(),
            backupFilePath.c_str()) != 0)
            perror("Error moving file");
        else
            std::cout << "File moved successfully" << std::endl;

        for (auto& line : fileLines) {
            backUp << line << std::endl;
        }
        backUp.close();
        fileLines.insert(fileLines.begin() + country->countryPosIdea, "ultimate_bravery");
        int linesToDeleteStart = country->linesToDeleteStart;
        int linesToDeleteEnd = country->linesToDeleteEnd;
        int lineToDeleteCount = linesToDeleteEnd - linesToDeleteStart;

        std::vector<std::string> tempLine = fileLines;

        for (int i = 0; i < fileLines.size(); i++) {
            if (i >= linesToDeleteStart && i <= linesToDeleteEnd && lineToDeleteCount != 0) {
                fileLines.erase(fileLines.begin() + country->linesToDeleteStart);
                lineToDeleteCount--;
            }
        }

        std::vector<std::string> templateLine;
        int counterTemplateLine = 0;

        std::ifstream templateFile("./Assets/Data/equipment_template.txt", std::ios::binary);
        int index;
        std::vector<std::string> replacementList{ "Test",
            std::format("{0}_{1}_chassis_{2}", Tank::tankTypeToString(tank.type), Role::typeToString(tank.role), Tank::tankVersionToInt(tank.version)),
            converterToGameName.find(Utils::hash(std::format("{0}_{1}", Gun::gunNameToString(tank.gun.name), Gun::typeToString(tank.gun.type)).c_str()))->second,
            converterToGameName.find(Utils::hash(std::format("{0}_{1}", TurretType::turretTypeToString(tank.turret.type), tank.turret.crew).c_str()))->second,
            converterToGameName.find(Utils::hash(Suspension::typeToString(tank.suspension.type).c_str()))->second,
            converterToGameName.find(Utils::hash(Armor::typeToString(tank.armor.type).c_str()))->second,
            converterToGameName.find(Utils::hash(Engine::typeToString(tank.engine.type).c_str()))->second,
            converterToGameName.find(Utils::hash(SpecialModule::typeToString(tank.specialModules[0].type).c_str()))->second,
            converterToGameName.find(Utils::hash(SpecialModule::typeToString(tank.specialModules[1].type).c_str()))->second,
            converterToGameName.find(Utils::hash(SpecialModule::typeToString(tank.specialModules[2].type).c_str()))->second,
            converterToGameName.find(Utils::hash(SpecialModule::typeToString(tank.specialModules[3].type).c_str()))->second,
            std::to_string(tank.engineLevel),
            std::to_string(tank.armorLevel),
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
        if (std::rename(std::format("/Assets/Data/{0}", fileName).c_str(),
            filePath.c_str()) != 0) {
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