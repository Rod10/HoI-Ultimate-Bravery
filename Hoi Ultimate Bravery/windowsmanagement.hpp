#pragma once
#include "unittype.hpp"

#include <map>
#include <string>
class WindowsManagement
{
protected:
	WindowsManagement(std::map<std::string,
		bool> buttons, std::map<std::string,
		bool> subWindow, std::map<UnitType::Type,
		bool> typeSubWindow,
		UnitType::Type prevTypeSubWindow) :
		buttons_(buttons),
		subWindow_(subWindow),
		typeSubWindow_(typeSubWindow),
		prevTypeSubWindow_(prevTypeSubWindow)
	{}
	static WindowsManagement* windowsManagement_;
	std::map<std::string, bool> buttons_;
	std::map<std::string, bool> subWindow_;
	std::map<UnitType::Type, bool> typeSubWindow_;
	UnitType::Type prevTypeSubWindow_;
	int designerType_;

public:
	WindowsManagement(WindowsManagement& other) = delete;
	void operator=(const WindowsManagement&) = delete;
	static WindowsManagement* GetInstance();
	std::map<std::string, bool> getButtons();
	std::map<std::string, bool> getSubWindow();
	std::map<UnitType::Type, bool> getTypeSubWindow();
	UnitType::Type getPrevTypeSubWindow();
	int getDesignerTypeSubWindow();

	void setButtons(std::string name, bool value);
	void setSubWindow(std::string name, bool value);
	void setTypeSubWindow(UnitType::Type type, bool value);
	void setPrevTypeSubWindow(UnitType::Type type);
	void setDesignerTypeSubWindow(int type);
};

