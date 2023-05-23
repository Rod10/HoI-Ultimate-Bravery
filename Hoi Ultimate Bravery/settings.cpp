#include "settings.hpp"

Settings::Settings() {
    std::ifstream fC("Assets/Data/Settings.json");
    json data = json::parse(fC);
    fC.close();

    gamePath = data["gamePath"];
    std::vector<Language> languageList = Language::getLanguageList();
    for (Language l : languageList) {
        if (l.value == data["language"]) {
            language = l;
        }
    }
}

std::string Settings::getGamepath()
{
    return gamePath;
}
