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
		std::map<std::string, std::map<std::string, Texture>> tankModulesTextures) :
		tankIconTextures_(tankIconTextures),
		tankModulesTextures_(tankModulesTextures){}
	static Icon* icon_;
	std::map<std::string, std::map<std::string, Texture>> tankIconTextures_;
	std::map<std::string, std::map<std::string, Texture>> tankModulesTextures_;

public:
	Icon(Icon& other) = delete;
	void operator=(const Icon&) = delete;
	static Icon* GetInstance();
	std::map<std::string, Texture> getTankIcon(std::string type);
	Texture getTankIconTextures(std::string type, std::string name);
	Texture getTankModulesTextures(std::string type, std::string name);
};

