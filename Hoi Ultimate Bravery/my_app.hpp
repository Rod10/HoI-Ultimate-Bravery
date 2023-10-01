#include "app_base.hpp"

#include "armor.hpp"
#include "constant.hpp"
#include "country.hpp"
#include "engine.hpp"
#include "files.hpp"
#include "gun.hpp"
#include "language.hpp"
#include "renderer.hpp"
#include "settings.hpp"
#include "shiptype.hpp"
#include "ship.hpp"
#include "special.hpp"
#include "suspension.hpp"
#include "tank.hpp"
#include "tanktype.hpp"
#include "texture.hpp"
#include "turret.hpp"
#include "turrettype.hpp"
#include "utils.hpp"
#include "shipversion.hpp"

#include "imgui_stdlib.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <json.hpp>
#include <locale>
#include <map>
#include <numbers>
#include <random>
#include <sstream>
#include <string>

using json = nlohmann::json;

class MyApp : public AppBase
{
public:
	MyApp() {}
	~MyApp() {};

	virtual void StartUp() final
	{
		auto statsKey = Stats::getStatsKeyArray();
		languageFile = std::format("{0}.csv", settings->getLanguage().value);
		languageFilePath = std::format("Assets/Data/languages/{0}", languageFile);
		localizedStrings = Utils::loadTranslation(languageFilePath);
	}

