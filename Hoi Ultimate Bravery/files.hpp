#pragma once
#include "country.hpp"
#include "tank.hpp"
#include "settings.hpp"
class Files {
public:
	static void generateCountryFile(Tank tank, Country* country, std::unordered_map<int, std::string> converterToGameName, bool debugMode) {
        std::vector<std::string> fileLines;

        std::string gamePath = Settings::getInstance()->getGamepath();
        std::string fileName = std::format("{0} - {1}.txt", country->tag, country->name);
        std::string filePath = std::format("{0}\\history\\countries\\{1}", gamePath, fileName);
        std::string backupFilePath = std::format("{0}\\history\\countries\\{1}.back", gamePath, fileName);

        std::string newFilePath = "/Assets/Data/Files/NewFiles/Country/";
        std::ifstream src(std::format("{0}\\history\\countries\\{1}", gamePath, fileName), std::ios::binary);
        std::ofstream newFile(std::format("{0}{1}", newFilePath, fileName), std::ios::binary);
        std::string line;

        //generate a vector of line from file
        while (std::getline(src, line)) {
            fileLines.push_back(line);
        }
        src.close();

        //rename original file to .back
        if (std::rename(filePath.c_str(),
            backupFilePath.c_str()) != 0)
            perror("Error moving file");
        else
            std::cout << "File moved successfully" << std::endl;

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
        if (!debugMode) {
            if (std::rename(std::format("{0}{1}", newFilePath, fileName).c_str(),
                filePath.c_str()) != 0) {
                perror("Error moving file");
            }
            else {
                std::cout << "File moved successfully" << std::endl;
            };
        }
    }

    static void generateIdeaFile(Country* country) {
        std::vector<std::string> fileLines; 
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
};