#include "country.hpp"

std::vector<Country> Country::generateCountryList()
{
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