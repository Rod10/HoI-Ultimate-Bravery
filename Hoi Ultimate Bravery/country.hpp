#pragma once
#include "json.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using json = nlohmann::json;

class Country
{
public:
	Country(std::string name,
		std::string tag,
		int countryPosIdea,
		int linesToDeleteStart,
		int linesToDeleteEnd,
		int ideaPosIdea) :
		name(name),
		tag(tag),
		countryPosIdea(countryPosIdea),
		linesToDeleteStart(linesToDeleteStart),
		linesToDeleteEnd(linesToDeleteEnd),
		ideaPosIdea(ideaPosIdea) {
		lineToDeleteCount = linesToDeleteEnd - linesToDeleteStart;
	}
	static std::vector<Country> generateCountryList();

	std::string name;
	std::string tag;
	int countryPosIdea;
	int linesToDeleteStart;
	int linesToDeleteEnd;
	int lineToDeleteCount;
	int ideaPosIdea;
};