	virtual void Update() final
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFont* basicFont = io.Fonts->Fonts[0];
		ImFont* titleFont = io.Fonts->Fonts[1];
		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
		ImGui::PushFont(titleFont);
		ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(59, 65, 57, 255));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor);
		ImGui::Begin("Main Window", &mainWindowOpen, 7 | ImGuiWindowFlags_NoInputs);
		Renderer::createLabelWithPosition("HoI Ultimate Bravery", Constant::Position::MIDDLE);
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopFont();

		float testMiddle = ImGui::GetWindowWidth() / 2.0f;

		auto off = Renderer::calculatePos(testMiddle, "generate");

		// Main Menu Block
		if (mainMenuOpen) {
			ImGui::SetNextWindowPos(ImVec2(testMiddle, 200.0f));
			ImGui::PushStyleColor(ImGuiCol_WindowBg, windowColor);
			ImGui::Begin("generate", &mainMenuOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::PopStyleColor();
			ImGui::PushFont(basicFont);
			ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
			if (Renderer::createButtonWithPosition(getLocalizedString("generate"), Constant::Position::MIDDLE)) {
				mainMenuOpen = false;
				generateWindowOpen = true;
			}
			if (Renderer::createButtonWithPosition(getLocalizedString("options"), Constant::Position::MIDDLE)) {
				mainMenuOpen = false;
				optionWindowOpen = true;
			}
			if (Renderer::createButtonWithPosition(getLocalizedString("quit"), Constant::Position::MIDDLE)) {
				//countries files
				std::string countriesPathDirectory = "./Assets/Data/Files/Back-Up/countries";
				std::string countriesTargetDirectory = std::format("{0}/history/countries", settings->getGamepath());
				//idea files
				std::string ideassPathDirectory = "./Assets/Data/Files/Back-Up/ideas";
				std::string ideasTargetDirectory = std::format("{0}/common/ideas", settings->getGamepath());

				try {
					std::filesystem::permissions(countriesPathDirectory, std::filesystem::perms::all);
					std::filesystem::permissions(countriesTargetDirectory, std::filesystem::perms::all);
					std::filesystem::permissions(ideassPathDirectory, std::filesystem::perms::all);
					std::filesystem::permissions(ideasTargetDirectory, std::filesystem::perms::all);
					const auto copyOptions = std::filesystem::copy_options::update_existing
						| std::filesystem::copy_options::recursive;
					std::filesystem::copy(countriesPathDirectory, countriesTargetDirectory, copyOptions);
					std::filesystem::copy(ideassPathDirectory, ideasTargetDirectory, copyOptions);
					exit(1);
				}
				catch (std::exception& e) // Not using fs::filesystem_error since std::bad_alloc can throw too.  
				{
					std::cout << e.what();
				}
			}
			ImGui::PopStyleColor();
			ImGui::PopFont();
			ImGui::End();
		}
		// Main Menu Block

		// Generate Menu
		if (generateWindowOpen) {
			auto off = Renderer::calculatePos(
				Constant::Position::MIDDLE,
				std::format("{0} : {1} {2} {3} {4} {5} {6}",
					getLocalizedString("ship"),
					getLocalizedString("destroyer"),
					getLocalizedString("cruiser"),
					getLocalizedString("heavyShip"),
					getLocalizedString("superHeavyShip"),
					getLocalizedString("carrier"),
					getLocalizedString("submarine")
				).c_str()
			);
			ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
			ImGui::PushStyleColor(ImGuiCol_WindowBg, windowColor);
			ImGui::Begin("generate", &generateWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::PopStyleColor();
			Renderer::createLabelWithPosition(getLocalizedString("generate"), Constant::Position::MIDDLE);

			off = Renderer::calculatePos(Constant::Position::MIDDLE, std::format("{0} :", getLocalizedString("country")));
			Renderer::createLabelWithPosition(std::format("{0} :", getLocalizedString("country")).c_str(), off, ImGui::GetCursorPosY() + 10.0f);
			ImGui::SameLine();
			static ImGuiComboFlags flags = 0;
			static int item_current_idx = 0; // Here we store our selection data as an index.
			const char* combo_preview_value = countryList[item_current_idx].name.c_str();  // Pass in the preview value visible before opening the combo (it could be anything)
			if (ImGui::BeginCombo("##", combo_preview_value, flags))
			{
				for (int n = 0; n < countryList.size(); n++)
				{
					const bool is_selected = (item_current_idx == n);
					if (ImGui::Selectable(countryList[n].name.c_str(), is_selected)) {
						item_current_idx = n;
						country = &countryList[n];
					}

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			off = Renderer::calculatePos(Constant::Position::MIDDLE, getLocalizedString("allCountries"));
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
			ImGui::Checkbox(getLocalizedString("allCountries"), &allCountries);
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);

			if (mtg) {
				renderShipGenerate();
			}

			if (nsb) {
				renderTankGenerate();
			}

			if (bba) {
				renderPlaneGenerate();
			}

			if (Renderer::createButtonWithPosition("Import Into Game", Constant::Position::MIDDLE)) {
				if (allCountries) {
					for (Country country : countryList) {
						Files::generateCountryFile(&country, converterToGameName, debugMode);
					}
				}
				else {
					Files::generateCountryFile(country, converterToGameName, debugMode);
				}
			}
			if (Renderer::createButtonWithPosition("Back", Constant::Position::MIDDLE)) {
				mainMenuOpen = true;
				generateWindowOpen = false;
			}
			ImGui::End();

			ImGui::SetNextWindowPos(ImVec2(Constant::Position::LEFT + 250.0f, 200.0f));
			ImGui::Begin("tankDesigned", &generateWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
			Renderer::createLabelWithPosition(getLocalizedString("tank"), Constant::Position::MIDDLE);
			if (!country->tankList.empty()) {
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("light"));
				bool light = country->tankList.count(TankType::Light);
				ImGui::Checkbox(getLocalizedString("light"), &light);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("medium"));
				bool medium = country->tankList.count(TankType::Medium);
				ImGui::Checkbox(getLocalizedString("medium"), &medium);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("heavy"));
				bool heavy = country->tankList.count(TankType::Heavy);
				ImGui::Checkbox(getLocalizedString("heavy"), &heavy);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("superHeavy"));
				bool superHeavy = country->tankList.count(TankType::SuperHeavy);
				ImGui::Checkbox(getLocalizedString("superHeavy"), &superHeavy);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("modern"));
				bool modern = country->tankList.count(TankType::Modern);
				ImGui::Checkbox(getLocalizedString("modern"), &modern);
			}
			ImGui::End();

			ImGui::SetNextWindowPos(ImVec2(Constant::Position::MIDDLE + 500.0f, 500.0f));
			ImGui::Begin("shipDesigned", &generateWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
			Renderer::createLabelWithPosition(getLocalizedString("ship"), Constant::Position::MIDDLE);
			if (!country->shipList.empty()) {
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("destroyer"));
				bool destroyer = country->shipList.count(Hull::Destroyer);
				ImGui::Checkbox(getLocalizedString("destroyer"), &destroyer);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("cruiser"));
				bool cruiser = country->shipList.count(Hull::Cruiser);
				ImGui::Checkbox(getLocalizedString("cruiser"), &cruiser);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("heavyShip"));
				bool heavyShip = country->shipList.count(Hull::HeavyShip);
				ImGui::Checkbox(getLocalizedString("heavy"), &heavyShip);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("carrier"));
				bool carrier = country->shipList.count(Hull::Carrier);
				ImGui::Checkbox(getLocalizedString("superHeavy"), &carrier);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("submarine"));
				bool submarine = country->shipList.count(Hull::Submarine);
				ImGui::Checkbox(getLocalizedString("modern"), &submarine);
			}
			ImGui::End();

			ImGui::SetNextWindowPos(ImVec2(Constant::Position::RIGHT + 250.0f, 200.0f));
			ImGui::Begin("planeDesigned", &generateWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
			Renderer::createLabelWithPosition(getLocalizedString("plane"), Constant::Position::MIDDLE);
			if (!country->planeList.empty()) {
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("fighter"));
				bool destroyer = country->planeList.count(PlaneRole::Fighter);
				ImGui::Checkbox(getLocalizedString("fighter"), &destroyer);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("cas"));
				bool cruiser = country->planeList.count(PlaneRole::CAS);
				ImGui::Checkbox(getLocalizedString("cas"), &cruiser);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("navalBomber"));
				bool heavyShip = country->planeList.count(PlaneRole::NavalBombing);
				ImGui::Checkbox(getLocalizedString("navalBomber"), &heavyShip);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("tacticalBomber"));
				bool carrier = country->planeList.count(PlaneRole::TacticalBombing);
				ImGui::Checkbox(getLocalizedString("tacticalBomber"), &carrier);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("strategicBomber"));
				bool submarine = country->planeList.count(PlaneRole::StrategicBombing);
				ImGui::Checkbox(getLocalizedString("strategicBomber"), &submarine);
			}
			ImGui::End();

		}
		// Generate Menu

		//By Type
		if (designerWindowOpen) {
			Renderer::renderTankDesignerWindow(designerWindowOpen, country->tankList.find(tankTypeToShow)->second);
			Renderer::renderStats(designerWindowOpen, country->tankList.find(tankTypeToShow)->second, tankIconNames, country->newTankStats);

			ImGui::SetCursorPosY(515.0f);
			ImGuiStyle& style = ImGui::GetStyle();
			float width = 0.0f;
			width += ImGui::CalcTextSize("Regenerate").x;
			width += style.ItemSpacing.x;
			width += ImGui::CalcTextSize("Back").x;
			width += style.ItemSpacing.x;
			AlignForWidth(width);
			if (ImGui::Button("Regenerate")) {
				country->tankList.find(tankTypeToShow)->second = Tank::generateRandomTank(tankTypeToShow);
				country->newTankStats.find(tankTypeToShow)->second = generateNewStats(country->tankList.find(tankTypeToShow)->second);

				std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(tankTypeToShow));
				auto it = icon.cbegin();
				int random = rand() % icon.size();
				std::advance(it, random);

				tankIconNames[tankTypeToShow] = it->first;
			}
			ImGui::SameLine();
			if (ImGui::Button("Back")) {
				generateWindowOpen = true;
				designerWindowOpen = false;
			}

			ImGui::PopStyleColor();
			ImGui::PopFont();
			ImGui::End();
		}
		//By Type

		//All Tank Type
		if (allGenerationWindowOpen) {
			ImGui::Begin("generateAll", &allGenerationWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
			int posMult = 250;
			for (auto& [type, tank] : country->tankList) {
				ImGui::SetNextWindowPos(ImVec2(posMult, 200.0f));
				ImGui::Begin(Tank::tankTypeToString(tank.type).c_str(), &allGenerationWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
				Renderer::createLabelWithPosition(Tank::tankTypeToString(tank.type).c_str(), Constant::Position::MIDDLE);
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
				ImGuiIO& io = ImGui::GetIO();
				Renderer::createLabelWithPosition(std::format("{0} {1}", Gun::gunNameToString(tank.gun.name), Gun::typeToString(tank.gun.type)).c_str(), Constant::Position::LEFT);
				Renderer::createLabelWithPosition(std::format("{0} {1}", TurretType::turretTypeToString(tank.turret.type), tank.turret.crew).c_str(), Constant::Position::LEFT);
				Renderer::createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[0].type).c_str(), Constant::Position::LEFT);
				Renderer::createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[1].type).c_str(), Constant::Position::LEFT);
				Renderer::createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[2].type).c_str(), Constant::Position::LEFT);
				Renderer::createLabelWithPosition(SpecialModule::typeToString(tank.specialModules[3].type).c_str(), Constant::Position::LEFT);
				Renderer::createLabelWithPosition(Suspension::typeToString(tank.suspension.type).c_str(), Constant::Position::LEFT);
				Renderer::createLabelWithPosition(Armor::typeToString(tank.armor.type).c_str(), Constant::Position::LEFT);
				Renderer::createLabelWithPosition(Engine::typeToString(tank.engine.type).c_str(), Constant::Position::LEFT);
				Renderer::createLabelWithPosition(std::format("Armor: {0}", tank.armorLevel).c_str(), Constant::Position::LEFT);
				Renderer::createLabelWithPosition(std::format("Engine: {0}", tank.engineLevel).c_str(), Constant::Position::LEFT);
				posMult += 250;
				ImGui::PopStyleColor();
				ImGui::End();
			}
			ImGui::SetCursorPosY(515.0f);
			ImGuiStyle& style = ImGui::GetStyle();
			ImGui::PushFont(basicFont);
			float width = 0.0f;
			width += ImGui::CalcTextSize("Regenerate").x;
			width += style.ItemSpacing.x;
			width += ImGui::CalcTextSize("Back").x;
			width += style.ItemSpacing.x;
			AlignForWidth(width);			if (ImGui::Button("Regenerate")) {
				std::vector<TankType::Type> tankType;
				for (int i = 0; i < TankType::Type::Last; i++) {
					tankType.push_back(static_cast<TankType::Type>(i));
				}
				if (allCountries) {
					for (Country& country : countryList) {
						for (TankType::Type& type : tankType) {
							Tank tank = Tank::generateRandomTank(type);
							country.tankList.find(type)->second = tank;
							country.newTankStats.find(type)->second = generateNewStats(tank);
						}
					}
				}
				else {
					for (TankType::Type& type : tankType) {
						Tank tank = Tank::generateRandomTank(type);
						country->tankList.find(type)->second = tank;
						country->newTankStats.find(type)->second = generateNewStats(tank);
					}
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Back")) {
				generateWindowOpen = true;
				allGenerationWindowOpen = false;
			}
			ImGui::PopFont();
			ImGui::End();
		}
		//All Tank Type

		if (designerShipWindowOpen) {
			ImGui::PushFont(basicFont);
			Renderer::renderShipDesignerWindow(designerWindowOpen, country->shipList.find(hullTypeToShow)->second);
			Renderer::renderStats(designerWindowOpen, country->shipList.find(hullTypeToShow)->second, shipIconNames, country->newShipStats);
			ImGui::SetCursorPosY(515.0f);
			ImGuiStyle& style = ImGui::GetStyle();
			float width = 0.0f;
			width += ImGui::CalcTextSize("Regenerate S").x;
			width += style.ItemSpacing.x;
			width += ImGui::CalcTextSize("Back").x;
			width += style.ItemSpacing.x;
			AlignForWidth(width);
			if (ImGui::Button("Regenerate S")) {
				country->shipList.find(hullTypeToShow)->second = Ship::generateRandomShip(hullTypeToShow);
			}
			ImGui::SameLine();
			if (ImGui::Button("Back")) {
				generateWindowOpen = true;
				designerShipWindowOpen = false;
			}
			ImGui::PopFont();
			ImGui::End();
		}

		if (allGenerationShipWindowOpen) {
			ImGui::Begin("generateAll", &allGenerationShipWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
			int posMult = 250;
			for (auto& [type, ship] : country->shipList) {
				ImGui::SetNextWindowPos(ImVec2(posMult, 200.0f));
				ImGui::Begin(ShipType::shipTypeToString(ship.type).c_str(), &allGenerationWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
				Renderer::createLabelWithPosition(std::format("{0} {1}", ShipVersion::versionToYear(ship.version).c_str(), ShipType::shipTypeToString(ship.type).c_str()).c_str(), Constant::Position::MIDDLE);
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
				ImGuiIO& io = ImGui::GetIO();
				for (auto& module : ship.customModule) {
					if (module.type != Module::Type::None) {
						Renderer::createLabelWithPosition(std::format("{0} {1}", Module::moduleTypeToStringFile(module.type), Module::versionToString(module.version)).c_str(), Constant::Position::LEFT);
					}
				}
				for (auto& module : ship.fixedModule) {
					if (module.type != Module::Type::None) {
						Renderer::createLabelWithPosition(std::format("{0} {1}", Module::moduleTypeToStringFile(module.type), Module::versionToString(module.version)).c_str(), Constant::Position::LEFT);
					}
				}
				posMult += 250;
				ImGui::PopStyleColor();
				ImGui::End();
			}
			ImGui::SetCursorPosY(515.0f);
			ImGuiStyle& style = ImGui::GetStyle();
			ImGui::PushFont(basicFont);
			float width = 0.0f;
			width += ImGui::CalcTextSize("Regenerate").x;
			width += style.ItemSpacing.x;
			width += ImGui::CalcTextSize("Back").x;
			width += style.ItemSpacing.x;
			AlignForWidth(width);			
			if (ImGui::Button("Regenerate S")) {
				std::vector<Hull::Type> hullType;
				for (int i = 0; i < Hull::Type::Last; i++) {
					hullType.push_back(static_cast<Hull::Type>(i));
				}
				if (allCountries) {
					for (Country& country : countryList) {
						for (Hull::Type& hull : hullType) {
							if (hull != Hull::Type::SuperHeavyShip) {
								Ship ship = Ship::generateRandomShip(hull);
								country.shipList.find(hull)->second = ship;
								country.newShipStats.find(hull)->second = Stats();
							}
						}
					}
				}
				else {
					for (Hull::Type& hull : hullType) {
						if (hull != Hull::Type::SuperHeavyShip) {
							Ship ship = Ship::generateRandomShip(hull);
							country->shipList.find(hull)->second = ship;
							country->newShipStats.find(hull)->second = Stats();
						}
					}
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Back")) {
				generateWindowOpen = true;
				allGenerationShipWindowOpen = false;
			}
			ImGui::PopFont();
			ImGui::End();
		}

		if (designerPlaneWindowOpen) {
			ImGui::PushFont(basicFont);
			Renderer::renderPlaneDesignerWindow(designerWindowOpen, country->planeList.find(planeRoleToShow)->second);
			Renderer::renderStats(designerWindowOpen, country->planeList.find(planeRoleToShow)->second, planeIconNames, country->newPlaneStats);
			ImGui::SetCursorPosY(515.0f);
			ImGuiStyle& style = ImGui::GetStyle();
			float width = 0.0f;
			width += ImGui::CalcTextSize("Regenerate").x;
			width += style.ItemSpacing.x;
			width += ImGui::CalcTextSize("Back").x;
			width += style.ItemSpacing.x;
			AlignForWidth(width);
			if (ImGui::Button("Regenerate P")) {
				Plane newPlane = Plane::generateRandomPlane(planeRoleToShow);
				country->planeList.find(planeRoleToShow)->second = newPlane;
				country->newPlaneStats.insert(std::pair<PlaneRole::Role, Stats>(planeRoleToShow, Stats()));

				std::map<std::string, Texture> icon = Icon::GetInstance()->getPlaneIcon(PlaneType::typeToString(newPlane.type));
				planeIconNames.insert(std::pair<PlaneType::Type, std::string>(newPlane.type, Icon::GetInstance()->getPlaneIcon(newPlane.type, planeRoleToShow, country)));
			}
			ImGui::SameLine();
			if (ImGui::Button("Back")) {
				generateWindowOpen = true;
				designerPlaneWindowOpen = false;
			}
			ImGui::PopFont();
			ImGui::End();
		}

		if (allGenerationPlaneWindowOpen) {
			ImGui::Begin("generateAll", &allGenerationShipWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
			int posMult = 250;
			for (auto& [type, plane] : country->planeList) {
				ImGui::SetNextWindowPos(ImVec2(posMult, 200.0f));
				ImGui::Begin(PlaneRole::roleToString(plane.role).c_str(), &allGenerationWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
				Renderer::createLabelWithPosition(std::format("{0} {1}", PlaneVersion::versionToYear(plane.version).c_str(), PlaneRole::roleToString(plane.role).c_str()).c_str(), Constant::Position::MIDDLE);
				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
				ImGuiIO& io = ImGui::GetIO();
				for (auto& module : plane.custom) {
					if (module.type != PlaneModule::Type::None) {
						Renderer::createLabelWithPosition(std::format("{0} {1}", PlaneModule::subTypeToString(module.subType), PlaneModule::versionToString(module.version)).c_str(), Constant::Position::LEFT);
					}
				}
				posMult += 250;
				ImGui::PopStyleColor();
				ImGui::End();
			}
			ImGui::SetCursorPosY(515.0f);
			ImGuiStyle& style = ImGui::GetStyle();
			ImGui::PushFont(basicFont);
			float width = 0.0f;
			width += ImGui::CalcTextSize("Regenerate").x;
			width += style.ItemSpacing.x;
			width += ImGui::CalcTextSize("Back").x;
			width += style.ItemSpacing.x;
			AlignForWidth(width);
			if (ImGui::Button("Regenerate P")) {
				std::vector<PlaneRole::Role> roleList;
				for (int i = 0; i < PlaneRole::Role::Last; i++) {
					roleList.push_back(static_cast<PlaneRole::Role>(i));
				}
				if (allCountries) {
					for (Country& country : countryList) {
						for (PlaneRole::Role& role : roleList) {
							Plane plane = Plane::generateRandomPlane(role);
							country.planeList.find(role)->second = plane;
							country.newPlaneStats.find(role)->second = Stats();
						}
					}
				}
				else {
					for (PlaneRole::Role& role : roleList) {
						Plane plane = Plane::generateRandomPlane(role);
						country->planeList.find(role)->second = plane;
						country->newPlaneStats.find(role)->second = Stats();
					}
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Back")) {
				generateWindowOpen = true;
				allGenerationPlaneWindowOpen = false;
			}
			ImGui::PopFont();
			ImGui::End();
		}

		// Options
		if (optionWindowOpen) {
			off = Renderer::calculatePos(Constant::Position::MIDDLE, 250);
			ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
			ImGui::Begin("options", &optionWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
			Renderer::createLabelWithPosition("Options", Constant::Position::MIDDLE);

			ImGui::Text("Game Path: ");
			ImGuiStyle& style = ImGui::GetStyle();
			float width = 0.0f;
			width += ImGui::CalcTextSize("Game Path: ").x;
			width += style.ItemSpacing.x;
			width += ImGui::CalcTextSize(settings->getGamepath().data()).x;
			width += style.ItemSpacing.x;
			AlignForWidth(width);
			ImGui::SameLine();
			std::string gamePathT = settings->getGamepath();
			std::string* gamePath = &gamePathT;
			ImGui::InputText("##", gamePath);

			ImGui::Text("Language: ");
			ImGui::SameLine();
			static ImGuiComboFlags flags = 0;
			static int languageIndex = settings->getLanguage().index;
			static int nameIndex = 0;// Here we store our selection data as an index.
			const char* combo_preview_value = languageList[languageIndex].name[nameIndex].c_str();  // Pass in the preview value visible before opening the combo (it could be anything)
			if (ImGui::BeginCombo("###", combo_preview_value, flags))
			{
				for (int n = 0; n < languageList[languageIndex].name.size(); n++)
				{
					const bool is_selected = (nameIndex == n);
					if (ImGui::Selectable(languageList[languageIndex].name[n].c_str(), is_selected)) {
						nameIndex = n;
						language = &languageList[n];
					}

					// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			if (Renderer::createButtonWithPosition(getLocalizedString("setDlc"), Constant::Position::MIDDLE)) {
				dlcWindowOpen = true;
			}
			if (Renderer::createButtonWithPosition(getLocalizedString("setMod"), Constant::Position::MIDDLE)) {
				modWindowOpen = true;
			}
			if (dlcWindowOpen) {
				ImGui::SetNextWindowPos(ImVec2(Constant::Position::MIDDLE, 200.0f));
				ImGui::Begin("dlc", &dlcWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
				Renderer::createLabelWithPosition("DLC", Constant::Position::MIDDLE);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("mtg"));
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
				ImGui::Checkbox(getLocalizedString("mtg"), &mtg);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("nsb"));
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
				ImGui::Checkbox(getLocalizedString("nsb"), &nsb);
				off = Renderer::calculatePos(Constant::Position::LEFT, getLocalizedString("bba"));
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
				ImGui::Checkbox(getLocalizedString("bba"), &bba);
				if (Renderer::createButtonWithPosition(getLocalizedString("back"), Constant::Position::MIDDLE)) {
					dlcWindowOpen = false;
				}
				ImGui::End();
			}
			if (modWindowOpen) {
				ImGui::SetNextWindowPos(ImVec2(Constant::Position::MIDDLE, 200.0f));
				ImGui::Begin("mod", &modWindowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
				if (Renderer::createButtonWithPosition(getLocalizedString("back"), Constant::Position::MIDDLE)) {
					modWindowOpen = false;
				}
				ImGui::End();
			}

			width = 0.0f;
			width += ImGui::CalcTextSize("Save").x;
			width += style.ItemSpacing.x;
			width += ImGui::CalcTextSize("Back").x;
			width += style.ItemSpacing.x;
			AlignForWidth(width);

			if (ImGui::Button("Save")) {
				json settingsFile;
				settingsFile["gamePath"] = *gamePath;
				settingsFile["language"] = language->value;
				std::vector<std::string> dlc = {};
				if (mtg) {
					dlc.push_back("mtg");
				}
				if (nsb) {
					dlc.push_back("nsb");
				}
				if (bba) {
					dlc.push_back("bba");
				}
				settingsFile["dlc"] = dlc;
				std::ofstream file("Assets/Data/Settings.json");
				languageFile = std::format("{0}.csv", language->value);
				languageFilePath = std::format("Assets/Data/languages/{0}", languageFile);
				localizedStrings = Utils::loadTranslation(languageFilePath);
				file << settingsFile;
			}
			ImGui::SameLine();
			if (ImGui::Button("Back")) {
				mainMenuOpen = true;
				optionWindowOpen = false;
			}
			ImGui::End();
		}
		// Options

		ImGui::End();
	}

private:
	bool debugMode = true;
	Hull::Type hullTypeToShow;
	TankType::Type tankTypeToShow;
	PlaneRole::Role planeRoleToShow;
	std::map<TankType::Type, Tank> tankList;
	std::unordered_map<TankType::Type, Stats> newTankStats;
	std::vector<std::string> tankModule = { "gun", "turret", "suspension", "engine", "armor" };
	std::vector<Country> countryList = Country::generateCountryList();
	Country* country = &countryList[0];
	std::vector<Language> languageList = Language::getLanguageList();
	Language* language;
	Settings* settings = Settings::getInstance();

	bool mainWindowOpen = true;
	bool mainMenuOpen = true;
	bool generateWindowOpen = false;
	bool optionWindowOpen = false;
	bool designerWindowOpen = false;
	bool allGenerationWindowOpen = false;
	bool allGenerationShipWindowOpen = false;
	bool allGenerationPlaneWindowOpen = false;
	bool allCountries = false;
	bool dlcWindowOpen = false;
	bool modWindowOpen = false;
	bool designerShipWindowOpen = false;
	bool designerPlaneWindowOpen = false;

	bool mtg = settings->getDlcOwned("mtg");
	bool nsb = settings->getDlcOwned("nsb");
	bool bba = settings->getDlcOwned("bba");

	std::map<TankType::Type, std::string> tankIconNames;
	std::map<Hull::Type, std::string> shipIconNames;
	std::map<PlaneType::Type, std::string> planeIconNames;

	std::map<Gun::Category, std::vector<Gun>> gunList = Gun::generateGunList();
	std::map<Gun::Name, bool> gunNameWindowOpen;

	std::string languageFile;
	std::string languageFilePath;
	std::unordered_map<int, std::string> localizedStrings;
	std::unordered_map<int, std::string> converterToGameName = Utils::loadConverter();

	ImVec4 backgroundColor = ImVec4(0.831f, 0.902f, 0.945f, 1.00f);
	ImVec4 windowColor = ImVec4(0.149f, 0.137f, 0.125f, 1.00f);
	ImVec4 buttonColor = ImVec4(0.231f, 0.255f, 0.224f, 1.00f);

	const char* getLocalizedString(std::string text) {
		int id = Utils::hash(text.c_str());
		return localizedStrings[id].c_str();
	}

	void AlignForWidth(float width, float alignment = 0.5f) {
		ImGuiStyle& style = ImGui::GetStyle();
		float avail = ImGui::GetContentRegionAvail().x;
		float off = (avail - width) * alignment;
		if (off > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
	}

	void renderShipGenerate() {
		Renderer::createLabelWithPosition(std::format("{0} :", getLocalizedString("ship")).c_str(), Constant::Position::LEFT);
		ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
		ImGuiStyle& style = ImGui::GetStyle();

		float width = 0.0f;
		width += ImGui::CalcTextSize(std::format("{0}: ", getLocalizedString("ship")).c_str()).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("destroyer")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("cruiser")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("heavyShip")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("superHeavyShip")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("carrier")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("submarine")).x;
		AlignForWidth(width);
		ImGui::SameLine();

		if (ImGui::Button(getLocalizedString("destroyer"))) {
			hullTypeToShow = Hull::Destroyer;
			generatingShip();
		}
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("cruiser"))) {
			hullTypeToShow = Hull::Cruiser;
			generatingShip();
		}
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("heavyShip"))) {
			hullTypeToShow = Hull::HeavyShip;
			generatingShip();
		}
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("carrier"))) {
			hullTypeToShow = Hull::Carrier;
			generatingShip();
		}
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("submarine"))) {
			hullTypeToShow = Hull::Submarine;
			generatingShip();
		}
		if (Renderer::createButtonWithPosition(getLocalizedString("allShip"), Constant::Position::MIDDLE)) {
			std::vector<Hull::Type> hullType;
			for (int i = 0; i < Hull::Type::Last; i++) {
				hullType.push_back(static_cast<Hull::Type>(i));
			}
			for (Hull::Type& type : hullType) {
				if (type != Hull::Type::SuperHeavyShip) {
					country->shipList.insert(std::pair<Hull::Type, Ship>(type, Ship::generateRandomShip(type)));
					country->newShipStats.insert(std::pair<Hull::Type, Stats>(type, Stats()));
					std::map<std::string, Texture> icon = Icon::GetInstance()->getShipIcon(Hull::typeToString(type));
					shipIconNames.insert(std::pair<Hull::Type, std::string>(type, Icon::GetInstance()->getShipIcon(type, country)));
				}
			}
			allGenerationShipWindowOpen = true;
			generateWindowOpen = false;
		}

		ImGui::PopStyleColor();
	}

	void generatingShip() {
		if (allCountries) {
			for (Country& country : countryList) {
				Ship ship = Ship::generateRandomShip(hullTypeToShow);
				country.shipList.insert(std::pair<Hull::Type, Ship>(hullTypeToShow, ship));
				country.newShipStats.insert(std::pair<Hull::Type, Stats>(hullTypeToShow, Stats()));
			}
		}
		else {
			Ship ship = Ship::generateRandomShip(hullTypeToShow);
			country->shipList.insert(std::pair<Hull::Type, Ship>(hullTypeToShow, ship));
			country->newShipStats.insert(std::pair<Hull::Type, Stats>(hullTypeToShow, Stats()));
		}
		std::map<std::string, Texture> icon = Icon::GetInstance()->getShipIcon(Hull::typeToString(hullTypeToShow));
		shipIconNames.insert(std::pair<Hull::Type, std::string>(hullTypeToShow, Icon::GetInstance()->getShipIcon(hullTypeToShow, country)));
		designerShipWindowOpen = true;
		generateWindowOpen = false;
	}

	void renderTankGenerate() {
		Renderer::createLabelWithPosition(std::format("{0} :", getLocalizedString("tank")).c_str(), Constant::Position::LEFT);
		ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
		ImGuiStyle& style = ImGui::GetStyle();
		float width = 0.0f;
		width += ImGui::CalcTextSize(std::format("{0}: ", getLocalizedString("tank")).c_str()).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("light")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("medium")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("heavy")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("superHeavy")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("modern")).x;
		AlignForWidth(width);
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("light"))) {
			tankTypeToShow = TankType::Type::Light;
			generatingTank();
		}
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("medium"))) {
			tankTypeToShow = TankType::Type::Medium;
			generatingTank();
		}
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("heavy"))) {
			tankTypeToShow = TankType::Type::Heavy;
			generatingTank();
		}
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("superHeavy"))) {
			tankTypeToShow = TankType::Type::SuperHeavy;
			generatingTank();
		}
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("modern"))) {
			tankTypeToShow = TankType::Type::Modern;
			generatingTank();
		}

		if (Renderer::createButtonWithPosition(getLocalizedString("allTank"), Constant::Position::MIDDLE)) {
			std::vector<TankType::Type> tankType;
			for (int i = 0; i < TankType::Type::Last; i++) {
				tankType.push_back(static_cast<TankType::Type>(i));
			}
			if (allCountries) {
				for (Country& country : countryList) {
					for (TankType::Type& type : tankType) {
						Tank tank = Tank::generateRandomTank(type);
						country.tankList.insert(std::pair<TankType::Type, Tank>(type, tank));
						country.newTankStats.insert(std::pair<TankType::Type, Stats>(type, generateNewStats(tank)));
						tankIconNames.insert(std::pair<TankType::Type, std::string>(type, Icon::GetInstance()->getRandomIcon(type)));
					}
				}
			}
			else {
				for (TankType::Type& type : tankType) {
					Tank tank = Tank::generateRandomTank(type);
					country->tankList.insert(std::pair<TankType::Type, Tank>(type, tank));
					country->newTankStats.insert(std::pair<TankType::Type, Stats>(type, generateNewStats(tank)));
					tankIconNames.insert(std::pair<TankType::Type, std::string>(type, Icon::GetInstance()->getRandomIcon(type)));
				}
			}

			allGenerationWindowOpen = true;
			generateWindowOpen = false;

		}
		ImGui::PopStyleColor();
	}

	void generatingTank() {
		if (allCountries) {
			for (Country& country : countryList) {
				Tank tank = Tank::generateRandomTank(tankTypeToShow);

				country.tankList.insert(std::pair<TankType::Type, Tank>(tankTypeToShow, tank));
				country.newTankStats.insert(std::pair<TankType::Type, Stats>(tankTypeToShow, generateNewStats(tank)));
			}
		}
		else {
			Tank tank = Tank::generateRandomTank(tankTypeToShow);

			country->tankList.insert(std::pair<TankType::Type, Tank>(tankTypeToShow, tank));
			country->newTankStats.insert(std::pair<TankType::Type, Stats>(tankTypeToShow, generateNewStats(tank)));
		}

		std::map<std::string, Texture> icon = Icon::GetInstance()->getTankIcon(Tank::tankTypeToString(tankTypeToShow));
		tankIconNames.insert(std::pair<TankType::Type, std::string>(tankTypeToShow, Icon::GetInstance()->getRandomIcon(tankTypeToShow)));

		designerWindowOpen = true;
		generateWindowOpen = false;
	}

	Stats generateNewStats(Tank tank) {
		Stats stats;
		Stats newStats = tank.stats;

		for (auto& module : tankModule) {
			stats = getStats(tank, module);
			newStats += stats;
		}

		//Add Stats of special modules
		for (const SpecialModule& module : tank.specialModules) {
			newStats += module.stats;
		}
		//Add Stats of special modules

		// Base Stats
		float totalSpeedP = newStats.speedP + ((tank.engineLevel * 10) + (tank.armorLevel * -5.0));
		float reliabilityP = newStats.reliabilityP + ((tank.engineLevel * -1.5) + (tank.armorLevel * 1.5));
		float speedf = newStats.speed + (newStats.speed * (totalSpeedP / 100));
		newStats.speed = speedf;

		float reliabilityf = newStats.reliability + reliabilityP;
		newStats.reliability = reliabilityf;
		//Base Stats

		//Combat Stats
		float softAttackF = newStats.softAttack + (newStats.softAttack * (newStats.softAttackP / 100));
		newStats.softAttack = softAttackF;

		float hardAttackF = newStats.hardAttack + (newStats.hardAttack * (newStats.hardAttackP / 100));
		newStats.hardAttack = hardAttackF;

		float piercingF = newStats.piercing + (newStats.piercing * (newStats.piercingP / 100));
		newStats.piercing = piercingF;

		float hardnessF = newStats.hardness + (newStats.hardness * (newStats.hardnessP / 100));
		newStats.hardness = hardnessF;

		float totalArmorP = newStats.armorP + (tank.armorLevel * 8.5);
		float armorF = newStats.armor + (newStats.armor * (totalArmorP / 100));
		newStats.armor = armorF;

		float totalBreakthroughF = newStats.breakthrough + tank.armorLevel * 1.2;
		float breakthroughF = totalBreakthroughF + (totalBreakthroughF * (newStats.breakthroughP / 100));
		newStats.breakthrough = breakthroughF;

		float defenseF = newStats.defense + (newStats.defense * (newStats.defenseP / 100));
		newStats.defense = defenseF;

		float airAttackF = newStats.airAttack + (newStats.airAttack * (newStats.airAttackP / 100));
		newStats.airAttack = airAttackF;
		//Combat Stats
		return newStats;
	}

	Stats getStats(Tank tank, std::string module) {
		switch (tank.tankModuleToInt(module)) {
		case 0: return Stats(tank.gun.stats);
		case 1: return Stats(tank.turret.stats);
		case 2: return Stats(tank.suspension.stats);
		case 3: return Stats(tank.armor.stats);
		case 4: return Stats(tank.engine.stats);
		}
	}

	void renderPlaneGenerate() {
		Renderer::createLabelWithPosition(std::format("{0} :", getLocalizedString("plane")).c_str(), Constant::Position::LEFT);
		ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
		ImGuiStyle& style = ImGui::GetStyle();

		float width = 0.0f;
		width += ImGui::CalcTextSize(std::format("{0}: ", getLocalizedString("plane")).c_str()).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("fighter")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("cas")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("navalBomber")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("tacticalBomber")).x;
		width += style.ItemSpacing.x;
		width += ImGui::CalcTextSize(getLocalizedString("strategicBomber")).x;
		width += style.ItemSpacing.x;
		AlignForWidth(width);
		ImGui::SameLine();

		if (ImGui::Button(getLocalizedString("fighter"))) {
			planeRoleToShow = PlaneRole::Role::Fighter;
			generatingPlane();
		}
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("cas"))) {
			planeRoleToShow = PlaneRole::Role::CAS;
			generatingPlane();
		}
		if (ImGui::Button(getLocalizedString("navalBomber"))) {
			planeRoleToShow = PlaneRole::Role::NavalBombing;
			generatingPlane();
		}
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("tacticalBomber"))) {
			planeRoleToShow = PlaneRole::Role::TacticalBombing;
			generatingPlane();
		}
		ImGui::SameLine();
		if (ImGui::Button(getLocalizedString("strategicBomber"))) {
			planeRoleToShow = PlaneRole::Role::StrategicBombing;
			generatingPlane();
		}
		if (Renderer::createButtonWithPosition(getLocalizedString("allPlane"), Constant::Position::MIDDLE)) {
			std::vector<PlaneRole::Role> planeRole;
			for (int i = 0; i < PlaneRole::Role::Last; i++) {
				planeRole.push_back(static_cast<PlaneRole::Role>(i));
			}
			if (allCountries) {
				for (Country& country : countryList) {
					for (PlaneRole::Role& role : planeRole) {
						Plane plane = Plane::generateRandomPlane(role);
						country.planeList.insert(std::pair<PlaneRole::Role, Plane>(role, plane));
						country.newPlaneStats.insert(std::pair<PlaneRole::Role, Stats>(role, Stats()));
						planeIconNames.insert(std::pair<PlaneType::Type, std::string>(plane.type, Icon::GetInstance()->getPlaneIcon(plane.type, role, &country)));
					}
				}
			}
			else {
				for (PlaneRole::Role& role : planeRole) {
					Plane plane = Plane::generateRandomPlane(role);
					country->planeList.insert(std::pair<PlaneRole::Role, Plane>(role, plane));
					country->newPlaneStats.insert(std::pair<PlaneRole::Role, Stats>(role, Stats()));
					planeIconNames.insert(std::pair<PlaneType::Type, std::string>(plane.type, Icon::GetInstance()->getPlaneIcon(plane.type, role, country)));
				}
			}

			allGenerationPlaneWindowOpen = true;
			generateWindowOpen = false;

		}
		ImGui::PopStyleColor();
	}

	void generatingPlane() {
		if (allCountries) {
			for (Country& country : countryList) {
				Plane plane = Plane::generateRandomPlane(planeRoleToShow);

				country.planeList.insert(std::pair<PlaneRole::Role, Plane>(planeRoleToShow, plane));
				country.newPlaneStats.insert(std::pair<PlaneRole::Role, Stats>(planeRoleToShow, Stats()));

				std::map<std::string, Texture> icon = Icon::GetInstance()->getPlaneIcon(PlaneType::typeToString(plane.type));
				planeIconNames.insert(std::pair<PlaneType::Type, std::string>(plane.type, Icon::GetInstance()->getPlaneIcon(plane.type, planeRoleToShow, &country)));
			}
		}
		else {
			Plane plane = Plane::generateRandomPlane(planeRoleToShow);

			country->planeList.insert(std::pair<PlaneRole::Role, Plane>(planeRoleToShow, plane));
			country->newPlaneStats.insert(std::pair<PlaneRole::Role, Stats>(planeRoleToShow, Stats()));

			std::map<std::string, Texture> icon = Icon::GetInstance()->getPlaneIcon(PlaneType::typeToString(plane.type));
			planeIconNames.insert(std::pair<PlaneType::Type, std::string>(plane.type, Icon::GetInstance()->getPlaneIcon(plane.type, planeRoleToShow, country)));
		}

		designerPlaneWindowOpen = true;
		generateWindowOpen = false;
	}
};