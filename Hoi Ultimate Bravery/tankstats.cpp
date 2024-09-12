#include "tankstats.hpp"

std::array<std::string, 30> TankStats::getStatsKeyArray()
{
	return {
		"speed",
		"speedP",
		"reliability",
		"reliabilityP",
		"softAttack",
		"softAttackP",
		"hardAttack",
		"hardAttackP",
		"piercing",
		"piercingP",
		"breakthrough",
		"breakthroughP",
		"airAttack",
		"airAttackP",
		"productionCost",
		"productionCostP",
		"armor",
		"armorP",
		"defense",
		"defenseP",
		"entrenchment",
		"entrenchmentP",
		"hardness",
		"hardnessP",
		"fuelUsage",
		"fuelUsageP",
		"fuelCapacity",
		"fuelCapacityP",
		"supplyUse",
		"supplyUseP"
	   };
}

std::string TankStats::getShowStat(int row)
{
	switch (row)
	{
	case 0: return std::format("Speed: {0} Km/h", speed);
	case 1: return std::format("Reliability: {0} %%", reliability);
	case 2: return std::format("Soft Attack: {0}", softAttack);
	case 3: return std::format("Hard Attack: {0}", hardAttack);
	case 4: return std::format("Armor: {0}", armor);
	default:
		break;
	}
}
