#pragma once
#include "json.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using json = nlohmann::json;

class Language
{
public:
	Language(std::string value, std::vector<std::string> name, int index) :
		value(value),
		name(name),
		index(index)
	{};
	Language() {};

	std::string value;
	std::vector<std::string> name;
	int index;

	static std::vector<Language> getLanguageList();
};

