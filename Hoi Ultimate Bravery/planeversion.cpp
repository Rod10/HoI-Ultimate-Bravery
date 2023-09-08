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
    int planeVersionInt = rand() % planeKey.size();
    PlaneVersion::Version planeVersion = PlaneVersion::stringToVersion(planeKey[planeVersionInt]);
    return planeVersion;
}
