#pragma once
#include <json.hpp>
using json = nlohmann::json;
class Ressources
{
public:
	Ressources(
		int steel = 0,
		int tungsten = 0,
		int chromium = 0) :
		steel(steel),
		tungsten(tungsten),
		chromium(chromium) {}

	Ressources(json data) :
		steel(data["steel"]),
		tungsten(data["tungsten"]),
		chromium(data["chromium"]) {}

	int steel;
	int tungsten;
	int chromium;

	Ressources& operator+=(const Ressources& rhs) {
		this->steel += rhs.steel;
		this->tungsten += rhs.tungsten;
		this->chromium += rhs.chromium;
		return *this;
	}
};

