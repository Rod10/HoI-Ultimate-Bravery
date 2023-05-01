#pragma once
#include <json.hpp>
#include "ressources.hpp"
#include <array>
#include <string>
#include <iterator>
#include <iostream>
using json = nlohmann::json;
class Stats
{
public:
	Stats() {};
	Stats(Ressources ressources, json data) :
		ressources(ressources),
		year(data["year"]),
		speed(data["speed"]),
		speedP(data["speedP"]),
		reliability(data["reliability"]),
		reliabilityP(data["reliabilityP"]),
		softAttack(data["softAttack"]),
		softAttackP(data["softAttackP"]),
		hardAttack(data["hardAttack"]),
		hardAttackP(data["hardAttackP"]),
		piercing(data["piercing"]),
		piercingP(data["piercingP"]),
		breakthrough(data["breakthrough"]),
		breakthroughP(data["breakthroughP"]),
		airAttack(data["airAttack"]),
		airAttackP(data["airAttackP"]),
		productionCost(data["productionCost"]),
		productionCostP(data["productionCostP"]),
		armor(data["armor"]),
		armorP(data["armorP"]),
		defense(data["defense"]),
		defenseP(data["defenseP"]),
		entrenchment(data["entrenchment"]),
		entrenchmentP(data["entrenchmentP"]),
		hardness(data["hardness"]),
		hardnessP(data["hardnessP"]),
		fuelUsage(data["fuelUsage"]),
		fuelUsageP(data["fuelUsageP"]),
		fuelCapacity(data["fuelCapacity"]),
		fuelCapacityP(data["fuelCapacityP"])
	{};

	static std::array<std::string, 29> getStatsKeyArray();

	int year;
	float speed;
	float speedP;
	float reliability;
	float reliabilityP;
	float softAttack;
	float softAttackP;
	float hardAttack;
	float hardAttackP;
	float piercing;
	float piercingP;
	float breakthrough;
	float breakthroughP;
	float airAttack;
	float airAttackP;
	float productionCost;
	float productionCostP;
	float armor;
	float armorP;
	float defense;
	float defenseP;
	float entrenchment;
	float entrenchmentP;
	float hardness;
	float hardnessP;
	float fuelUsage;
	float fuelUsageP;
	float fuelCapacity;
	float fuelCapacityP;
	Ressources ressources;
};