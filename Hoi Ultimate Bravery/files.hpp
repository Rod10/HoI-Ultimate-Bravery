#pragma once
#include "country.hpp"
#include "tank.hpp"
#include "settings.hpp"

class Files {
public:

    static bool cmpA(std::pair<std::string, int>& a,
        std::pair<std::string, int>& b)
    {
        return a.second < b.second;
    }
    static bool cmpD(std::pair<std::string, int>& a,
        std::pair<std::string, int>& b)
    {
        return a.second > b.second;
    }

    // Function to sort the map according
    // to value in a (key-value) pairs
    static std::vector<std::pair<std::string, int> > sort(std::map<std::string, int>& M, std::string mode)
    {
        // Declare vector of pairs
        std::vector<std::pair<std::string, int> > A;

        // Copy key-value pair from Map
        // to vector of pairs
        for (auto& it : M) {
            A.push_back(it);
        }

        /*if (mode == "addition") {
            // Sort using comparator function
            std::sort(A.begin(), A.end(), cmpA);
        }
        else {
            // Sort using comparator function
            std::sort(A.begin(), A.end(), cmpD);
        }*/
        std::sort(A.begin(), A.end(), cmpD);

        /*std::cout << mode << std::endl;
        // Print the sorted value
        for (auto& it : A) {

            std::cout << it.first << ' '
                << it.second << std::endl;
        }*/

        return A;
    }


    static void generateCountryFile(Country* country, std::unordered_map<int, std::string> converterToGameName, bool debugMode) {
        Country newCountry = Country(*country);
        std::vector < std::string > tempFile;
        std::string gamePath = Settings::getInstance()->getGamepath();
        std::string fileName = std::format("{0} - {1}.txt", country->tag, country->name);
        std::string filePath = std::format("{0}/history/countries/{1}", gamePath, fileName);

        std::string newFilePath = "./Assets/Data/Files/NewFiles/countries/";
        std::ofstream newFile(std::format("{0}{1}", newFilePath, fileName), std::ios::binary);

        std::ifstream src(filePath, std::ios::binary);
        std::string line;

        while (std::getline(src, line)) {
            tempFile.push_back(line);
        }
        src.close();

        makeOrder("deletion", &tempFile, &newCountry, converterToGameName);
        tempFile.insert(tempFile.begin() + country->coutriesSettings.ideaPos, "\tultimate_bravery");
        makeOrder("addition", &tempFile, &newCountry, converterToGameName);

        for (int i = 0; i < tempFile.size(); i++) {
            newFile << tempFile[i] << std::endl;
        }
        newFile.close();

        const auto copyOptions = std::filesystem::copy_options::update_existing
            | std::filesystem::copy_options::recursive;
        std::filesystem::copy_file(std::format("{0}{1}", newFilePath, fileName), filePath, copyOptions);
    
    }

    static void generateIdeaFile(Country country) {
       /* std::vector<std::string< fileLines;
        std::string gamePath = Settings::getInstance()->getGamepath();
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
        std::vector<std::string< newLines;
        std::ifstream ideaFile(std::format("/Assets/Data/{0}", fileName), std::ios::binary);
        while (std::getline(ideaFile, line)) {
            newLines.push_back(line);
        }
        for (int i = 0; i < fileLines.size(); i++) {
            if (i <= linesToAddStart && counterTemplateLine < newLines.size()) {
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
        };*/
    }

    static void makeOrder(std::string mode, std::vector<std::string>* tempFile, Country* country, std::unordered_map<int, std::string> converterToGameName) {
        auto& countriesSettings = country->coutriesSettings.dlcSettings;

        std::map<std::string, int> test;

        for (auto& [dlc, dlcSettings] : countriesSettings) {
            test.insert(std::pair<std::string, int>(dlc, dlcSettings.linesToDeleteStart));
        }
        auto dlcSettingsSorted = sort(test, mode);

        int previousOffset = 0;
        int i = 0;
        for (auto& [dlc, dlcSettings] : dlcSettingsSorted) {
            auto& settings = countriesSettings.find(dlc)->second;

            if (mode == "deletion") {
                bool removed = remove(tempFile, country, dlc, settings.linesToDeleteStart - 1, settings.linesToDeleteEnd, settings.lineToDeleteCount);
                if (removed) {
                    if (i == 1) {
                        countriesSettings.find(dlcSettingsSorted[i - 1].first)->second.linesToDeleteStart -= settings.lineToDeleteCount;
                    }
                    else if (i == 2) {
                        countriesSettings.find(dlcSettingsSorted[0].first)->second.linesToDeleteStart -= settings.lineToDeleteCount;
                        countriesSettings.find(dlcSettingsSorted[i - 1].first)->second.linesToDeleteStart -= settings.lineToDeleteCount;
                    }
                }
            }
            else if (mode == "addition") {
                insert(tempFile, country, dlc, settings.linesToDeleteStart, converterToGameName);
            }
            i++;
        }

        /*for (int i = 0; i < 3; ++i) {
            int start = startOrder[i];
            auto& settings = (start == startMTG) ? mtgSettings : (start == startNSB) ? nsbSettings : bbaSettings;

            // Calcule l'offset en fonction de la valeur pr�c�dente
            int offset = previousOffset;
            
            int newLinesToDeleteStart = settings.linesToDeleteStart - 1;
            int newLinesToDeleteEnd = settings.linesToDeleteEnd - 1;

            if (mode == "deletion") {
                // Fait l'op�ration pour le d�marrage actuel
                remove(tempFile, newLinesToDeleteStart, newLinesToDeleteEnd, settings.lineToDeleteCount);
            }
            else if (mode == "addition") {
                newLinesToDeleteStart = settings.linesToDeleteStart - previousOffset;
                //tempFile->insert(tempFile->begin() + newLinesToDeleteStart + i, "testy");
            }
            // Met � jour la valeur pr�c�dente
            previousOffset += settings.lineToDeleteCount;
        }*/
    }

