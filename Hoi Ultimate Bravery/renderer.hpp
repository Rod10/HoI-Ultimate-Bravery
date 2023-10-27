#pragma once
#include "country.hpp"
#include "hull.hpp"
#include "icon.hpp"
#include "plane.hpp"
#include "planerole.hpp"
#include "settings.hpp"
#include "ship.hpp"
#include "tank.hpp"
#include "tanktype.hpp"
#include "unittype.hpp"
#include "utils.hpp"
#include "windowsmanagement.hpp"

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
#include <memory>
#include <numbers>
#include <random>
#include <sstream>
#include <string>

class Renderer
{
public:
	static void renderButtonBlock(float pos);
	static void renderSubWindow();
	static void renderShipDesignerWindow(bool windowOpen, Ship ship);
	static void renderPlaneDesignerWindow(bool windowOpen, Plane plane);
	static void renderStats(bool windowOpen, Ship ship, std::map<Hull::Type, std::string> shipIconNames, std::unordered_map<Hull::Type, Stats> newShipStats);
	static void renderStats(bool windowOpen, Plane plane, std::map<PlaneType::Type, std::string> planeIconNames, std::unordered_map<PlaneRole::Role, Stats> newPlaneStats);
};

static Country* countrySelected = &CountryList::GetInstance()->getList()->at(0);
static int columnSelected;
static UnitType::Type unitTypeSelected;
