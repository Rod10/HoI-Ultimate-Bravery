#pragma once
#include "ressources.hpp"

#include <array>
#include <iterator>
#include <iostream>
#include <json.hpp>
#include <string>

using json = nlohmann::json;
class TankStats
{
public:	
	TankStats() {};
	TankStats(Ressources ressources, json data) :
	ressources(ressources),
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
	fuelCapacityP(data["fuelCapacityP"]),
	supplyUse(data["supplyUse"]),
	supplyUseP(data["supplyUseP"])
{};
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
	  float supplyUse;
	  float supplyUseP;
	  Ressources ressources;

	  TankStats& operator+=(const TankStats& rhs) {
		  this->speed += rhs.speed;
		  this->speedP += rhs.speedP;
		  this->reliability += rhs.reliability;
		  this->reliabilityP += rhs.reliabilityP;
		  this->softAttack += rhs.softAttack;
		  this->softAttackP += rhs.softAttackP;
		  this->hardAttack += rhs.hardAttack;
		  this->hardAttackP += rhs.hardAttackP;
		  this->piercing += rhs.piercing;
		  this->piercingP += rhs.piercingP;
		  this->breakthrough += rhs.breakthrough;
		  this->breakthroughP += rhs.breakthroughP;
		  this->airAttack += rhs.airAttack;
		  this->airAttackP += rhs.airAttackP;
		  this->productionCost += rhs.productionCost;
		  this->productionCostP += rhs.productionCostP;
		  this->armor += rhs.armor;
		  this->armorP += rhs.armorP;
		  this->defense += rhs.defense;
		  this->defenseP += rhs.defenseP;
		  this->entrenchment += rhs.entrenchment;
		  this->entrenchmentP += rhs.entrenchmentP;
		  this->hardness += rhs.hardness;
		  this->hardnessP += rhs.hardnessP;
		  this->fuelUsage += rhs.fuelUsage;
		  this->fuelUsageP += rhs.fuelUsageP;
		  this->fuelCapacity += rhs.fuelCapacity;
		  this->fuelCapacityP += rhs.fuelCapacityP;
		  this->supplyUse += rhs.supplyUse;
		  this->supplyUseP += rhs.supplyUseP;
		  this->ressources += rhs.ressources;
		  return *this;
	  }

	static std::array<std::string, 30> getStatsKeyArray();
	std::string getShowStat(int row);
};