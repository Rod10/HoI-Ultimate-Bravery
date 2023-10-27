#include "country.hpp"
CountryList* CountryList::countryList_ = nullptr;;

CountryList* CountryList::GetInstance() {
    if (countryList_ == nullptr) {
        std::vector<Country> countryList;

        std::ifstream fC("Assets/Data/Country.json");
        json data = json::parse(fC);
        fC.close();
        for (auto& countryData : data.items()) {
            std::string name = countryData.value().at("name");
            std::string tag = countryData.value().at("tag");
            int ideaPosIdea = countryData.value().at("ideaPosIdea");
            int ideaPos = countryData.value().at("countriesSettings").at("ideaPos");
            bool major = countryData.value().at("major");
            std::map<std::string, DlcSettings> dlcSettings;
            for (auto& test : data[countryData.key()]["countriesSettings"].items()) {
                if (test.key() != "ideaPos") {
                    int linesToDeleteStart = test.value().at("linesToDeleteStart");
                    int linesToDeleteEnd = test.value().at("linesToDeleteEnd");
                    int lineToDeleteCount = linesToDeleteEnd - linesToDeleteStart;
                    DlcSettings dlcSetting = DlcSettings(linesToDeleteStart, linesToDeleteEnd, lineToDeleteCount);
                    dlcSettings.insert(std::pair <std::string, DlcSettings>(test.key(), dlcSetting));
                }
            }
            CountriesSettings countriesSettings = CountriesSettings(ideaPos, dlcSettings);
            Country country = Country(
                name,
                tag,
                countriesSettings,
                ideaPosIdea,
                major
            );
            if (country.major) {
                countryList.push_back(country);
            }
        }
        countryList_ = new CountryList(countryList);
    }
    return countryList_;
}

std::vector<Country>* CountryList::getList() {
    return &list_;
}

void Country::setNewUnits(UnitType::Type unitType, Ship unit) {
    auto& shipTypeList = std::any_cast<std::map<Hull::Type, std::vector<std::any>>&>(units.find(unitType)->second);
    if (this->getShipHullListSize((int)unit.hull) == 0) {
        shipTypeList.find(unit.hull)->second.push_back(unit);
        shipTypeList.find(unit.hull)->second.push_back(Stats());
    }
    else {
        shipTypeList.find(unit.hull)->second.clear();
        shipTypeList.find(unit.hull)->second.push_back(unit);
        shipTypeList.find(unit.hull)->second.push_back(Stats());
    }
}

void Country::setNewUnits(UnitType::Type unitType, Tank unit) {
    auto &tankTypeList = std::any_cast<std::map<TankType::Type, std::vector<std::any>>&>(units.find(unitType)->second);
    if (this->getTankTypeListSize((int)unit.type) == 0) {
        tankTypeList.find(unit.type)->second.push_back(unit);
        tankTypeList.find(unit.type)->second.push_back(Tank::generateNewStats(unit));
    }
    else {
        tankTypeList.find(unit.type)->second.clear();
        tankTypeList.find(unit.type)->second.push_back(unit);
        tankTypeList.find(unit.type)->second.push_back(Tank::generateNewStats(unit));
    }
}

void Country::setNewUnits(UnitType::Type unitType, Plane unit) {
    auto& planeTypeList = std::any_cast<std::map<PlaneRole::Role, std::vector<std::any>>&>(units.find(unitType)->second);
    planeTypeList.find(unit.role)->second.push_back(unit);
    planeTypeList.find(unit.role)->second.push_back(Stats());
}

Ship Country::getShipByHull(int type) {
    auto& shipTypeList = std::any_cast<std::map<Hull::Type, std::vector<std::any>>&>(units.find(UnitType::Ship)->second);
    return std::any_cast<Ship>(shipTypeList.find(static_cast<Hull::Type>(type))->second[0]);
}

int Country::getShipHullListSize(int hull) {
    auto& shipTypeList = std::any_cast<std::map<Hull::Type, std::vector<std::any>>&>(units.find(UnitType::Ship)->second);
    return shipTypeList.find(static_cast<Hull::Type>(hull))->second.size();
}

std::tuple<Tank, TankStats> Country::getTankByType(int type) {
    auto& tankTypeList = std::any_cast<std::map<TankType::Type, std::vector<std::any>>&>(units.find(UnitType::Tank)->second);
    return { 
        std::any_cast<Tank>(tankTypeList.find(static_cast<TankType::Type>(type))->second[0]),
        std::any_cast<TankStats>(tankTypeList.find(static_cast<TankType::Type>(type))->second[1]),
    };
}

int Country::getTankTypeListSize(int type) {
    auto& tankTypeList = std::any_cast<std::map<TankType::Type, std::vector<std::any>>&>(units.find(UnitType::Tank)->second);
    return tankTypeList.find(static_cast<TankType::Type>(type))->second.size();
}


Plane Country::getPlaneByRole(int type) {
    auto& planeTypeList = std::any_cast<std::map<PlaneRole::Role, std::vector<std::any>>&>(units.find(UnitType::Plane)->second);
    return std::any_cast<Plane>(planeTypeList.find(static_cast<PlaneRole::Role>(type))->second[0]);
}

std::vector<Country> Country::generateCountryList() {
    std::vector<Country> countryList;

    std::ifstream fC("Assets/Data/Country.json");
    json data = json::parse(fC);
    fC.close();
    for (auto& countryData : data.items()) {
        std::string name = countryData.value().at("name");
        std::string tag = countryData.value().at("tag");
        int ideaPosIdea = countryData.value().at("ideaPosIdea");
        int ideaPos = countryData.value().at("countriesSettings").at("ideaPos");
        bool major = countryData.value().at("major");
        std::map<std::string, DlcSettings> dlcSettings;
        for (auto& test : data[countryData.key()]["countriesSettings"].items()) {
            if (test.key() != "ideaPos") {
                int linesToDeleteStart = test.value().at("linesToDeleteStart");
                int linesToDeleteEnd = test.value().at("linesToDeleteEnd");
                int lineToDeleteCount = linesToDeleteEnd - linesToDeleteStart;
                DlcSettings dlcSetting = DlcSettings(linesToDeleteStart, linesToDeleteEnd, lineToDeleteCount);
                dlcSettings.insert(std::pair <std::string, DlcSettings>(test.key(), dlcSetting));
            }
        }
        CountriesSettings countriesSettings = CountriesSettings(ideaPos, dlcSettings);
        Country country = Country(
            name,
            tag,
            countriesSettings,
            ideaPosIdea,
            major
        );
        if (country.major) {
            countryList.push_back(country);
        }
    }

    return countryList;
}