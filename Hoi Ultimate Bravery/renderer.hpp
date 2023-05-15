#pragma once
#include "icon.hpp"
#include "tank.hpp"
#include "utils.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <filesystem>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <json.hpp>
#include <locale>
#include <map>
#include <numbers>
#include <random>
#include <sstream>
#include <string>

class Renderer
{
	static void renderStats(bool windowOpen, Tank tank);
	static void setIcon(float y, float x, std::string type, std::string name);
};

