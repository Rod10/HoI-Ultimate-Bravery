#include "tooltip.hpp"

void renderTankSpeedTooltip(Tank tank) {
	float engineLevel = tank.engineLevel * 0.1f;
	float armorLevel = tank.armorLevel * -0.1f;
	std::string testTooltip;
	std::string tankVersionAndType = std::format("{0} {1}", Tank::tankVersionToString(tank.version).c_str(), Tank::tankTypeToString(tank.type).c_str());
	testTooltip = std::format("{0}: {1} Km/h\r\n", tankVersionAndType, tank.stats.speed);

	if (tank.turret.stats.speed != 0.0f) {
		std::string speedT = std::format("{:.1f} km/h", tank.turret.stats.speed);
		std::string stringT = std::format("{0} man turret: {1}\r\n", tank.turret.crew, speedT.c_str());
		testTooltip.append(stringT);
	}

	if (tank.gun.stats.speed != 0.0f) {
		std::string gunNameAndVersion = std::format("{0} {1}", Gun::typeToString(tank.gun.type), Gun::gunNameToString(tank.gun.name));
		std::string speedG = std::format("{:.1f} km/h", tank.gun.stats.speed);
		std::string stringT = std::format("{0}: {1}\r\n", gunNameAndVersion, speedG);
		testTooltip.append(stringT);
	}

	for (SpecialModule& module : tank.specialModules) {
		if (module.stats.speed != 0.0f) {
			std::string speedM = std::format("{:.1f} km/h", module.stats.speed);
			std::string stringT = std::format("{0}: {1}\r\n", module.typeToString(module.type), speedM);
			testTooltip.append(stringT);
		}
	}

	if (tank.suspension.stats.speedP != 0.0f) {
		std::string speedS = std::format("{:.1f} km/h", ((tank.stats.speed + engineLevel + armorLevel + tank.suspension.stats.speed) * tank.suspension.stats.speedP) / 100);
		std::string stringT = std::format("{0} suspension: {1}\r\n", Suspension::typeToString(tank.suspension.type), speedS.c_str());
		testTooltip.append(stringT);
	}

	if (tank.engine.stats.speedP != 0.0f) {
		float engineSpeed = ((tank.stats.speed + engineLevel + armorLevel + tank.engine.stats.speed) * tank.engine.stats.speedP) / 100;
		std::string speedE = std::format("{:.1f} km/h", engineSpeed);
		std::string stringT = std::format("{0} : {1}\r\n", Engine::typeToString(tank.engine.type), speedE.c_str());
		testTooltip.append(stringT);
	}

	if (tank.engineLevel != 0) {
		std::string speedE = std::format("{:.1f} km/h", engineLevel);
		std::string stringT = std::format("Engine Level : {0}\r\n", speedE.c_str());
		testTooltip.append(stringT);
	}

	if (tank.armorLevel != 0) {
		std::string speedE = std::format("{:.1f} km/h", armorLevel);
		std::string stringT = std::format("Armor Level : {0}\r\n", speedE.c_str());
		testTooltip.append(stringT);
	}

	ImGui::SetItemTooltip(testTooltip.c_str());
}

