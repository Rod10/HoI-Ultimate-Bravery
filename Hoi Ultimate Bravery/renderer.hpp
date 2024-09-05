#pragma once
#include "country.hpp"
#include "division.hpp"
#include "files.hpp"
#include "hull.hpp"
#include "icon.hpp"
#include "imgui_stdlib.h"
#include "plane.hpp"
#include "planerole.hpp"
#include "settings.hpp"
#include "ship.hpp"
#include "tank.hpp"
#include "tanktype.hpp"
#include "texture.hpp"
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
	static ImVec2 getBlockSize();
	static ImVec2 getButtonSize();
};

static std::vector<Country>* countryList = CountryList::GetInstance()->getList();
static Country* countrySelected = &countryList->at(0);
static int columnSelected;
static UnitType::Type unitTypeSelected;
static bool allCountries;
static std::unordered_map<int, std::string> converterToGameName = Utils::loadConverter();
static std::vector<Language> languageList = Language::getLanguageList();
static Language* language;
