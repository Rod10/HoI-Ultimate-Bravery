#pragma once
#include "ressources.hpp"
#include "tank.hpp"

#include <array>
#include <format>
#include <iterator>
#include <iostream>
#include <string>

class Tooltip {
public: 
	static void renderTankTooltip(Tank tank, std::string stat);
};