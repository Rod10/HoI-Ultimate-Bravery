#pragma once
#include "json.hpp"
#include "language.hpp"

#include <fstream>
#include <iostream>

using json = nlohmann::json;

class Settings
{
protected:
	Settings(
		std::string gamePath,
		Language language
	) :
		gamePath_(gamePath),
		language_(language) {};

	static Settings* settings_;
	std::string gamePath_;
	Language language_;

public:
	Settings(Settings& other) = delete;
	void operator=(const Settings&) = delete;
	static Settings* getInstance();
	std::string getGamepath();
	std::string getLanguage();
	std::string gamePath;
	Language language;
};

