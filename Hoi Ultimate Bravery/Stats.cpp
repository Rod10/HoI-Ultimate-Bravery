#include "stats.hpp"

std::array<std::string, 25> Stats::getStatsKeyArray()
{
	   return { 
		   "year", 
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
		   "hardnessP" 
	   };
}
