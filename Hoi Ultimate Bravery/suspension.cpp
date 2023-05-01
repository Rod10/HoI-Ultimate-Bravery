#include "suspension.hpp"

Suspension Suspension::generateRandomSuspension(TankType::Type type)
{
    auto statsKey = Stats::getStatsKeyArray();

    Suspension::Type suspensionType = static_cast<Suspension::Type>(rand() % Suspension::Type::Last);
    while (type != TankType::Type::Light &&
        (static_cast<Suspension::Type>(rand() % Suspension::Type::Last) == Suspension::Type::HalfTrack
            || static_cast<Suspension::Type>(rand() % Suspension::Type::Last) == Suspension::Type::Wheeled)) {
        suspensionType = static_cast<Suspension::Type>(rand() % Suspension::Type::Last);
    }
    std::string suspensionTypeString = Suspension::typeToString(suspensionType);

    std::ifstream fs("Assets/Data/Suspensions.json");
    json suspensionData = json::parse(fs);
    fs.close();

    json suspensionDataStats = suspensionData[suspensionTypeString]["stats"];
    for (auto& el : statsKey) {
        if (suspensionDataStats[el].is_null()) {
            suspensionDataStats[el] = 0.0f;
        }
    }
    Ressources moduleRessources;
    Stats stats = Stats(moduleRessources, suspensionDataStats);

    Suspension suspension = Suspension(suspensionType, stats);
    return suspension;
}
