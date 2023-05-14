#include "settings.hpp"

Settings::Settings() {
    std::ifstream fC("Assets/Data/Settings.json");
    json data = json::parse(fC);
    fC.close();

    gamePath = data["gamePath"];
    //language = data["language"];
}

std::string Settings::getGamepath()
{
    return gamePath;
}
