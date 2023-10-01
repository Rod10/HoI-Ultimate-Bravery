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

        if (mode == "addition") {
            // Sort using comparator function
            std::sort(A.begin(), A.end(), cmpA);
        }
        else {
            // Sort using comparator function
            std::sort(A.begin(), A.end(), cmpD);
        }

        std::cout << mode << std::endl;
        // Print the sorted value
        for (auto& it : A) {

            std::cout << it.first << ' '
                << it.second << std::endl;
        }

        return A;
    }


    static void generateCountryFile(Country* country, std::unordered_map<int, std::string> converterToGameName, bool debugMode) {
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

        int startMTG = country->coutriesSettings.dlcSettings.find("mtg")->second.linesToDeleteStart;
        int startNSB = country->coutriesSettings.dlcSettings.find("nsb")->second.linesToDeleteStart;
        int startBBA = country->coutriesSettings.dlcSettings.find("bba")->second.linesToDeleteStart;


        makeOrder("deletion", &tempFile, country, converterToGameName);
        tempFile.insert(tempFile.begin() + country->coutriesSettings.ideaPos, "\tultimate_bravery");
        makeOrder("addition", &tempFile, country, converterToGameName);

        for (int i = 0; i < tempFile.size(); i++) {
            newFile << tempFile[i] << std::endl;
        }
        newFile.close();
    
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
        auto countriesSettings = country->coutriesSettings.dlcSettings;

        std::map<std::string, int> test;

        for (auto& [dlc, dlcSettings] : countriesSettings) {
            test.insert(std::pair<std::string, int>(dlc, dlcSettings.linesToDeleteStart));
        }
        auto dlcSettingsSorted = sort(test, mode);

        int previousOffset = 0;
        int i = 0;
        for (auto& [dlc, dlcSettings] : dlcSettingsSorted) {
            auto& settings = countriesSettings.find(dlc)->second;

            // Calcule l'offset en fonction de la valeur précédente
            int offset = previousOffset;

            int newLinesToDeleteStart = settings.linesToDeleteStart - 1;
            int newLinesToDeleteEnd = settings.linesToDeleteEnd - 1;

            if (mode == "deletion") {
                // Fait l'opération pour le démarrage actuel
                remove(tempFile, country, dlc, newLinesToDeleteStart, newLinesToDeleteEnd, settings.lineToDeleteCount);
            }
            else if (mode == "addition") {
                newLinesToDeleteStart = (settings.linesToDeleteStart - previousOffset) + i;
                insert(tempFile, country, dlc, newLinesToDeleteStart, converterToGameName);
            }
            // Met à jour la valeur précédente
            previousOffset += settings.lineToDeleteCount;
            i++;
        }

        /*for (int i = 0; i < 3; ++i) {
            int start = startOrder[i];
            auto& settings = (start == startMTG) ? mtgSettings : (start == startNSB) ? nsbSettings : bbaSettings;

            // Calcule l'offset en fonction de la valeur précédente
            int offset = previousOffset;
            
            int newLinesToDeleteStart = settings.linesToDeleteStart - 1;
            int newLinesToDeleteEnd = settings.linesToDeleteEnd - 1;

            if (mode == "deletion") {
                // Fait l'opération pour le démarrage actuel
                remove(tempFile, newLinesToDeleteStart, newLinesToDeleteEnd, settings.lineToDeleteCount);
            }
            else if (mode == "addition") {
                newLinesToDeleteStart = settings.linesToDeleteStart - previousOffset;
                //tempFile->insert(tempFile->begin() + newLinesToDeleteStart + i, "testy");
            }
            // Met à jour la valeur précédente
            previousOffset += settings.lineToDeleteCount;
        }*/
    }

    static void remove(std::vector<std::string>* tempFile, Country* country, std::string dlc, int start, int end, int count) {
        if ((dlc == "mtg" && !country->shipList.empty())
            || (dlc == "nsb" && !country->tankList.empty())
            || (dlc == "bba" && !country->planeList.empty())) {
            for (int i = 0; i < tempFile->size(); i++) {
                if (i <= start && i <= end && count != 0) {
                    tempFile->erase(tempFile->begin() + start);
                    count--;
                }
            }
        }
    }

    static void insert(std::vector<std::string>* tempFile, Country* country, std::string dlc, int newLinesToDeleteStart, std::unordered_map<int, std::string> converterToGameName) {
        if (dlc == "mtg" && !country->shipList.empty()) {
            for (auto& [hull, ship] : country->shipList) {
                std::ifstream templateFile("./Assets/Data/Files/ship_equipment_template.txt", std::ios::binary);
                int index;
                std::string line;
                std::vector<std::string> templateLine;
                int counterTemplateLine = 0;
                std::vector<std::string> replacementList{
                    Hull::typeToString(ship.hull),
                    ShipType::shipTypeToString(ship.type),
                };

                for (auto& module : ship.fixedModule) {
                    Module::moduleTypeToEquipmentString(module.type);
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
            tempFile->insert(tempFile->begin() + newLinesToDeleteStart, "plane");
        }
    }
};