void renderTankReliabilityTooltip(Tank tank) {
	float engineLevel = tank.engineLevel * -1.5f;
	float armorLevel = tank.armorLevel * -1.5f;
	std::string testTooltip;
	std::string tankVersionAndType = std::format("{0} {1}", Tank::tankVersionToString(tank.version).c_str(), Tank::tankTypeToString(tank.type).c_str());
	testTooltip = std::format("{0}: {1} %%\r\n", tankVersionAndType, tank.stats.reliabilityP);

	if (tank.turret.stats.reliabilityP != 0.0f) {
		std::string stringT = std::format("{0} man turret: {1}\r\n", tank.turret.crew, tank.turret.stats.reliabilityP);
		testTooltip.append(stringT);
	}

	if (tank.gun.stats.reliabilityP != 0.0f) {
		std::string gunNameAndVersion = std::format("{0} {1}", Gun::typeToString(tank.gun.type), Gun::gunNameToString(tank.gun.name));
		std::string stringT = std::format("{0}: {1}%%\r\n", gunNameAndVersion, tank.gun.stats.reliabilityP);
		testTooltip.append(stringT);
	}

	for (SpecialModule& module : tank.specialModules) {
		if (module.stats.reliabilityP != 0.0f) {
			std::string stringT = std::format("{0}: {1}%%\r\n", module.typeToString(module.type), module.stats.reliabilityP);
			testTooltip.append(stringT);
		}
	}

	if (tank.suspension.stats.reliabilityP != 0.0f) {
		std::string stringT = std::format("{0} suspension: {1}%%\r\n", Suspension::typeToString(tank.suspension.type), tank.suspension.stats.reliabilityP);
		testTooltip.append(stringT);
	}

	if (tank.engine.stats.reliabilityP != 0.0f) {
		std::string stringT = std::format("{0} : {1}\r\n", Engine::typeToString(tank.engine.type), tank.engine.stats.reliabilityP);
		testTooltip.append(stringT);
	}

	if (tank.engineLevel != 0) {
		std::string stringT = std::format("Engine Level : {0}%%\r\n", (tank.stats.reliabilityP * engineLevel) / 100);
		testTooltip.append(stringT);
	}

	if (tank.armorLevel != 0) {
		std::string stringT = std::format("Armor Level : {0}%%\r\n", (tank.stats.reliabilityP * armorLevel) / 100);
		testTooltip.append(stringT);
	}

	ImGui::SetItemTooltip(testTooltip.c_str());
}

void renderTankSupplyUseTooltip(Tank tank) {
	//TODO: Calcultate Supply Use, No info on the Wiki
	ImGui::SetItemTooltip("calculate supply use");
}

void renderTankSoftAttackTooltip(Tank tank) {
	std::string testTooltip;

	std::string gunNameAndVersion = std::format("{0} {1}", Gun::typeToString(tank.gun.type), Gun::gunNameToString(tank.gun.name));
	std::string stringT = std::format("{0}: {1}\r\n", gunNameAndVersion, tank.gun.stats.softAttack);
	testTooltip.append(stringT);

	if (tank.turret.stats.softAttackP != 0.0f) {
		std::string stringT = std::format("{0} man turret: {1}%%\r\n", tank.turret.crew, tank.turret.stats.softAttackP);
		testTooltip.append(stringT);
	}

	for (SpecialModule& module : tank.specialModules) {
		if (module.stats.softAttack != 0.0f) {
			std::string stringT = std::format("{0}: {1}\r\n", module.typeToString(module.type), module.stats.softAttack);
			testTooltip.append(stringT);
		}
	}

	ImGui::SetItemTooltip(testTooltip.c_str());
}

void renderTankHardAttackTooltip(Tank tank) {
	std::string testTooltip;

	std::string gunNameAndVersion = std::format("{0} {1}", Gun::typeToString(tank.gun.type), Gun::gunNameToString(tank.gun.name));
	std::string stringT = std::format("{0}: {1}\r\n", gunNameAndVersion, tank.gun.stats.hardAttack);
	testTooltip.append(stringT);

	if (tank.turret.stats.hardAttackP != 0.0f) {
		std::string stringT = std::format("{0} man turret: {1}%%\r\n", tank.turret.crew, tank.turret.stats.hardAttackP);
		testTooltip.append(stringT);
	}

	for (SpecialModule& module : tank.specialModules) {
		if (module.stats.hardAttack != 0.0f) {
			std::string stringT = std::format("{0}: {1}\r\n", module.typeToString(module.type), module.stats.hardAttack);
			testTooltip.append(stringT);
		}
	}

	ImGui::SetItemTooltip(testTooltip.c_str());
}

void renderTankPiercingTooltip(Tank tank) {
	std::string testTooltip;

	std::string gunNameAndVersion = std::format("{0} {1}", Gun::typeToString(tank.gun.type), Gun::gunNameToString(tank.gun.name));
	std::string stringT = std::format("{0}: {1}\r\n", gunNameAndVersion, tank.gun.stats.piercing);
	testTooltip.append(stringT);

	for (SpecialModule& module : tank.specialModules) {
		if (module.stats.piercingP != 0.0f) {
			std::string stringT = std::format("{0}: {1}%%\r\n", module.typeToString(module.type), module.stats.piercingP);
			testTooltip.append(stringT);
		}
	}

	ImGui::SetItemTooltip(testTooltip.c_str());
}

