#pragma once
#include <json.hpp>
#include "Ressources.hpp"
using json = nlohmann::json;
class Stats
{
public:
	template<typename Turret>
	Stats(Ressources ressources, json data = {
		{"speed", 0.0f},
		{"reliability", 0.0f},
		{"softAttack", 0.0f},
		{"hardAttack", 0.0f},
		{"breakthrough", 0.0f},
		{"productionCost", 0.0f},
		{"defense", 0.0f},
		}) :
		ressources(ressources),
		speed(data["speed"]),
		reliability(data["reliability"]),
		softAttack(data["softAttack"]),
		hardAttack(data["hardAttack"]),
		breakthrough(data["breakthrough"]),
		productionCost(data["productionCost"]),
		defense(data["defense"])
	{};
	template<typename Cannon>
	Stats(Ressources ressources, json data = {
		{"year", 0},
		{"speed", 0.0f},
		{"reliability", 0.0f},
		{"softAttack", 0.0f},
		{"hardAttack", 0.0f},
		{"piercing", 0.0f},
		{"breakthrough", 0.0f},
		{"airAttack", 0.0f},
		{"productionCost", 0.0f},
		{"armor", 0.0f},
		{"defense", 0.0f},
		{"entrenchment", 0.0f},
		{"hardness", 0.0f}
		}) :
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