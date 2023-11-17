#pragma once
#include "constant.hpp"
#include "divisiontype.hpp"
#include "Stats.hpp"
#include "support.hpp"
#include "unit.hpp"
#include "unitsubtype.hpp"
#include "utils.hpp"

#include <format>
#include <random>
#include <string>
#include <vector>
class Division
{
public:
	Division(
		std::string name,
		std::vector<Support> support,
		std::vector<std::vector<Unit>> regimentList,
		int width) :
		name(name),
		support(support),
		regimentList(regimentList),
		width(width) {};

	std::string name;
	std::vector<Support> support;
	std::vector<std::vector<Unit>> regimentList;
	int width;

	static Division generateRandom();
};