void renderTankHardnessTooltip(Tank tank) {
	std::string testTooltip;
	std::string tankVersionAndType = std::format("{0} {1}", Tank::tankVersionToString(tank.version).c_str(), Tank::tankTypeToString(tank.type).c_str());
	testTooltip = std::format("{0}: {1}%%\r\n", tankVersionAndType, tank.stats.hardnessP);

	if (tank.suspension.stats.hardnessP != 0.0f) {
		std::string stringT = std::format("{0} suspension: {1}%%\r\n", Suspension::typeToString(tank.suspension.type), tank.suspension.stats.hardnessP);
		testTooltip.append(stringT);
	}

	if (tank.armor.stats.hardnessP != 0.0f) {
		std::string stringT = std::format("{0} armor: {1}%%\r\n", Armor::typeToString(tank.armor.type), tank.armor.stats.hardnessP);
		testTooltip.append(stringT);
	}

	ImGui::SetItemTooltip(testTooltip.c_str());
}

void renderTankArmorTooltip(Tank tank) {
	std::string testTooltip;
	float armorLevel = tank.armorLevel * 2.5f;
	std::string tankVersionAndType = std::format("{0} {1}", Tank::tankVersionToString(tank.version).c_str(), Tank::tankTypeToString(tank.type).c_str());
	testTooltip = std::format("{0}: {1}\r\n", tankVersionAndType, tank.stats.armor);

	for (SpecialModule& module : tank.specialModules) {
		if (module.stats.armor != 0.0f) {
			std::string stringT = std::format("{0}: {1}\r\n", module.typeToString(module.type), module.stats.armor);
			testTooltip.append(stringT);
		} else if (module.stats.armorP != 0.0f) {
			std::string stringT = std::format("{0}: {1}%%\r\n", module.typeToString(module.type), module.stats.armorP);
			testTooltip.append(stringT);
		}
	}

	if (tank.armor.stats.armorP != 0.0f) {
		std::string stringT = std::format("{0} armor: {1}\r\n", Armor::typeToString(tank.armor.type), ((tank.stats.armor + armorLevel) * tank.armor.stats.armorP) / 100);
		testTooltip.append(stringT);
	}

	if (armorLevel != 0.0f) {
		std::string stringT = std::format("Armor Level: {0}\r\n", armorLevel);
		testTooltip.append(stringT);
	}

	ImGui::SetItemTooltip(testTooltip.c_str());
}

void renderTankBreakthroughTooltip(Tank tank) {
	std::string testTooltip;
	float armorLevel = tank.armorLevel * 1.2f;

	if (tank.turret.stats.breakthrough != 0.0f) {
		std::string stringT = std::format("{0} man turret: {1}\r\n", tank.turret.crew, tank.turret.stats.breakthrough);
		testTooltip.append(stringT);
	} else if (tank.turret.stats.breakthroughP != 0.0f) {
		std::string stringT = std::format("{0} man turret: {1}%%\r\n", tank.turret.crew, tank.turret.stats.breakthroughP);
		testTooltip.append(stringT);
	}

	if (tank.gun.stats.breakthrough != 0.0f) {
		std::string gunNameAndVersion = std::format("{0} {1}", Gun::typeToString(tank.gun.type), Gun::gunNameToString(tank.gun.name));
		std::string stringT = std::format("{0}: {1}%%\r\n", gunNameAndVersion, tank.gun.stats.breakthrough);
		testTooltip.append(stringT);
	}

	for (SpecialModule& module : tank.specialModules) {
		if (module.stats.breakthrough != 0.0f) {
			std::string stringT = std::format("{0}: {1}\r\n", module.typeToString(module.type), module.stats.breakthrough);
			testTooltip.append(stringT);
		}
	}

	if (tank.suspension.stats.breakthrough != 0.0f) {
		std::string stringT = std::format("{0} suspension: {1}%%\r\n", Suspension::typeToString(tank.suspension.type), tank.suspension.stats.breakthrough);
		testTooltip.append(stringT);
	}

	if (tank.armor.stats.breakthrough != 0.0f) {
		std::string stringT = std::format("{0} armor: {1}\r\n", Armor::typeToString(tank.armor.type), tank.armor.stats.breakthrough);
		testTooltip.append(stringT);
	}

	if (armorLevel != 0.0f) {
		std::string stringT = std::format("Armor Level: {0}\r\n", armorLevel);
		testTooltip.append(stringT);
	}

	ImGui::SetItemTooltip(testTooltip.c_str());
}

