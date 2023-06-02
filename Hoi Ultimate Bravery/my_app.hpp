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
#include "language.hpp"
#include "files.hpp"

using json = nlohmann::json;

class MyApp : public AppBase
{
public:
    MyApp()
    {}
    ~MyApp() {
        if (fileModified) {
            std::string gamePath = settings.getGamepath();
            std::string fileName = std::format("{0} - {1}.txt", country->tag, country->name);
            std::string filePath = std::format("{0}\\history\\countries\\{1}", gamePath, fileName);
            std::string backupFilePath = std::format("{0}\\history\\countries\\{1}.back", gamePath, fileName);

            std::string src(fileName);
            std::remove(src.c_str());
            std::string backUp(backupFilePath);
            if(std::rename(backUp.c_str(), src.c_str()) != 0) {
                perror("Error moving file");
            }
            else {
                std::cout << "File moved successfully" << std::endl;
            };


            fileName = std::format("{0}.txt", country->tag, country->name);
            filePath = std::format("{0}\\common\\ideas\\{1}", gamePath, fileName);
            backupFilePath = std::format("{0}\\history\\countries\\{1}.back", gamePath, fileName);
            src = filePath;
            std::remove(src.c_str());
            backUp = backupFilePath;
            if(std::rename(backUp.c_str(), src.c_str()) != 0) {
                perror("Error moving file");
            }
            else {
                std::cout << "File moved successfully" << std::endl;
            };
        }
    };

    virtual void StartUp() final
    {
        auto statsKey = Stats::getStatsKeyArray();
        languageFile = std::format("{0}.csv", settings.language.value);
        languageFilePath = std::format("Assets/Data/languages/{0}", languageFile);
        localizedStrings = Utils::loadTranslation(languageFilePath);
        
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
            if (Renderer::createButtonWithPosition(getLocalizedString("generate"), Constant::Position::MIDDLE)) {
                mainMenuOpen = false;
                generateWindowOpen = true;
            }
            if (Renderer::createButtonWithPosition(getLocalizedString("options"), Constant::Position::MIDDLE)) {
                mainMenuOpen = false;
                optionWindowOpen = true;
            }
            if (Renderer::createButtonWithPosition(getLocalizedString("quit"), Constant::Position::MIDDLE)) {
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
            Renderer::createLabelWithPosition(getLocalizedString("generate"), Constant::Position::MIDDLE);

            off = Renderer::calculatePos(Constant::Position::MIDDLE, std::format("{0} :", getLocalizedString("country")));
            Renderer::createLabelWithPosition(std::format("{0} :", getLocalizedString("country")).c_str(), off, ImGui::GetCursorPosY() + 10.0f);
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
            off = Renderer::calculatePos(Constant::Position::MIDDLE, getLocalizedString("allCountries"));
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
            ImGui::Checkbox(getLocalizedString("allCountries"), &allCountries);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);
            Renderer::createLabelWithPosition(std::format("{0} :", getLocalizedString("tank")).c_str(), Constant::Position::LEFT);
            ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
            ImGuiStyle& style = ImGui::GetStyle();
            float width = 0.0f;
            width += ImGui::CalcTextSize(std::format("{0}: ", getLocalizedString("tank")).c_str()).x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize(getLocalizedString("light")).x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize(getLocalizedString("medium")).x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize(getLocalizedString("heavy")).x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize(getLocalizedString("superHeavy")).x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize(getLocalizedString("modern")).x;
            AlignForWidth(width);
            ImGui::SameLine();
            if (ImGui::Button(getLocalizedString("light"))) {
                typeToShow = TankType::Type::Light;
                if (allCountries) {
                    for (Country &country : countryList) {
                        Tank tank = Tank::generateRandomTank(typeToShow);

                        country.tankList.insert(std::pair<TankType::Type, Tank>(typeToShow, tank));
                        country.newTankStats.insert(std::pair<TankType::Type, Stats>(typeToShow, generateNewStats(tank)));
                    }
                } else {
                    Tank tank = Tank::generateRandomTank(typeToShow);

                    country->tankList.insert(std::pair<TankType::Type, Tank>(typeToShow, tank));
                    country->newTankStats.insert(std::pair<TankType::Type, Stats>(typeToShow, generateNewStats(tank)));
                }

                std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(typeToShow));
                tankIconNames.insert(std::pair<std::string, std::string>("light", getRandomIcon(typeToShow)));

                designerWindowOpen = true;
                generateWindowOpen = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(getLocalizedString("medium"))) {
                typeToShow = TankType::Type::Medium;
                if (allCountries) {
                    for (Country &country : countryList) {
                        Tank tank = Tank::generateRandomTank(typeToShow);

                        country.tankList.insert(std::pair<TankType::Type, Tank>(typeToShow, tank));
                        country.newTankStats.insert(std::pair<TankType::Type, Stats>(typeToShow, generateNewStats(tank)));
                    }
                }
                else {
                    Tank tank = Tank::generateRandomTank(typeToShow);

                    country->tankList.insert(std::pair<TankType::Type, Tank>(typeToShow, tank));
                    country->newTankStats.insert(std::pair<TankType::Type, Stats>(typeToShow, generateNewStats(tank)));
                }

                std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(typeToShow));
                tankIconNames.insert(std::pair<std::string, std::string>("light", getRandomIcon(typeToShow)));

