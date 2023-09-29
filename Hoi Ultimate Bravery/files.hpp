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


        makeOrder(startMTG, startNSB, startBBA, "deletion", &tempFile, country);
        tempFile.insert(tempFile.begin() + country->coutriesSettings.ideaPos, "\tultimate_bravery");
        makeOrder(startMTG, startNSB, startBBA, "addition", &tempFile, country);

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

    /*static void makeOrder(int startMTG, int startNSB, int startBBA, std::string mode, std::vector<std::string>* tempFile, Country* country) {
        auto countriesSettings = country->coutriesSettings.dlcSettings;
        auto mtgSettings = countriesSettings.find("mtg")->second;
        auto nsbSettings = countriesSettings.find("nsb")->second;
        auto bbaSettings = countriesSettings.find("bba")->second;
        if ((startMTG < startNSB && startMTG < startBBA) && (startNSB < startBBA)) {
            if (mode == "deletion") {
                // do startMTG
                remove(tempFile, mtgSettings.linesToDeleteStart, mtgSettings.linesToDeleteEnd, mtgSettings.lineToDeleteCount);
                // do startNSB
                remove(tempFile, nsbSettings.linesToDeleteStart - mtgSettings.lineToDeleteCount, nsbSettings.linesToDeleteEnd - mtgSettings.lineToDeleteCount, nsbSettings.lineToDeleteCount);
                // do startBBA
                remove(tempFile, bbaSettings.linesToDeleteStart - mtgSettings.lineToDeleteCount - nsbSettings.lineToDeleteCount, bbaSettings.linesToDeleteEnd - mtgSettings.lineToDeleteCount - nsbSettings.lineToDeleteCount, bbaSettings.lineToDeleteCount);
            }
            else if (mode == "addition") {

            }
        }
        else if ((startMTG < startNSB || startMTG < startBBA) && (startNSB >= startBBA)) {
            if (mode == "deletion") {
                // do startMTG
                remove(tempFile, mtgSettings.linesToDeleteStart, mtgSettings.linesToDeleteEnd, mtgSettings.lineToDeleteCount);
                // do startBBA
                remove(tempFile, bbaSettings.linesToDeleteStart - mtgSettings.lineToDeleteCount, bbaSettings.linesToDeleteEnd - mtgSettings.lineToDeleteCount, bbaSettings.lineToDeleteCount);
                // do startNSB
                remove(tempFile, nsbSettings.linesToDeleteStart - mtgSettings.lineToDeleteCount - bbaSettings.lineToDeleteCount, nsbSettings.linesToDeleteEnd - mtgSettings.lineToDeleteCount - bbaSettings.lineToDeleteCount, nsbSettings.lineToDeleteCount);
            }
            else if (mode == "addition") {

            }
        }
        else if ((startNSB < startMTG || startNSB < startBBA) && (startMTG < startBBA)) {
            if (mode == "deletion") {
                // do startNSB
                remove(tempFile, nsbSettings.linesToDeleteStart, nsbSettings.linesToDeleteEnd, nsbSettings.lineToDeleteCount);
                // do startMTG
                remove(tempFile, mtgSettings.linesToDeleteStart - nsbSettings.lineToDeleteCount, mtgSettings.linesToDeleteEnd - nsbSettings.lineToDeleteCount, mtgSettings.lineToDeleteCount);
                // do startBBA
                remove(tempFile, bbaSettings.linesToDeleteStart - mtgSettings.lineToDeleteCount - nsbSettings.lineToDeleteCount, bbaSettings.linesToDeleteEnd - mtgSettings.lineToDeleteCount - nsbSettings.lineToDeleteCount, bbaSettings.lineToDeleteCount);
            }
            else if (mode == "addition") {

            }
        }
        else if ((startNSB < startMTG || startNSB < startBBA) && (startMTG >= startBBA)) {
            if (mode == "deletion") {
                // do startNSB
                remove(tempFile, nsbSettings.linesToDeleteStart, nsbSettings.linesToDeleteEnd, nsbSettings.lineToDeleteCount);
                // do startBBA
                remove(tempFile, bbaSettings.linesToDeleteStart - nsbSettings.lineToDeleteCount, bbaSettings.linesToDeleteEnd - nsbSettings.lineToDeleteCount, bbaSettings.lineToDeleteCount);
                // do startMTG
                remove(tempFile, mtgSettings.linesToDeleteStart - nsbSettings.lineToDeleteCount - bbaSettings.lineToDeleteCount, mtgSettings.linesToDeleteEnd - nsbSettings.lineToDeleteCount - bbaSettings.lineToDeleteCount, mtgSettings.lineToDeleteCount);
            }
            else if (mode == "addition") {

            }
        }
        else if ((startBBA < startMTG || startBBA < startNSB) && (startMTG < startNSB)) {
            if (mode == "deletion") {
                // do startBBA
                remove(tempFile, bbaSettings.linesToDeleteStart, bbaSettings.linesToDeleteEnd, bbaSettings.lineToDeleteCount);
                // do startMTG
                remove(tempFile, mtgSettings.linesToDeleteStart - bbaSettings.lineToDeleteCount, mtgSettings.linesToDeleteEnd - bbaSettings.lineToDeleteCount, mtgSettings.lineToDeleteCount);
               // do startNSB
                remove(tempFile, nsbSettings.linesToDeleteStart - mtgSettings.lineToDeleteCount - bbaSettings.lineToDeleteCount, nsbSettings.linesToDeleteEnd - mtgSettings.lineToDeleteCount - bbaSettings.lineToDeleteCount, nsbSettings.lineToDeleteCount);
            }
            else if (mode == "addition") {

            }
        }
        else {
            if (mode == "deletion") {
                // do startBBA
                remove(tempFile, bbaSettings.linesToDeleteStart, bbaSettings.linesToDeleteEnd, bbaSettings.lineToDeleteCount);
                // do startNSB
                remove(tempFile, nsbSettings.linesToDeleteStart - bbaSettings.lineToDeleteCount, nsbSettings.linesToDeleteEnd - bbaSettings.lineToDeleteCount, nsbSettings.lineToDeleteCount);
                // do startMTG
                remove(tempFile, mtgSettings.linesToDeleteStart - nsbSettings.lineToDeleteCount - bbaSettings.lineToDeleteCount, mtgSettings.linesToDeleteEnd - nsbSettings.lineToDeleteCount - bbaSettings.lineToDeleteCount, mtgSettings.lineToDeleteCount);
            }
            else if (mode == "addition") {

            }
        }
    }*/

    static void makeOrder(int startMTG, int startNSB, int startBBA, std::string mode, std::vector<std::string>* tempFile, Country* country) {
        auto countriesSettings = country->coutriesSettings.dlcSettings;
        auto mtgSettings = countriesSettings.find("mtg")->second;
        auto nsbSettings = countriesSettings.find("nsb")->second;
        auto bbaSettings = countriesSettings.find("bba")->second;

        std::vector<int> startOrder { startMTG, startNSB, startBBA };
        if (mode == "deletion") {
            std::sort(startOrder.rbegin(), startOrder.rend());
        }
        else if (mode == "addition") {
            std::sort(startOrder.begin(), startOrder.end());
        }

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
                insert(tempFile, country, dlc, newLinesToDeleteStart);
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

    static void insert(std::vector<std::string>* tempFile, Country* country, std::string dlc, int newLinesToDeleteStart) {
        if (dlc == "mtg" && !country->shipList.empty()) {
            tempFile->insert(tempFile->begin() + newLinesToDeleteStart, "ship");
        }
        else if (dlc == "nsb" && !country->tankList.empty()) {
            tempFile->insert(tempFile->begin() + newLinesToDeleteStart, "tank");
        }
        else if (dlc == "bba" && !country->planeList.empty()) {
            tempFile->insert(tempFile->begin() + newLinesToDeleteStart, "plane");
        }
    }
};