#include "windowsmanagement.hpp"
WindowsManagement* WindowsManagement::windowsManagement_ = nullptr;;

std::map<std::string, bool> WindowsManagement::getButtons()
{
	return buttons_;
}

std::map<std::string, bool> WindowsManagement::getSubWindow()
{
	return subWindow_;
}

std::map<UnitType::Type, bool> WindowsManagement::getTypeSubWindow()
{
	return typeSubWindow_;
}

void WindowsManagement::setButtons(std::string name, bool value)
{
	buttons_.find(name)->second = value;
}

void WindowsManagement::setSubWindow(std::string name, bool value)
{
	subWindow_.find(name)->second = value;
}

void WindowsManagement::setTypeSubWindow(UnitType::Type type, bool value)
{
	typeSubWindow_.find(type)->second = value;
}

WindowsManagement* WindowsManagement::GetInstance()
{
	if (windowsManagement_ == nullptr) {
		std::map<std::string, bool> buttons {
			{"mainMenu", true},
			{"generate", false},
			{"import", false},
			{"multiplayer", false},
			{"options", false},
		};
		std::map<std::string, bool> subWindow {
			{"generate", false},
			{"import", false},
			{"multiplayer", false},
			{"options", false},
		};
		std::map<UnitType::Type, bool> typeSubWindow {
			{UnitType::Tank, true},
			{ UnitType::Plane, false },
			{ UnitType::Ship, false },
			{ UnitType::Infantry, false },
		};
		windowsManagement_ = new WindowsManagement(buttons, subWindow, typeSubWindow);
	}
	return windowsManagement_;
}