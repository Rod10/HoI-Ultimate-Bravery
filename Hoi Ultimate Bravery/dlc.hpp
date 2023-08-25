#pragma once
#include <string>
#include <stdio.h>
class Dlc
{
public:
	Dlc(std::string name, bool owned) :
	name(name),
	owned(owned) {}

	std::string name;
	bool owned;
};

