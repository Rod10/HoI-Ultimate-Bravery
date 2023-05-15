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
	Icon(std::map<std::string, std::map<std::string, Texture>> tankIconTextures) : tankIconTextures_(tankIconTextures) {}
	static Icon* icon_;
	std::map<std::string, std::map<std::string, Texture>> tankIconTextures_;

public:
	Icon(Icon& other) = delete;
	void operator=(const Icon&) = delete;
	static Icon* GetInstance();
	Texture getTankIconTextures(std::string type, std::string name);
};

