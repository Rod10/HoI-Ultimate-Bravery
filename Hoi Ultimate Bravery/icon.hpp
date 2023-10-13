#pragma once
#include "country.hpp"
#include "hull.hpp"
#include "plane.hpp"
#include "tank.hpp"
#include "tanktype.hpp"
#include "texture.hpp"
#include "utils.hpp"

#include <filesystem>
#include <iostream>
#include <map>
#include <string>
class Icon
{
protected:
	Icon(
		std::map<std::string, std::map<std::string, Texture>> tankIconTextures,
		std::map<std::string, std::map<std::string, Texture>> tankModulesTextures,
		std::map<std::string, std::map<std::string, Texture>> shipIconTexture,
		std::map<std::string, std::map<std::string, Texture>> shipModulesTextures,
		std::map<std::string, std::map<std::string, Texture>> planeModulesTextures,
		std::map<std::string, std::map<std::string, Texture>> planeIconTextures,
		std::map<std::string, std::map<std::string, Texture>> othersTextures) :
		tankIconTextures_(tankIconTextures),
		tankModulesTextures_(tankModulesTextures),
		shipIconTexture_(shipIconTexture),
		shipModulesTextures_(shipModulesTextures),
		planeModulesTextures_(planeModulesTextures),
		planeIconTextures_(planeIconTextures),
		othersTextures_(othersTextures) {}
	static Icon* icon_;
	std::map<std::string, std::map<std::string, Texture>> tankIconTextures_;
	std::map<std::string, std::map<std::string, Texture>> shipIconTexture_;
	std::map<std::string, std::map<std::string, Texture>> tankModulesTextures_;
	std::map<std::string, std::map<std::string, Texture>> shipModulesTextures_;
	std::map<std::string, std::map<std::string, Texture>> planeModulesTextures_;
	std::map<std::string, std::map<std::string, Texture>> planeIconTextures_;
	std::map<std::string, std::map<std::string, Texture>> othersTextures_;

public:
	Icon(Icon& other) = delete;
	void operator=(const Icon&) = delete;
	static Icon* GetInstance();
	std::map<std::string, Texture> getTankIcon(std::string type);
	std::map<std::string, Texture> getShipIcon(std::string hull);
	std::map<std::string, Texture> getPlaneIcon(std::string type);
	std::string getRandomIcon(TankType::Type type);
	std::string getShipIcon(Hull::Type type, Country* country);
	std::string getPlaneIcon(PlaneType::Type type, PlaneRole::Role role, Country* country);
	Texture getTankIconTextures(std::string type, std::string name);
	Texture getTankModulesTextures(std::string type, std::string name);
	Texture getShipIconTextures(std::string type, std::string name);
	Texture getShipModulesTextures(std::string type, std::string name);
	Texture getPlaneModulesTextures(std::string type, std::string name);
	Texture getPlaneIconTextures(std::string type, std::string name);
	Texture getOthersTextures(std::string type, std::string name);
};

