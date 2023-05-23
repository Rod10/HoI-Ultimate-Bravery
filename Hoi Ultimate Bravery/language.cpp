#include "language.hpp"

std::vector<Language> Language::getLanguageList() {

    std::vector<Language> languageList;

    std::ifstream fC("Assets/Data/Languages/languages.json");
    json data = json::parse(fC);
    fC.close();
    int index = 0;
    for (auto& languageData : data.items()) {
        std::vector<std::string> nameListVector;
        std::string value = languageData.value().at("value");
        for (auto& namesList : languageData.value().at("name").items()) {
            std::cout << namesList.value() << std::endl;
            nameListVector.push_back(namesList.value());
        }
        Language language = Language(value, nameListVector, index);
        languageList.push_back(language);
        index++;
    }
    return languageList;
}
