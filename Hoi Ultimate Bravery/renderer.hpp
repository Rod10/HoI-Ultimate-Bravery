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
public:
	static float calculatePos(Constant::Position position, std::string text);
	static float calculatePos(Constant::Position position, int width);
	static bool createButtonWithPosition(const char* label, Constant::Position position);
	static void createLabelWithPosition(const char* label, Constant::Position position);
	static void createLabelWithPosition(const char* label, Constant::Position position, ImGuiInputTextFlags_ flag);
	static void createLabelWithPosition(const char* label, float x, float y);
	static void createTitleWithPosition(const char* label, float x, float y);
	static void renderTankDesignerWindow(bool windowOpen, Tank tank);
	static void renderStats(bool windowOpen, Tank tank, std::map<std::string, std::string> tankIconNames, std::unordered_map<TankType::Type, Stats> newTankStats);
};

