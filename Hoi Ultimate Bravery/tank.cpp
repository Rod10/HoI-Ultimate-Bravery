#include "tank.hpp"

Tank::Version Tank::generatingRandomVersion(TankType::Type type)
{
	srand(time(0));
	std::ifstream f("Assets/Data/Tank/Tank.json");
	json tankData = json::parse(f)[Tank::tankTypeToString(type)];
	f.close();

	std::vector<std::string> tankKey;
	for (auto& el : tankData.items()) {
		tankKey.push_back(el.key());
	}
	int tankVersionInt = rand() % tankKey.size();
	Tank::Version tankVersion = Tank::tankVersionStringToVersion(tankKey[tankVersionInt]);
	return tankVersion;
}

TankStats Tank::getStatsFromVersion(TankType::Type type, Tank::Version version)
{
	std::ifstream f("Assets/Data/Tank/Tank.json");
	json tankData = json::parse(f)[Tank::tankTypeToString(type)];
	f.close();
	auto statsKey = TankStats::getStatsKeyArray();
	json tankStatsData = tankData[Tank::tankVersionToString(version)]["stats"];
	for (auto& el : statsKey) {
		if (tankStatsData[el].is_null()) {
			tankStatsData[el] = 0.0f;
		}
	}
	Ressources ressources = tankStatsData["ressources"];
	TankStats tankStats = TankStats(ressources, tankStatsData);
	return tankStats;
}

auto getStats(Tank tank, std::string module) {
	switch (tank.tankModuleToInt(module)) {
	case 0: return TankStats(tank.gun.stats);
	case 1: return TankStats(tank.turret.stats);
	case 2: return TankStats(tank.suspension.stats);
	case 3: return TankStats(tank.armor.stats);
	case 4: return TankStats(tank.engine.stats);
	}
}

TankStats Tank::generateNewStats(Tank tank)
{
	std::vector<std::string> tankModule = { "gun", "turret", "suspension", "engine", "armor" };

	TankStats stats;
	TankStats newStats = tank.stats;

	for (auto& module : tankModule) {
		stats = getStats(tank, module);
		newStats += stats;
	}

	//Add Stats of special modules
	for (const SpecialModule& module : tank.specialModules) {
		newStats += module.stats;
	}
	//Add Stats of special modules

	// Base Stats
	float totalSpeedP = newStats.speedP + ((tank.engineLevel * 10) + (tank.armorLevel * -5.0));
	float reliabilityP = newStats.reliabilityP + ((tank.engineLevel * -1.5) + (tank.armorLevel * 1.5));
	float speedf = newStats.speed + (newStats.speed * (totalSpeedP / 100));
	newStats.speed = speedf;

	float reliabilityf = newStats.reliability + reliabilityP;
	newStats.reliability = reliabilityf;
	//Base Stats

	//Combat Stats
	float softAttackF = newStats.softAttack + (newStats.softAttack * (newStats.softAttackP / 100));
	newStats.softAttack = softAttackF;

	float hardAttackF = newStats.hardAttack + (newStats.hardAttack * (newStats.hardAttackP / 100));
	newStats.hardAttack = hardAttackF;

	float piercingF = newStats.piercing + (newStats.piercing * (newStats.piercingP / 100));
	newStats.piercing = piercingF;

	float hardnessF = newStats.hardness + (newStats.hardness * (newStats.hardnessP / 100));
	newStats.hardness = hardnessF;

	float totalArmorP = newStats.armorP + (tank.armorLevel * 8.5);
	float armorF = newStats.armor + (newStats.armor * (totalArmorP / 100));
	newStats.armor = armorF;

	float totalBreakthroughF = newStats.breakthrough + tank.armorLevel * 1.2;
	float breakthroughF = totalBreakthroughF + (totalBreakthroughF * (newStats.breakthroughP / 100));
	newStats.breakthrough = breakthroughF;

	float defenseF = newStats.defense + (newStats.defense * (newStats.defenseP / 100));
	newStats.defense = defenseF;

	float airAttackF = newStats.airAttack + (newStats.airAttack * (newStats.airAttackP / 100));
	newStats.airAttack = airAttackF;
	//Combat Stats
	return newStats;
}

Tank Tank::generateRandomTank()
{
	TankType::Type tankType = static_cast<TankType::Type>(rand() % TankType::Type::Last);
	std::cout << "Tank Type: " << Tank::tankTypeToString(tankType) << std::endl;

	Tank::Version tankVersion = Tank::generatingRandomVersion(tankType);
	TankStats tankStats = Tank::getStatsFromVersion(tankType, tankVersion);

	Turret turret = Turret::generatingRandomTurret(tankType);
	std::cout << "Turret Type: " << TurretType::turretTypeToString(turret.type) << std::endl;

	Gun gun = Gun::generateRandomGun(turret.allowedGun);
	Role::Type role = *Utils::select_randomly(gun.roleAllowed.begin(), gun.roleAllowed.end());

	std::array<SpecialModule, 4> specialModules = SpecialModule::generateSpecialModule();

	Suspension suspension = Suspension::generateRandomSuspension(tankType);

	Armor armor = Armor::generateRandomArmor();
	Engine engine = Engine::generateRandomEngine();
	return Tank(tankType, tankVersion, turret, gun, specialModules, suspension, armor, engine, tankStats, role);
}

Tank Tank::generateRandomTank(TankType::Type type)
{
	Tank::Version tankVersion = Tank::generatingRandomVersion(type);
	TankStats tankStats = Tank::getStatsFromVersion(type, tankVersion);

	Turret turret = Turret::generatingRandomTurret(type);

	Gun gun = Gun::generateRandomGun(turret.allowedGun);
	Role::Type role = *Utils::select_randomly(gun.roleAllowed.begin(), gun.roleAllowed.end());

	std::array<SpecialModule, 4> specialModules = SpecialModule::generateSpecialModule();

	Suspension suspension = Suspension::generateRandomSuspension(type);

	Armor armor = Armor::generateRandomArmor();
	Engine engine = Engine::generateRandomEngine();
	return Tank(type, tankVersion, turret, gun, specialModules, suspension, armor, engine, tankStats, role);
}
