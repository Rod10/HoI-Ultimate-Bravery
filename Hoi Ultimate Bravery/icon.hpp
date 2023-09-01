#pragma once
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
		std::map<std::string, std::map<std::string, Texture>> shipModulesTextures) :
		tankIconTextures_(tankIconTextures),
		tankModulesTextures_(tankModulesTextures),
		shipIconTexture_(shipIconTexture),
		shipModulesTextures_(shipModulesTextures){}
	static Icon* icon_;
	std::map<std::string, std::map<std::string, Texture>> tankIconTextures_;
	std::map<std::string, std::map<std::string, Texture>> shipIconTexture_;
	std::map<std::string, std::map<std::string, Texture>> tankModulesTextures_;
	std::map<std::string, std::map<std::string, Texture>> shipModulesTextures_;

public:
	Icon(Icon& other) = delete;
	void operator=(const Icon&) = delete;
	static Icon* GetInstance();
	std::map<std::string, Texture> getTankIcon(std::string type);
	std::map<std::string, Texture> getShipIcon(std::string hull);
	Texture getTankIconTextures(std::string type, std::string name);
	Texture getTankModulesTextures(std::string type, std::string name);
	Texture getShipIconTextures(std::string type, std::string name);
	Texture getShipModulesTextures(std::string type, std::string name);
};

