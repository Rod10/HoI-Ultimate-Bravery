#include "suspension.hpp"

Suspension Suspension::generateRandomSuspension(TankType::Type type)
{
    srand(time(0));
    auto statsKey = TankStats::getStatsKeyArray();

    std::vector<Suspension::Type> suspensionTypeList;
    for (int i = 0; i < Suspension::Type::Last; i++) {
        suspensionTypeList.push_back(static_cast<Suspension::Type>(i));
    }

    auto suspensionType = *Utils::select_randomly(suspensionTypeList.begin(), suspensionTypeList.end());
    while (type != TankType::Type::Light &&
        (static_cast<Suspension::Type>(rand() % Suspension::Type::Last) == Suspension::Type::HalfTrack
            || static_cast<Suspension::Type>(rand() % Suspension::Type::Last) == Suspension::Type::Wheeled)) {
        suspensionType = static_cast<Suspension::Type>(rand() % Suspension::Type::Last);
    }
    std::string suspensionTypeString = Suspension::typeToString(suspensionType);

    std::ifstream fs("Assets/Data/Tank/Suspensions.json");
    json suspensionData = json::parse(fs);
    fs.close();

    json suspensionDataStats = suspensionData[suspensionTypeString]["stats"];
    for (auto& el : statsKey) {
        if (suspensionDataStats[el].is_null()) {
            suspensionDataStats[el] = 0.0f;
        }
    }
    Ressources moduleRessources;
    TankStats stats = TankStats(moduleRessources, suspensionDataStats);

    Suspension suspension = Suspension(suspensionType, stats);
    return suspension;
}