                designerWindowOpen = true;
                generateWindowOpen = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(getLocalizedString("heavy"))) {
                typeToShow = TankType::Type::Heavy;
                if (allCountries) {
                    for (Country &country : countryList) {
                        Tank tank = Tank::generateRandomTank(typeToShow);

                        country.tankList.insert(std::pair<TankType::Type, Tank>(typeToShow, tank));
                        country.newTankStats.insert(std::pair<TankType::Type, Stats>(typeToShow, generateNewStats(tank)));
                    }
                }
                else {
                    Tank tank = Tank::generateRandomTank(typeToShow);

                    country->tankList.insert(std::pair<TankType::Type, Tank>(typeToShow, tank));
                    country->newTankStats.insert(std::pair<TankType::Type, Stats>(typeToShow, generateNewStats(tank)));
                }

                std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(typeToShow));
                tankIconNames.insert(std::pair<std::string, std::string>("light", getRandomIcon(typeToShow)));

                designerWindowOpen = true;
                generateWindowOpen = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(getLocalizedString("superHeavy"))) {
                typeToShow = TankType::Type::SuperHeavy;
                if (allCountries) {
                    for (Country &country : countryList) {
                        Tank tank = Tank::generateRandomTank(typeToShow);

                        country.tankList.insert(std::pair<TankType::Type, Tank>(typeToShow, tank));
                        country.newTankStats.insert(std::pair<TankType::Type, Stats>(typeToShow, generateNewStats(tank)));
                    }
                }
                else {
                    Tank tank = Tank::generateRandomTank(typeToShow);

                    country->tankList.insert(std::pair<TankType::Type, Tank>(typeToShow, tank));
                    country->newTankStats.insert(std::pair<TankType::Type, Stats>(typeToShow, generateNewStats(tank)));
                }

                std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(typeToShow));
                tankIconNames.insert(std::pair<std::string, std::string>("light", getRandomIcon(typeToShow)));

                designerWindowOpen = true;
                generateWindowOpen = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(getLocalizedString("modern"))) {
                typeToShow = TankType::Type::Modern;
                if (allCountries) {
                    for (Country &country : countryList) {
                        Tank tank = Tank::generateRandomTank(typeToShow);

                        country.tankList.insert(std::pair<TankType::Type, Tank>(typeToShow, tank));
                        country.newTankStats.insert(std::pair<TankType::Type, Stats>(typeToShow, generateNewStats(tank)));
                    }
                }
                else {
                    Tank tank = Tank::generateRandomTank(typeToShow);

                    country->tankList.insert(std::pair<TankType::Type, Tank>(typeToShow, tank));
                    country->newTankStats.insert(std::pair<TankType::Type, Stats>(typeToShow, generateNewStats(tank)));
                }

                std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(typeToShow));
                tankIconNames.insert(std::pair<std::string, std::string>("light", getRandomIcon(typeToShow)));

                designerWindowOpen = true;
                generateWindowOpen = false;
            }
            if (Renderer::createButtonWithPosition(getLocalizedString("all"), Constant::Position::MIDDLE)) {
                if (allCountries) {
                    for (Country &country : countryList) {
                        Tank lightTank = Tank::generateRandomTank(TankType::Type::Light);
                        country.tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Light, lightTank));

                        Tank mediumTank = Tank::generateRandomTank(TankType::Type::Medium);
                        country.tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Medium, mediumTank));

                        Tank heavyTank = Tank::generateRandomTank(TankType::Type::Heavy);
                        country.tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Heavy, heavyTank));

                        Tank superHeavyTank = Tank::generateRandomTank(TankType::Type::SuperHeavy);
                        country.tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::SuperHeavy, superHeavyTank));

                        Tank modernTank = Tank::generateRandomTank(TankType::Type::Modern);
                        country.tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Modern, modernTank));

                        country.newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Light, generateNewStats(lightTank)));
                        country.newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Medium, generateNewStats(mediumTank)));
                        country.newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Heavy, generateNewStats(heavyTank)));
                        country.newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::SuperHeavy, generateNewStats(superHeavyTank)));
                        country.newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Modern, generateNewStats(modernTank)));

                        tankIconNames.insert(std::pair<std::string, std::string>("light", getRandomIcon(TankType::Type::Light)));
                        tankIconNames.insert(std::pair<std::string, std::string>("medium", getRandomIcon(TankType::Type::Medium)));
                        tankIconNames.insert(std::pair<std::string, std::string>("heavy", getRandomIcon(TankType::Type::Heavy)));
                        tankIconNames.insert(std::pair<std::string, std::string>("superHeavy", getRandomIcon(TankType::Type::SuperHeavy)));
                        tankIconNames.insert(std::pair<std::string, std::string>("modern", getRandomIcon(TankType::Type::Modern)));
                    }
                }
                else {
                    Tank lightTank = Tank::generateRandomTank(TankType::Type::Light);
                    country->tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Light, lightTank));

                    Tank mediumTank = Tank::generateRandomTank(TankType::Type::Medium);
                    country->tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Medium, mediumTank));

                    Tank heavyTank = Tank::generateRandomTank(TankType::Type::Heavy);
                    country->tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Heavy, heavyTank));

                    Tank superHeavyTank = Tank::generateRandomTank(TankType::Type::SuperHeavy);
                    country->tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::SuperHeavy, superHeavyTank));

                    Tank modernTank = Tank::generateRandomTank(TankType::Type::Modern);
                    country->tankList.insert(std::pair<TankType::Type, Tank>(TankType::Type::Modern, modernTank));

                    country->newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Light, generateNewStats(lightTank)));
                    country->newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Medium, generateNewStats(mediumTank)));
                    country->newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Heavy, generateNewStats(heavyTank)));
                    country->newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::SuperHeavy, generateNewStats(superHeavyTank)));
                    country->newTankStats.insert(std::pair<TankType::Type, Stats>(TankType::Type::Modern, generateNewStats(modernTank)));

                    tankIconNames.insert(std::pair<std::string, std::string>("light", getRandomIcon(TankType::Type::Light)));
                    tankIconNames.insert(std::pair<std::string, std::string>("medium", getRandomIcon(TankType::Type::Medium)));
                    tankIconNames.insert(std::pair<std::string, std::string>("heavy", getRandomIcon(TankType::Type::Heavy)));
                    tankIconNames.insert(std::pair<std::string, std::string>("superHeavy", getRandomIcon(TankType::Type::SuperHeavy)));
                    tankIconNames.insert(std::pair<std::string, std::string>("modern", getRandomIcon(TankType::Type::Modern)));
                }

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
            Renderer::renderTankDesignerWindow(designerWindowOpen, country->tankList.find(typeToShow)->second);
            Renderer::renderStats(designerWindowOpen, country->tankList.find(typeToShow)->second, tankIconNames, country->newTankStats);
            
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
                fileModified = true;
                if (allCountries) {
                    for (Country &country : countryList) {
                        Files::generateCountryFile(country.tankList.find(typeToShow)->second, &country, settings, converterToGameName, debugMode);
                        generateIdeaFile(&country);
                    }
                }
                else {
                    Files::generateCountryFile(country->tankList.find(typeToShow)->second, country, settings, converterToGameName, debugMode);
                    generateIdeaFile(country);
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Regenerate")) {
                country->tankList.find(typeToShow)->second = Tank::generateRandomTank(typeToShow);
                country->newTankStats.find(typeToShow)->second = generateNewStats(country->tankList.find(typeToShow)->second);

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
            for (auto& [type, tank] : country->tankList) {
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
                fileModified = true;
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

            ImGui::Text("Language: ");
            ImGui::SameLine();
            static ImGuiComboFlags flags = 0;
            static int languageIndex = settings.language.index; 
            static int nameIndex = 0;// Here we store our selection data as an index.
            const char* combo_preview_value = languageList[languageIndex].name[nameIndex].c_str();  // Pass in the preview value visible before opening the combo (it could be anything)
            std::cout << languageList[languageIndex].name[0].size() << std::endl;
            if (ImGui::BeginCombo("###", combo_preview_value, flags))
            {
                for (int n = 0; n < languageList[languageIndex].name.size(); n++)
                {
                    const bool is_selected = (nameIndex == n);
                    if (ImGui::Selectable(languageList[languageIndex].name[n].c_str(), is_selected)) {
                        nameIndex = n;
                        language = &languageList[n];
                    }

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            width = 0.0f;
            width += ImGui::CalcTextSize("Save").x;
            width += style.ItemSpacing.x;
            width += ImGui::CalcTextSize("Back").x;
            width += style.ItemSpacing.x;
            AlignForWidth(width);
            if (ImGui::Button("Save")) {
                json settingsFile;
                settingsFile["gamePath"] = *gamePath;
                settingsFile["language"] = language->value;
                std::ofstream file("Assets/Data/Settings.json");
                languageFile = std::format("{0}.csv", language->value);
                languageFilePath = std::format("Assets/Data/languages/{0}", languageFile);
                localizedStrings = Utils::loadTranslation(languageFilePath);
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
    bool debugMode = true;
    TankType::Type typeToShow;
    std::map<TankType::Type, Tank> tankList;
    std::unordered_map<TankType::Type, Stats> newTankStats;
    std::vector<std::string> tankModule = { "gun", "turret", "suspension", "engine", "armor" };
    std::vector<Country> countryList = Country::generateCountryList();
    Country* country = &countryList[0];
    std::vector<Language> languageList = Language::getLanguageList();
    Language* language;
    Settings settings;

    bool mainWindowOpen = true;
    bool mainMenuOpen = true;
    bool generateWindowOpen = false;
    bool optionWindowOpen = false;
    bool designerWindowOpen = false;
    bool allGenerationWindowOpen = false;
    bool allCountries = false;

    bool fileModified = false;

    std::map<std::string, std::string> tankIconNames;

    std::map<Gun::Category, std::vector<Gun>> gunList = Gun::generateGunList();
    std::map<Gun::Category, bool> gunCateogryWindowOpen;
    std::map<Gun::Name, bool> gunNameWindowOpen;

    std::string languageFile;
    std::string languageFilePath;
    std::unordered_map<int, std::string> localizedStrings;
    std::unordered_map<int, std::string> converterToGameName = Utils::loadTranslation("Assets/Data/converter.csv");

    ImVec4 backgroundColor = ImVec4(0.831f, 0.902f, 0.945f, 1.00f);
    ImVec4 windowColor = ImVec4(0.149f, 0.137f, 0.125f, 1.00f);
    ImVec4 buttonColor = ImVec4(0.231f, 0.255f, 0.224f, 1.00f);

    const char* getLocalizedString(std::string text) {
        int id = Utils::hash(text.c_str());
        return localizedStrings[id].c_str();
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
        float totalSpeedP = newStats.speedP + ((tank.engineLevel * 10) + (tank.armorLevel * -5.0));
        float reliabilityP = newStats.reliabilityP + ((tank.engineLevel * -1.5) + (tank.armorLevel * 1.5));
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

    void generateIdeaFile(Country* country) {
        std::vector<std::string> fileLines;
        std::string gamePath = settings.getGamepath();
        std::string fileName = std::format("{0}.txt", country->tag, country->name);
        std::string filePath = std::format("{0}\\common\\ideas\\{1}", gamePath, fileName);
        std::string backupFilePath = std::format("{0}\\history\\countries\\{1}.back", gamePath, fileName);

        std::ifstream  src(filePath, std::ios::binary);
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
        int linesToAddStart = country->ideaPosIdea;
        int counterTemplateLine = 0;
        std::vector<std::string> newLines;
        std::ifstream ideaFile(std::format("/Assets/Data/{0}", fileName), std::ios::binary);
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
        if (std::rename(std::format("/Assets/Data/{0}", fileName).c_str(),
            filePath.c_str()) != 0) {
            perror("Error moving file");
        }
        else {
            std::cout << "File moved successfully" << std::endl;
        };

    }

    std::string getRandomIcon(TankType::Type type) {
        std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(type));
        auto it = icon.cbegin();
        int random = rand() % icon.size();
        std::advance(it, random);
        return it->first;
    }
};