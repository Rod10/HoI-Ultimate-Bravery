#pragma once
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

	int steel;
	int tungsten;
	int chromium;
};