    static bool remove(std::vector<std::string>* tempFile, Country* country, std::string dlc, int start, int end, int count) {
        if ((dlc == "mtg" && !country->shipList.empty())
            || (dlc == "nsb" && !country->tankList.empty())
            || (dlc == "bba" && !country->planeList.empty())) {
            for (int i = 0; i < tempFile->size(); i++) {
                if (i <= start && i <= end && count != 0) {
                    tempFile->erase(tempFile->begin() + start);
                    count--;
                }
            }
            return true;
        }
        return false;
    }

    static void insert(std::vector<std::string>* tempFile, Country* country, std::string dlc, int newLinesToDeleteStart, std::unordered_map<int, std::string> converterToGameName) {
        if (dlc == "mtg" && !country->shipList.empty()) {
            for (auto& [hull, ship] : country->shipList) {
                int index = 0;
                std::string line;
                int counterTemplateLine = 0;
                std::vector<std::string> replacementList{
                    "\tcreate_equipment_variant = {",
                    std::format("\t\tname = {0}", Hull::typeToString(ship.hull)),
                    std::format("\t\ttype = {0}", ShipType::shipTypeToString(ship.type)),
                    "\t\tmodules = {"
                };

                for (auto& module : ship.fixedModule) {
                    std::string key = Module::moduleTypeToEquipmentString(module.type);
                    std::string value = Module::typeToEquipmentFileValue(module, ship.hull, ship.type);
                    std::cout << std::format("\t\t\t{0} = {1}", key, value) << std::endl;
                    replacementList.push_back(std::format("\t\t\t{0} = {1}", key, value));
                }

                for (auto& module : ship.customModule) {
                    std::string key = Module::customKeyEquipmentFile(ship.type, ship.version, index);
                    if (!key.empty()) {
                        std::string value = Module::typeToEquipmentFileValue(module, ship.hull, ship.type);
                        replacementList.push_back(std::format("\t\t\t{0} = {1}", key, value));
                        index++;
                    }
                }
                replacementList.push_back("\t\t}");
                replacementList.push_back("\t}");
                for (int i = 0; i < tempFile->size(); i++) {
                    if (i >= newLinesToDeleteStart && counterTemplateLine < replacementList.size()) {
                        tempFile->insert(tempFile->begin() + i, replacementList[counterTemplateLine]);
                        counterTemplateLine++;
                    }
                }
            }
        }
        else if (dlc == "nsb" && !country->tankList.empty()) {
            for (auto& [type, tank] : country->tankList) {
                std::ifstream templateFile("./Assets/Data/Files/tank_equipment_template.txt", std::ios::binary);
                int index;
                std::string line;        
                std::vector<std::string> templateLine;
                int counterTemplateLine = 0;
                std::vector<std::string> replacementList{ Tank::tankTypeToString(tank.type),
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

                for (int i = 0; i < tempFile->size(); i++) {
                    if (i >= newLinesToDeleteStart && counterTemplateLine < templateLine.size()) {
                        tempFile->insert(tempFile->begin() + i, templateLine[counterTemplateLine]);
                        counterTemplateLine++;
                    }
                }
            }
        }
        else if (dlc == "bba" && !country->planeList.empty()) {
            for (auto& [role, plane] : country->planeList) {
                int index = 0;
                std::string line;
                int counterTemplateLine = 0;
                std::vector<std::string> replacementList{
                    "\tcreate_equipment_variant = {",
                    std::format("\t\tname = {0}", PlaneRole::roleToString(plane.role)),
                    std::format("\t\ttype = {0}", PlaneType::typeToString(plane.type)),
                    "\t\tmodules = {",
                };

                for (auto& module : plane.fixed) {
                    std::string key;
                    std::string value = PlaneModule::moduleToEquipmentStringValue(module, plane.type);
                    if (module.type == PlaneModule::None) {
                        value = "empty";
                    }
                    if (index == 0) key = "fixed_main_weapon_slot";
                    else key = std::format("fixed_auxiliary_weapon_slot_{0}", index);
                    replacementList.push_back(std::format("\t\t\t{0} = {1}", key, value));
                    index++;
                }

                replacementList.push_back(std::format("\t\t\tengine_type_slot = {0}", PlaneEngine::engineToEquipmentValueString(plane.engine)));
                index = 1;
                for (auto& module : plane.fixed) {
                    std::string key = std::format("special_type_slot_{0}", index);
                    std::string value;
                    replacementList.push_back(std::format("\t\t\t{0} = {1}", key, value));
                    index++;
                }

                replacementList.push_back("\t\t}");
                replacementList.push_back("\t}");
                for (int i = 0; i < tempFile->size(); i++) {
                    if (i >= newLinesToDeleteStart && counterTemplateLine < replacementList.size()) {
                        tempFile->insert(tempFile->begin() + i, replacementList[counterTemplateLine]);
                        counterTemplateLine++;
                    }
                }
            }
        }
    }
};