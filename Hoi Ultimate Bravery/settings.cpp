#include "settings.hpp"
Settings* Settings::settings_ = nullptr;;

Settings* Settings::getInstance() {
    if (settings_ == nullptr) {
        std::ifstream fC("Assets/Data/Settings.json");
        json data = json::parse(fC);
        fC.close();

        std::string gamePath = data["gamePath"];
        Language language;
        std::vector<Language> languageList = Language::getLanguageList();
        for (Language l : languageList) {
            std::string value = l.value;
            std::string test = data["language"];
            if (value == test) {
                language = l;
            }
        }
        settings_ = new Settings(gamePath, language);
    }
    return settings_;
}

std::string Settings::getGamepath()
{
    return gamePath_;
}

Language Settings::getLanguage()
{
    return language_;
}
