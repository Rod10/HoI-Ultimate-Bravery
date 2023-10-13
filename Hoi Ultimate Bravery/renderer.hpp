#pragma once
#include "icon.hpp"
#include "plane.hpp"
#include "settings.hpp"
#include "ship.hpp"
#include "tank.hpp"
#include "unittype.hpp"
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
	static float calculatePos(float position, int width);
	static float calculatePos(float position, std::string text);
	static bool createButtonWithPosition(const char* label, float position);
	static bool createButtonWithSize(const char* label, ImVec2 size);
	static bool createButtonWithPosition(const char* label, Constant::Position position);
	static void createLabelWithPosition(const char* label, Constant::Position position);
	static void createLabelWithPosition(const char* label, Constant::Position position, ImGuiInputTextFlags_ flag);
	static void createLabelWithPosition(const char* label, float x, float y);
	static void createTitleWithPosition(const char* label, float x, float y);
	static void renderButtonBlock(std::string* window, std::map<std::string, bool>* windowOpened, std::string* subWindowOpened, float pos);
	static void renderSubWindow(std::string* subWindow);
	static void renderTankDesignerWindow(bool windowOpen, Tank tank);
	static void renderShipDesignerWindow(bool windowOpen, Ship ship);
	static void renderPlaneDesignerWindow(bool windowOpen, Plane plane);
	static void renderStats(bool windowOpen, Tank tank, std::map<TankType::Type, std::string> tankIconNames, std::unordered_map<TankType::Type, Stats> newTankStats);
	static void renderStats(bool windowOpen, Ship ship, std::map<Hull::Type, std::string> shipIconNames, std::unordered_map<Hull::Type, Stats> newShipStats);
	static void renderStats(bool windowOpen, Plane plane, std::map<PlaneType::Type, std::string> planeIconNames, std::unordered_map<PlaneRole::Role, Stats> newPlaneStats);
};

