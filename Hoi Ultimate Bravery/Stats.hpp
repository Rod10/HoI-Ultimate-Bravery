#pragma once
#include <json.hpp>
#include "Ressources.hpp"
using json = nlohmann::json;
class Stats
{
public:
	Stats() {};
	Stats(Ressources ressources, json data) :
		ressources(ressources),
		year(data["year"]),
		speed(data["speed"]),
		reliability(data["reliability"]),
		softAttack(data["softAttack"]),
		hardAttack(data["hardAttack"]),
		piercing(data["piercing"]),
		breakthrough(data["breakthrough"]),
		airAttack(data["airAttack"]),
		productionCost(data["productionCost"]),
		armor(data["armor"]),
		defense(data["defense"]),
		entrenchment(data["entrenchment"]),
		hardness(data["hardness"])
	{};

	int year;
	float speed;
	float reliability;
	float softAttack;
	float hardAttack;
	float piercing;
	float breakthrough;
	float airAttack;
	float productionCost;
	float armor;
	float defense;
	float entrenchment;
	float hardness;
	Ressources ressources;
};