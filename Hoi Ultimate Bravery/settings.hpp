#pragma once
#include "constant.hpp"
#include "dlc.hpp"
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
		Language language,
		std::vector<Dlc> dlc
	) :
		gamePath_(gamePath),
		language_(language),
		dlc_(dlc) {};

	static Settings* settings_;
	std::string gamePath_;
	Language language_;
	std::vector<Dlc> dlc_;

public:
	Settings(Settings& other) = delete;
	void operator=(const Settings&) = delete;
	static Settings* getInstance();
	std::string getGamepath();
	Language getLanguage();
	std::vector<Dlc> getDlc();
	bool getDlcOwned(std::string name);
};

