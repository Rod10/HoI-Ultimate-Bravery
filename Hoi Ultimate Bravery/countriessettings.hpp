#pragma once
#include <map>
#include <string>

class DlcSettings
{
public:
	DlcSettings(int linesToDeleteStart,
		int linesToDeleteEnd,
		int lineToDeleteCount) :
		linesToDeleteStart(linesToDeleteStart),
		linesToDeleteEnd(linesToDeleteEnd),
		lineToDeleteCount(lineToDeleteCount)
	{}

	int linesToDeleteStart;
	int linesToDeleteEnd;
	int lineToDeleteCount;
};

class CountriesSettings
{
public:
	CountriesSettings(int ideaPos, 
		std::map<std::string, DlcSettings> dlcSettings) :
		ideaPos(ideaPos),
		dlcSettings(dlcSettings) {}

	int ideaPos;
	std::map<std::string, DlcSettings> dlcSettings;
};