void renderTankDefenseTooltip(Tank tank) {
	std::string testTooltip;

	if (tank.turret.stats.defense != 0.0f) {
		std::string stringT = std::format("{0} man turret: {1}\r\n", tank.turret.crew, tank.turret.stats.defense);
		testTooltip.append(stringT);
	}

	for (SpecialModule& module : tank.specialModules) {
		if (module.stats.defense != 0.0f) {
			std::string stringT = std::format("{0}: {1}\r\n", module.typeToString(module.type), module.stats.defense);
			testTooltip.append(stringT);
		} else if (module.stats.defenseP != 0.0f) {
			std::string stringT = std::format("{0}: {1}\r\n", module.typeToString(module.type), module.stats.defenseP);
			testTooltip.append(stringT);
		}
	}

	if (tank.engine.stats.defense != 0.0f) {
		std::string stringT = std::format("{0} : {1}\r\n", Engine::typeToString(tank.engine.type), tank.engine.stats.defense);
		testTooltip.append(stringT);
	}

	if (tank.armor.stats.defense != 0.0f) {
		std::string stringT = std::format("{0} armor: {1}\r\n", Armor::typeToString(tank.armor.type), tank.armor.stats.defense);
		testTooltip.append(stringT);
	}

	ImGui::SetItemTooltip(testTooltip.c_str());
}

void renderTankAirAttackTooltip(Tank tank) {
	std::string testTooltip;
	if (tank.gun.stats.airAttack != 0.0f) {
		std::string gunNameAndVersion = std::format("{0} {1}", Gun::typeToString(tank.gun.type), Gun::gunNameToString(tank.gun.name));
		std::string stringT = std::format("{0}: {1}\r\n", gunNameAndVersion, tank.gun.stats.airAttack);
		testTooltip.append(stringT);
	}
	ImGui::SetItemTooltip(testTooltip.c_str());
}

void renderTankFuelCapacityTooltip(Tank tank) {
	std::string testTooltip;
	for (SpecialModule& module : tank.specialModules) {
		if (module.stats.fuelCapacity != 0.0f) {
			std::string stringT = std::format("{0}: {1}\r\n", module.typeToString(module.type), module.stats.fuelCapacity);
			testTooltip.append(stringT);
		}
	}
	ImGui::SetItemTooltip(testTooltip.c_str());
}

void renderTankFuelUsageTooltip(Tank tank) {
	float engineLevel = tank.engineLevel * 0.05f;
	std::string testTooltip;

	if (tank.engine.stats.fuelUsage != 0.0f) {
		std::string stringT = std::format("{0} : {1}\r\n", Engine::typeToString(tank.engine.type), tank.engine.stats.fuelUsage);
		testTooltip.append(stringT);
	}

	if (engineLevel != 0.0f) {
		std::string stringT = std::format("Engine Level: {0}\r\n", engineLevel);
		testTooltip.append(stringT);
	}

	ImGui::SetItemTooltip(testTooltip.c_str());
}

void Tooltip::renderTankTooltip(Tank tank, std::string stat) {
	if (stat == "speed") {
		renderTankSpeedTooltip(tank);
	}
	else if (stat == "reliability") {
		renderTankReliabilityTooltip(tank);
	}
	else if (stat == "supplyUse") {
		renderTankSupplyUseTooltip(tank);
	}
	else if (stat == "softAttack") {
		renderTankSoftAttackTooltip(tank);
	}
	else if (stat == "hardAttack") {
		renderTankHardAttackTooltip(tank);
	}
	else if (stat == "piercing") {
		renderTankPiercingTooltip(tank);
	}
	else if (stat == "hardness") {
		renderTankHardnessTooltip(tank);
	}
	else if (stat == "armor") {
		renderTankArmorTooltip(tank);
	}
	else if (stat == "breakthrough") {
		renderTankBreakthroughTooltip(tank);
	}
	else if (stat == "defense") {
		renderTankDefenseTooltip(tank);
	}
	else if (stat == "airAttack") {
		renderTankAirAttackTooltip(tank);
	}
	else if (stat == "fuelCapacity") {
		renderTankFuelCapacityTooltip(tank);
	}
	else if (stat == "fuelUsage") {
		renderTankFuelUsageTooltip(tank);
	}
}
