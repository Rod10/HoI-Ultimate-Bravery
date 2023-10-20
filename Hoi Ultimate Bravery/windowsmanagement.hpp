#pragma once
#include "unittype.hpp"

#include <map>
#include <string>
class WindowsManagement
{
protected:
	WindowsManagement(std::map<std::string, bool> buttons, std::map<std::string, bool> subWindow, std::map<UnitType::Type, bool> typeSubWindow) :
		buttons_(buttons),
		subWindow_(subWindow),
		typeSubWindow_(typeSubWindow)
	{}
	static WindowsManagement* windowsManagement_;
	std::map<std::string, bool> buttons_;
	std::map<std::string, bool> subWindow_;
	std::map<UnitType::Type, bool> typeSubWindow_;
public:
	WindowsManagement(WindowsManagement& other) = delete;
	void operator=(const WindowsManagement&) = delete;
	static WindowsManagement* GetInstance();
	std::map<std::string, bool> getButtons();
	std::map<std::string, bool> getSubWindow();
	std::map<UnitType::Type, bool> getTypeSubWindow();

	void setButtons(std::string name, bool value);
	void setSubWindow(std::string name, bool value);
	void setTypeSubWindow(UnitType::Type, bool value);
};

