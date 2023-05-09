#include "country.hpp"

std::vector<Country> Country::generateCountryList()
{
    std::vector<Country> countryList;

    std::ifstream fC("Assets/Data/Country.json");
    json data = json::parse(fC);
    fC.close();
    for (auto& countryData : data.items()) {
        std::cout << countryData.value().at("name") << std::endl;
        std::string name = countryData.value().at("name");
        std::string tag = countryData.value().at("tag");
        int countryPosIdea = countryData.value().at("countryPosIdea");
        int linesToDeleteStart = countryData.value().at("linesToDeleteStart");
        int linesToDeleteEnd = countryData.value().at("linesToDeleteEnd");
        int ideaPosIdea = countryData.value().at("ideaPosIdea");
        Country country = Country(
            name,
            tag,
            countryPosIdea,
            linesToDeleteStart,
            linesToDeleteEnd,
            ideaPosIdea
        );
        countryList.push_back(country);
    }

    return countryList;
}
