#include "planeversion.hpp"

PlaneVersion::Version PlaneVersion::generateRandom(PlaneType::Type type)
{
    srand(time(0));
    std::ifstream f("Assets/Data/Plane/Plane.json");
    json planeData = json::parse(f)[PlaneType::typeToString(type)];
    f.close();

    std::vector<std::string> planeKey;
    for (auto& el : planeData.items()) {
        planeKey.push_back(el.key());
    }
    std::string planeVersionString = *Utils::select_randomly(planeKey.begin(), planeKey.end());
    PlaneVersion::Version planeVersion = PlaneVersion::stringToVersion(planeVersionString);
    return planeVersion;
}
