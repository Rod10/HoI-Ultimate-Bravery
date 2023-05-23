#pragma once
#include "json.hpp"
#include "language.hpp"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

class Settings
{
public:
	Settings();

	std::string getGamepath();
	std::string gamePath;
	Language language;
};

