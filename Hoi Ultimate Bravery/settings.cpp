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
        std::vector<Dlc> dlcSettings = {};
        for (auto& dlc : Constant::DLC) {
            if (data["dlc"][0] == dlc) {
                dlcSettings.push_back(Dlc(dlc, true));
            }
            if (data["dlc"][1] == dlc) {
                dlcSettings.push_back(Dlc(dlc, true));
            }
            if (data["dlc"][2] == dlc) {
                dlcSettings.push_back(Dlc(dlc, true));
            }
        }
        settings_ = new Settings(gamePath, language, dlcSettings);
    }
    return settings_;
}

std::string Settings::getGamepath() {
    return gamePath_;
}

Language Settings::getLanguage() {
    return language_;
}

std::vector<Dlc> Settings::getDlc() {
    return dlc_;
}

bool Settings::getDlcOwned(std::string name) {
    for (auto& dlc : dlc_) {
        if (dlc.name == name) {
            return dlc.owned;
        }
    }
    return false;
}