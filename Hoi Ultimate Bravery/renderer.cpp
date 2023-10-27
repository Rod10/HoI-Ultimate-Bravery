#include "renderer.hpp"

void setIcon(float y, float x, std::string type, std::string name, UnitType::Type unitType) {
	ImGui::SetCursorPosY(y);
	ImGui::SetCursorPosX(x);
	if (unitType == UnitType::Type::Tank) {
		Texture texture = Icon::GetInstance()->getTankIconTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
	}
	else if (unitType == UnitType::Type::Ship) {
		Texture texture = Icon::GetInstance()->getShipIconTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
	}
	else if (unitType == UnitType::Type::Plane) {
		Texture texture = Icon::GetInstance()->getPlaneIconTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
	}
}

void setImage(float y, float x, std::string type, std::string name, UnitType::Type unitType) {
	ImGui::SetCursorPosY(y);
	ImGui::SetCursorPosX(x);
	if (unitType == UnitType::Type::Tank) {
		Texture texture = Icon::GetInstance()->getTankModulesTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
	}
	else if (unitType == UnitType::Type::Ship) {
		Texture texture = Icon::GetInstance()->getShipModulesTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
	}
	else if (unitType == UnitType::Type::Plane) {
		Texture texture = Icon::GetInstance()->getPlaneModulesTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
	}
}

float calculatePos(Constant::Position position, std::string text) {
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(text.c_str()).x - style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * (position / 1000.f);
	return off;
}

float calculatePos(Constant::Position position, int width) {
	ImGuiStyle& style = ImGui::GetStyle();

	float size = width - style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * (position / 1000.f);
	return off;
}

bool createButtonWithSize(const char* label, ImVec2 size) {
	ImGuiStyle& style = ImGui::GetStyle();

	return ImGui::Button(label, size);
}

bool createButtonWithPos(const char* label, float x, float y) {
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetCursorPosX(x);
	ImGui::SetCursorPosY(y);

	return ImGui::Button(label);
}

void createLabelWithPosition(const char* label, Constant::TextPos position) {
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * (position / 1000.f);
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

	return ImGui::Text(label);
}

void createLabelWithPosition(const char* label, float position, Constant::TextPos height) {
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * (position / 1000.f);
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

	ImGui::SetCursorPosY(height);
	return ImGui::Text(label);
}

void createLabelWithPosition(const char* label, float position, float height) {
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * (position / 1000.f);
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

	ImGui::SetCursorPosY(height);
	return ImGui::Text(label);
}

void createLabelWithPosition(const char* label, float position)
{
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * (position / 1000.f);
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

	return ImGui::Text(label);
}

void createTitleWithPosition(const char* label, float x, float y)
{
	ImGui::SetCursorPosY(y);
	ImGui::SetCursorPosX(x);
	return ImGui::Text(label);
}

void renderMainMenuButtonBlock(float pos) {
	auto windowsManagement = WindowsManagement::GetInstance();
	Settings* settings = Settings::getInstance();
	if (createButtonWithSize("Generate", ImVec2(365.0f, 75.0f))) {
		windowsManagement->setButtons("mainMenu", false);
		windowsManagement->setButtons("generate", true);
		windowsManagement->setSubWindow("generate", true);
	}
	if (createButtonWithSize("Import", ImVec2(365.0f, 75.0f))) {
		windowsManagement->setButtons("mainMenu", false);
		windowsManagement->setButtons("import", true);
		windowsManagement->setSubWindow("import", true);
	}
	if (createButtonWithSize("Multiplayer", ImVec2(365.0f, 75.0f))) {
		windowsManagement->setButtons("mainMenu", false);
		windowsManagement->setButtons("multiplayer", true);
		windowsManagement->setSubWindow("multiplayer", true);
	}
	if (createButtonWithSize("Options", ImVec2(365.0f, 75.0f))) {
		windowsManagement->setButtons("mainMenu", false);
		windowsManagement->setButtons("options", true);
		windowsManagement->setSubWindow("options", true);
	}
	if (createButtonWithSize("Quit", ImVec2(365.0f, 75.0f))) {
		//countries files
		std::string countriesPathDirectory = "./Assets/Data/Files/Back-Up/countries";
		std::string countriesTargetDirectory = std::format("{0}/history/countries", settings->getGamepath());
		//idea files
		std::string ideassPathDirectory = "./Assets/Data/Files/Back-Up/ideas";
		std::string ideasTargetDirectory = std::format("{0}/common/ideas", settings->getGamepath());

		try {
			for (const auto& entry : std::filesystem::directory_iterator(countriesTargetDirectory))
				std::filesystem::remove_all(entry.path());
			for (const auto& entry : std::filesystem::directory_iterator(ideasTargetDirectory))
				std::filesystem::remove_all(entry.path());

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
}

void renderGenerateButtonBlock() {
	WindowsManagement* windowsManagement = WindowsManagement::GetInstance();
	ImGuiIO& io = ImGui::GetIO();
	float my_tex_w = (float)io.Fonts->TexWidth;
	float my_tex_h = (float)io.Fonts->TexHeight;

	std::unordered_map<UnitType::Type, std::string> icons {
		{UnitType::Tank, "Modern_tank_button"},
		{UnitType::Plane, "Air_Support"},
		{UnitType::Ship, "Hold"},
		{UnitType::Infantry, "Infantry"},
	};
	UnitType::Type prevType = windowsManagement->getPrevTypeSubWindow();
	for (auto& [type, icon] : icons) {
		Texture texture = Icon::GetInstance()->getOthersTextures("icons", icon);
		ImVec2 size = ImVec2(texture.my_image_width, texture.my_image_height);                         // Size of the image we want to make visible
		ImVec2 uv0 = ImVec2(0.0f, 0.0f);                            // UV coordinates for lower-left
		ImVec2 uv1 = ImVec2(1.0f, 1.0f);
		//ImVec2 uv1 = ImVec2(100.0f / my_tex_w, 75.0f / my_tex_h);    // UV coordinates for (32,32) in our texture
		ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);             // Black background
		ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

		if (ImGui::ImageButton(UnitType::typeToString(type).c_str(), (void*)(intptr_t)texture.my_image_texture, size, uv0, uv1, bg_col, tint_col)) {
			if (prevType != NULL) windowsManagement->setTypeSubWindow(prevType, false);
			windowsManagement->setTypeSubWindow(type, true);
			windowsManagement->setPrevTypeSubWindow(type);
		}
	}
	if (createButtonWithSize("Back", ImVec2(365.0f, 75.0f))) {
		windowsManagement->setButtons("mainMenu", true);
		windowsManagement->setButtons("generate", false);
		windowsManagement->setSubWindow("generate", false);
	}
}

void renderMultiplayerButtonBlock() {
	WindowsManagement* windowsManagement = WindowsManagement::GetInstance();
	if (createButtonWithSize("Back", ImVec2(365.0f, 75.0f))) {
		windowsManagement->setButtons("mainMenu", true);
		windowsManagement->setButtons("multiplayer", false);
		windowsManagement->setSubWindow("multiplayer", false);
	}
}

void renderOptionsButtonBlock() {
	WindowsManagement* windowsManagement = WindowsManagement::GetInstance();
	if (createButtonWithSize("Back", ImVec2(365.0f, 75.0f))) {
		windowsManagement->setButtons("mainMenu", true);
		windowsManagement->setButtons("options", false);
		windowsManagement->setSubWindow("options", false);
	}
}

void Renderer::renderButtonBlock(float pos)
{
	std::string window;
	for (auto& it : WindowsManagement::GetInstance()->getButtons()) {
		if (it.second == true) {
			window = it.first;
		}
	}
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[5];
	ImGui::PushFont(basicFont);
	if (window == "mainMenu") {
		renderMainMenuButtonBlock(pos);
	}
	else if (window == "generate" || window == "import") {
		renderGenerateButtonBlock();
	}
	else if (window == "multiplayer") {
		renderMultiplayerButtonBlock();
	}
	else if (window == "options") {
		renderOptionsButtonBlock();
	}
	ImGui::PopFont();
}

void renderGenerateImportSubWindow() {
	ImGuiIO& io = ImGui::GetIO();
	ImFont* statsFont = io.Fonts->Fonts[4];
	WindowsManagement* windowsManagement = WindowsManagement::GetInstance();
	UnitType::Type unitType;
	for (auto& it : windowsManagement->getTypeSubWindow()) {
		if (it.second == true) {
			unitType = it.first;
		}
	}
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	std::map<UnitType::Type, std::vector<std::string>> icons {
		{UnitType::Tank, {"Light_tank", "Medium_tank", "Heavy_tank", "Super_heavy_tank", "Modern_tank"}},
		{UnitType::Plane, {"Fighter", "CAS", "Naval_bomber", "Tactical_bomber", "Strategic_bomber"}},
		{UnitType::Ship, {"Destroyer", "Cruiser", "Battleship", "Carrier", "Submarine"}}
	};
	ImGui::PushFont(statsFont);
	if (ImGui::BeginTable("table1", 3))
	{
		for (int row = 0; row < 5; row++)
		{
			ImGui::TableNextRow();
			for (int column = 0; column < 3; column++)
			{
				ImGui::TableSetColumnIndex(column);
				if (row == 0) {
					Texture texture = Icon::GetInstance()->getOthersTextures("icons", icons.find(unitType)->second[column]);
					ImVec2 size = ImVec2(texture.my_image_width, texture.my_image_height);                         // Size of the image we want to make visible
					ImVec2 uv0 = ImVec2(0.0f, 0.0f);                            // UV coordinates for lower-left
					ImVec2 uv1 = ImVec2(1.0f, 1.0f);
					//ImVec2 uv1 = ImVec2(100.0f / my_tex_w, 75.0f / my_tex_h);    // UV coordinates for (32,32) in our texture
					ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);             // Black background
					ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
					if (ImGui::ImageButton(icons.find(unitType)->second[column].c_str(), (void*)(intptr_t)texture.my_image_texture, size, uv0, uv1, bg_col, tint_col)) {
						if (unitType == UnitType::Ship) {
							unitTypeSelected = unitType;
							columnSelected = column;
							if (countrySelected->getShipHullListSize(column) == 0) {
								Ship ship = Ship::generateRandomShip(static_cast<Hull::Type>(column));
								ship.iconName = Icon::GetInstance()->getShipIcon(ship);
								countrySelected->setNewUnits(unitType, ship);
							}
						}
						else if (unitType == UnitType::Tank) {
							unitTypeSelected = unitType;
							columnSelected = column;
							if (countrySelected->getTankTypeListSize(column) == 0) {
								Tank tank = Tank::generateRandomTank(static_cast<TankType::Type>(column));
								tank.iconName = Icon::GetInstance()->getRandomIcon(tank.type);
								countrySelected->setNewUnits(unitType, tank);
							}
						}
						else if (unitType == UnitType::Plane) {

						}
						windowsManagement->setTypeSubWindow(unitType, true);
						windowsManagement->setSubWindow("generate", false);
						windowsManagement->setSubWindow("designer", true);
					}
				}
				else {
					if (unitType == UnitType::Ship) {

					}
					else if (unitType == UnitType::Tank) {
						if (countrySelected->getTankTypeListSize(column) == 0) {
							ImGui::Text("Not Created", row, column);
						}
						else {
							auto [tank, tankStats] = countrySelected->getTankByType(column);
							ImGui::Text(tankStats.getShowStat(row).c_str(), row, column);
						}
					}
					else if (unitType == UnitType::Plane) {

					}
				}
			}
		}
		ImGui::EndTable();
	}
	ImGui::SetCursorPosX(200.0f);
	ImGui::SetCursorPosY(center.y / 1.5f);
	if (ImGui::BeginTable("table2", 2))
	{
		for (int row = 0; row < 5; row++)
		{
			ImGui::TableNextRow();
			for (int column = 0; column < 2; column++)
			{
				ImGui::TableSetColumnIndex(column);				
				if (row == 0) {
					Texture texture = Icon::GetInstance()->getOthersTextures("icons", icons.find(unitType)->second[column + 3]);
					ImVec2 size = ImVec2(texture.my_image_width, texture.my_image_height);                         // Size of the image we want to make visible
					ImVec2 uv0 = ImVec2(0.0f, 0.0f);                            // UV coordinates for lower-left
					ImVec2 uv1 = ImVec2(1.0f, 1.0f);
					//ImVec2 uv1 = ImVec2(100.0f / my_tex_w, 75.0f / my_tex_h);    // UV coordinates for (32,32) in our texture
					ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);             // Black background
					ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
					if (ImGui::ImageButton(icons.find(unitType)->second[column + 3].c_str(), (void*)(intptr_t)texture.my_image_texture, size, uv0, uv1, bg_col, tint_col)) {
						if (unitType == UnitType::Ship) {

						}
						else if (unitType == UnitType::Tank) {
							unitTypeSelected = unitType;
							columnSelected = column + 3;
							if (countrySelected->getTankTypeListSize(column + 3) == 0) {
								Tank tank = Tank::generateRandomTank(static_cast<TankType::Type>(column + 3));
								tank.iconName = Icon::GetInstance()->getRandomIcon(tank.type);
								countrySelected->setNewUnits(unitType, tank);
							}
						}
						else if (unitType == UnitType::Plane) {

						}
						windowsManagement->setTypeSubWindow(unitType, true);
						windowsManagement->setSubWindow("generate", false);
						windowsManagement->setSubWindow("designer", true);
					}
				}
				else {					
					if (unitType == UnitType::Ship) {

					}
					else if (unitType == UnitType::Tank) {
						if (countrySelected->getTankTypeListSize(column + 3) == 0) {
							ImGui::Text("Not Created", row, column);
						}
						else {
							auto [tank, tankStats] = countrySelected->getTankByType(column + 3);
							ImGui::Text(tankStats.getShowStat(row).c_str(), row, column);
						}
					}
					else if (unitType == UnitType::Plane) {

					}
				}
			}
		}
		ImGui::EndTable();
	}
	ImGui::PopFont();
}
//Ship Designer
void renderShipDesignerWindows() {
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];
	Texture texture = Icon::GetInstance()->getTankModulesTextures("background", "tank_designer_bg");
	ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));

	setImage(Constant::TextPos::TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "ship_name_bg", UnitType::Type::Ship);

	setImage(95, 150, "background", "ship_icon_bg", UnitType::Type::Ship);

	setImage(Constant::TextPos::TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 275.0f, "background", "ship_name_bg", UnitType::Type::Ship);

}

//Tank Designer
void renderTankDesignerWindows() {
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];
	Texture texture = Icon::GetInstance()->getTankModulesTextures("background", "tank_designer_bg");
	ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
	setImage(Constant::TextPos::TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "tank_name_bg", UnitType::Type::Tank);

	setImage(95.0f, 329, "background", "tank_icon_bg", UnitType::Type::Tank);

	setImage(Constant::TextPos::TANK_ROLE_HEIGHT + 5.0f, ImGui::GetCursorPosX() + 20.0f, "background", "tank_role_bg", UnitType::Type::Tank); 
	
	for (int i = 0; i <= 5; i++) {
		float x = ImGui::GetCursorPosX() + (76 * i) + (13.0f - (i * 3));
		if (i == 0) {
			x = 23.0f;
		}
		setImage(Constant::TextPos::TANK_MODULE_HEIGHT, x, "background", "equipment_icon_bg", UnitType::Type::Tank);
	}

	setImage(ImGui::GetCursorPosY() - 4.0f, ImGui::GetCursorPosX() + 16.0f, "background", "tank_blueprint_background", UnitType::Type::Tank);

	texture = Icon::GetInstance()->getTankModulesTextures("background", "equipment_icon_bg");;
	for (int i = 0; i <= 2; i++) {
		float x = ImGui::GetCursorPosX() + (76 * i) + (12.0f - (i * 3));
		if (i == 0) {
			x = 23.0f;
		}
		setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2, x, "background", "equipment_icon_bg", UnitType::Type::Tank);
	}
	ImGui::PushFont(TitleStatsFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
	createTitleWithPosition("Base Stats", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 45.0f);
	createTitleWithPosition("Combat Stats", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 45.0f);
	createTitleWithPosition("Misc. Stats", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 45.0f);
	ImGui::PopFont();

	//Base Stats 
	ImGui::PushFont(statsFont);
	createTitleWithPosition("Max Speed:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 75.0f);
	createTitleWithPosition("Reliability:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 95.0f);
	createTitleWithPosition("Supply use:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 115.0f);
	//Base Stats 

	//Combat Stats 
	createTitleWithPosition("Soft attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 75.0f);
	createTitleWithPosition("Hard attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 95.0f);
	createTitleWithPosition("Piercing:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 115.0f);
	createTitleWithPosition("Hardness:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 135.0f);
	createTitleWithPosition("Armor:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 155.0f);
	createTitleWithPosition("Breakthrough:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 175.0f);
	createTitleWithPosition("Defense:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 195.0f);
	createTitleWithPosition("Air attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 215.0f);
	//Combat Stats

	//Misc. Stats
	createTitleWithPosition("Fuel Capacity:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 75.0f);
	createTitleWithPosition("Fuel Usage:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 95.0f);
	createTitleWithPosition("Suppression:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 115.0f);
	createTitleWithPosition("Reconnaissance:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 135.0f);
	createTitleWithPosition("Entrenchment:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 155.0f);
	//Misc. Stats

	ImGui::PopFont();
	ImGui::PopStyleColor();

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	ImGui::PushFont(textFont);
	createTitleWithPosition("Engine", Constant::Position::MIDDLE - 110.0f, Constant::TextPos::TANK_MODULE_HEIGHT_2);
	createTitleWithPosition("Armor", Constant::Position::MIDDLE - 30.0f, Constant::TextPos::TANK_MODULE_HEIGHT_2);
	ImGui::PopFont();
	ImGui::PopStyleColor();
}

//Plane Designer
void renderPlaneDesignerWindows() {

}

//Ship stats
void renderUnit(Ship ship) {

}

//Tank stats
void renderUnit(std::tuple<Tank, TankStats> unit) {
	auto& [tank, tankStats] = unit;
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[2];
	ImFont* statsFont = io.Fonts->Fonts[4];
	ImGui::PushFont(basicFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	ImGui::SetCursorPosY(Constant::TextPos::TANK_NAME_HEIGHT + 5.0f);
	createLabelWithPosition(std::format("{0} {1}", Tank::tankVersionToString(tank.version).c_str(), Tank::tankTypeToString(tank.type)).c_str(), Constant::TextPos::TANK_NAME_WIDTH);
	setIcon(ImGui::GetCursorPosY() - 15.0f, ImGui::GetCursorPosX() + 325.0f, Tank::tankTypeToString(tank.type), tank.iconName, UnitType::Type::Tank);
	ImGui::SetCursorPosY(Constant::TextPos::TANK_ROLE_HEIGHT + 10.0f);
	createLabelWithPosition(Role::typeToString(tank.role).c_str(), Constant::TextPos::TANK_NAME_WIDTH);
	std::string fileName = std::format("{0}_{1}", Gun::gunNameToString(tank.gun.name), Gun::typeToString(tank.gun.type));
	setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 22.0f, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}_turret_{1}", TurretType::turretTypeToString(tank.turret.type), tank.turret.crew);
	setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 88.0f, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[0].type));
	setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 170.0f, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[1].type));
	setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 240.0f, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[2].type));
	setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 315.0f, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[3].type));
	setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 390.0f, "modules", fileName, UnitType::Type::Tank);

	setImage(ImGui::GetCursorPosY() - 4.0f, ImGui::GetCursorPosX() + 16.0f, "blueprint", std::format("ger_{0}_tank_blueprint", Tank::tankTypeToString(tank.type)), UnitType::Type::Tank);

	fileName = std::format("{0}", Suspension::typeToString(tank.suspension.type));
	setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f, ImGui::GetCursorPosX() + 22.5f, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", Armor::typeToString(tank.armor.type));
	setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f, ImGui::GetCursorPosX() + 100.0f, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", Engine::typeToString(tank.engine.type));
	setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f, ImGui::GetCursorPosX() + 165.0f, "modules", fileName, UnitType::Type::Tank);

	ImGui::SetCursorPosY(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 20.0f);
	auto off = calculatePos(Constant::Position::MIDDLE, std::to_string(tank.engineLevel).c_str());
	off /= 1.5;
	createLabelWithPosition(std::to_string(tank.engineLevel).c_str(), off);
	ImGui::SetCursorPosY(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 20.0f);
	createLabelWithPosition(std::to_string(tank.armorLevel).c_str(), off + 55.0f);
	ImGui::PopStyleColor();
	ImGui::PopFont();

	ImGui::PushFont(statsFont);
	//Base stats
	std::string speed = std::format("{:.1f} km/h", tankStats.speed);
	createLabelWithPosition(speed.c_str(), Constant::TextPos::BASE_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 75.0f);

	std::string reliability = std::format("{:.1f} %%", tankStats.reliability);
	createLabelWithPosition(reliability.c_str(), Constant::TextPos::BASE_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 95.0f);

	std::string supplyUse = std::format("{:.2f}", tankStats.supplyUse);
	createLabelWithPosition(supplyUse.c_str(), Constant::TextPos::BASE_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 115.0f);
	//Base stats

	//Combat stats
	std::string softAttack = std::format("{:.2f}", tankStats.softAttack);
	createLabelWithPosition(softAttack.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 75.0f);

	std::string hardAttack = std::format("{:.2f}", tankStats.hardAttack);
	createLabelWithPosition(hardAttack.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 95.0f);

	std::string piercing = std::format("{:.2f}", tankStats.piercing);
	createLabelWithPosition(piercing.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 115.0f);

	std::string hardness = std::format("{:.2f} %%", tankStats.hardness);
	createLabelWithPosition(hardness.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 135.0f);

	std::string armor = std::format("{:.2f}", tankStats.armor);
	createLabelWithPosition(armor.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 155.0f);

	std::string breakthrough = std::format("{:.2f}", tankStats.breakthrough);
	createLabelWithPosition(breakthrough.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 175.0f);

	std::string defense = std::format("{:.2f}", tankStats.defense);
	createLabelWithPosition(defense.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 195.0f);

	std::string airAttack = std::format("{:.2f}", tankStats.airAttack);
	createLabelWithPosition(airAttack.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 215.0f);
	//Combat stats

	//Misc Stats
	std::string fuelCapacity = std::format("{:.2f}", tankStats.fuelCapacity);
	createLabelWithPosition(fuelCapacity.c_str(), Constant::TextPos::MISC_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 75.0f);

	std::string fuelUsage = std::format("{:.2f}", tankStats.fuelUsage);
	createLabelWithPosition(fuelUsage.c_str(), Constant::TextPos::MISC_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 95.0f);

	//TODO research suppression value
	createLabelWithPosition("???", Constant::TextPos::MISC_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 115.0f);

	//TODO research reconnaissance value
	createLabelWithPosition("???", Constant::TextPos::MISC_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 135.0f);

	std::string entrenchment = std::format("{:.2f}", tankStats.entrenchment);
	createLabelWithPosition(entrenchment.c_str(), Constant::TextPos::MISC_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 155.0f);
	//Misc Stats
	ImGui::PopFont();
}

//Plane stats
void renderUnit(Plane plane) {

}

void Renderer::renderSubWindow() {
	std::string window;
	WindowsManagement* windowsManagement = WindowsManagement::GetInstance();
	for (auto& it : windowsManagement->getSubWindow()) {
		if (it.second == true) {
			window = it.first;
		}
	}
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[1];
	ImGui::PushFont(basicFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	createLabelWithPosition(window.c_str(), (float)center.x / 2, 0.f);

	if (window != "designer") {
		createLabelWithPosition("country", 10.0f, ImGui::GetCursorPosY() + 10.0f);
		ImGui::SameLine();
		static ImGuiComboFlags flags = 0;
		static int item_current_idx = 0; // Here we store our selection data as an index.
		std::vector<Country>* countryList = CountryList::GetInstance()->getList();
		const char* combo_preview_value = countryList->at(item_current_idx).name.c_str();  // Pass in the preview value visible before opening the combo (it could be anything)
		if (ImGui::BeginCombo("##", combo_preview_value, flags))
		{
			for (int n = 0; n < countryList->size(); n++)
			{
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(countryList->at(n).name.c_str(), is_selected)) {
					item_current_idx = n;
					countrySelected = &countryList->at(n);
				}

				// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
	}

	if (window == "generate" || window == "import") {
		renderGenerateImportSubWindow();
	}
	else if (window == "multiplayer") {
		std::string text = "Not Done";
		createLabelWithPosition(text.c_str(), (float)center.x / 2.0f, (float)center.y / 2.0f);
	}
	else if (window == "options") {
		std::string text = "Not Done";
		createLabelWithPosition(text.c_str(), (float)center.x / 2.0f, (float)center.y / 2.0f);
	}
	else if (window == "designer") {
		UnitType::Type unitType = UnitType::Type::Tank;
		for (auto& it : windowsManagement->getTypeSubWindow()) {
			if (it.second == true) {
				unitType = it.first;
			}
		}
		switch (unitType)
		{
		case UnitType::Ship:
			renderShipDesignerWindows();
			renderUnit(countrySelected->getShipByHull(columnSelected));
			break;
		case UnitType::Tank:
			renderTankDesignerWindows();
			renderUnit(countrySelected->getTankByType(columnSelected));
			break;
		case UnitType::Plane:
			renderPlaneDesignerWindows();
			break;
		case UnitType::Infantry:
			break;
		default:
			break;
		}
		if (createButtonWithPos("Back", center.x / 3, 575.0f)) {
			windowsManagement->setSubWindow("generate", true);
			windowsManagement->setSubWindow("designer", false);
		}
		if (createButtonWithPos("Regenerate", center.x / 2, 575.0f)) {
			Tank tank = Tank::generateRandomTank(static_cast<TankType::Type>(columnSelected));
			tank.iconName = Icon::GetInstance()->getRandomIcon(tank.type);
			countrySelected->setNewUnits(unitType, tank);
		}
	}
	ImGui::PopStyleColor();
	ImGui::PopFont();
}

void Renderer::renderShipDesignerWindow(bool windowOpen, Ship ship)
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];
	Texture texture = Icon::GetInstance()->getTankModulesTextures("background", "tank_designer_bg");
	auto off = calculatePos(Constant::Position::MIDDLE, texture.my_image_width);
	ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
	ImGui::Begin(ShipType::shipTypeToString(ship.type).c_str(), &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::PushFont(titleFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
	ImGui::SetCursorPosY(Constant::TextPos::TITLE_HEIGHT);
	createLabelWithPosition("Ship Designer", Constant::Position::MIDDLE);
	ImGui::PopFont();
	ImGui::PopStyleColor();

	setImage(Constant::TextPos::TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "ship_name_bg", UnitType::Type::Ship);

	setImage(95, 150, "background", "ship_icon_bg", UnitType::Type::Ship);

	setImage(Constant::TextPos::TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 275.0f, "background", "ship_name_bg", UnitType::Type::Ship);

	for (int i = 0; i <= 6; i++) {
		float x = ImGui::GetCursorPosX() + (76 * i) + (12.0f - (i * 3));
		if (i == 0) {
			x = 21.0f;
		}
		setImage(Constant::TextPos::TANK_MODULE_HEIGHT, x, "background", "equipment_icon_bg", UnitType::Type::Ship);
	}

	setImage(ImGui::GetCursorPosY() - 4.0f, ImGui::GetCursorPosX() + 21.0f, "background", "ship_view_bg", UnitType::Type::Ship);

	texture = Icon::GetInstance()->getTankModulesTextures("background", "equipment_icon_bg");;
	for (int i = 0; i <= 6; i++) {
		float x = ImGui::GetCursorPosX() + (76 * i) + (12.0f - (i * 3));
		if (i == 0) {
			x = 23.0f;
		}
		setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2, x, "background", "equipment_icon_bg", UnitType::Type::Ship);
	}
	ImGui::PushFont(TitleStatsFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
	createTitleWithPosition("Base Stats", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 29.0f);
	createTitleWithPosition("Combat Stats", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 29.0f);
	createTitleWithPosition("Misc. Stats", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 29.0f);
	ImGui::PopFont();

	//Base Stats 
	ImGui::PushFont(statsFont);
	createTitleWithPosition("Max Speed:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 60.0f);
	createTitleWithPosition("Reliability:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 80.0f);
	createTitleWithPosition("Supply use:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 100.0f);
	//Base Stats 

	//Combat Stats 
	createTitleWithPosition("Soft attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 60.0f);
	createTitleWithPosition("Hard attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 80.0f);
	createTitleWithPosition("Piercing:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 100.0f);
	createTitleWithPosition("Hardness:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 120.0f);
	createTitleWithPosition("Armor:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 140.0f);
	createTitleWithPosition("Breakthrough:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 160.0f);
	createTitleWithPosition("Defense:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 180.0f);
	createTitleWithPosition("Air attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 200.0f);
	//Combat Stats

	//Misc. Stats
	createTitleWithPosition("Fuel Capacity:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 60.0f);
	createTitleWithPosition("Fuel Usage:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 80.0f);
	createTitleWithPosition("Suppression:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 100.0f);
	createTitleWithPosition("Reconnaissance:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 120.0f);
	createTitleWithPosition("Entrenchment:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 140.0f);
	//Misc. Stats

	ImGui::PopFont();
	ImGui::PopStyleColor();

	ImGui::End();
}

void Renderer::renderPlaneDesignerWindow(bool windowOpen, Plane plane)
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];
	Texture texture = Icon::GetInstance()->getTankModulesTextures("background", "tank_designer_bg");
	auto off = calculatePos(Constant::Position::MIDDLE, texture.my_image_width);
	ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
	ImGui::Begin(PlaneType::typeToString(plane.type).c_str(), &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::PushFont(titleFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
	ImGui::SetCursorPosY(Constant::TextPos::TITLE_HEIGHT);
	createLabelWithPosition("Plane Designer", Constant::Position::MIDDLE);
	ImGui::PopFont();
	ImGui::PopStyleColor();

	setImage(Constant::TextPos::TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "tank_name_bg", UnitType::Type::Plane);

	setImage(79.8, 329, "background", "tank_icon_bg", UnitType::Type::Plane);

	setImage(Constant::TextPos::TANK_ROLE_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "tank_role_bg", UnitType::Type::Plane);

	for (int i = 0; i <= 4; i++) {
		float x = ImGui::GetCursorPosX() + (76 * i) + (12.0f - (i * 3));
		if (i == 0) {
			x = 21.0f;
		}
		setImage(Constant::TextPos::TANK_MODULE_HEIGHT, x, "background", "equipment_icon_bg", UnitType::Type::Plane);
	}

	setImage(ImGui::GetCursorPosY() - 4.0f, ImGui::GetCursorPosX() + 16.0f, "background", "plane_view_bg", UnitType::Type::Plane);

	texture = Icon::GetInstance()->getTankModulesTextures("background", "equipment_icon_bg");;
	for (int i = 0; i <= 6; i++) {
		float x = ImGui::GetCursorPosX() + (76 * i) + (12.0f - (i * 3));
		if (i == 0) {
			x = 23.0f;
		}
		setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2, x, "background", "equipment_icon_bg", UnitType::Type::Plane);
	}
	ImGui::PushFont(TitleStatsFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
	createTitleWithPosition("Base Stats", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 29.0f);
	createTitleWithPosition("Combat Stats", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 29.0f);
	createTitleWithPosition("Misc. Stats", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 29.0f);
	ImGui::PopFont();

	//Base Stats 
	ImGui::PushFont(statsFont);
	createTitleWithPosition("Max Speed:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 60.0f);
	createTitleWithPosition("Reliability:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 80.0f);
	createTitleWithPosition("Supply use:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 100.0f);
	//Base Stats 

	//Combat Stats 
	createTitleWithPosition("Soft attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 60.0f);
	createTitleWithPosition("Hard attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 80.0f);
	createTitleWithPosition("Piercing:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 100.0f);
	createTitleWithPosition("Hardness:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 120.0f);
	createTitleWithPosition("Armor:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 140.0f);
	createTitleWithPosition("Breakthrough:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 160.0f);
	createTitleWithPosition("Defense:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 180.0f);
	createTitleWithPosition("Air attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 200.0f);
	//Combat Stats

	//Misc. Stats
	createTitleWithPosition("Fuel Capacity:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 60.0f);
	createTitleWithPosition("Fuel Usage:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 80.0f);
	createTitleWithPosition("Suppression:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 100.0f);
	createTitleWithPosition("Reconnaissance:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 120.0f);
	createTitleWithPosition("Entrenchment:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 140.0f);
	//Misc. Stats

	ImGui::PopFont();
	ImGui::PopStyleColor();

	ImGui::End();
}

int getModulePos(int index) {
	switch (index) {
	case 0: return Module::CustomModulePos::First;
	case 1: return Module::CustomModulePos::Second;
	case 2: return Module::CustomModulePos::Third;
	case 3: return Module::CustomModulePos::Four;
	case 4: return Module::CustomModulePos::Five;
	case 5: return Module::CustomModulePos::Six;
	case 6: return Module::CustomModulePos::Sevent;
	}
}

void Renderer::renderStats(bool windowOpen, Ship ship, std::map<Hull::Type, std::string> shipIconNames, std::unordered_map<Hull::Type, Stats> newShipStats)
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[2];
	ImFont* statsFont = io.Fonts->Fonts[4];

	auto off = calculatePos(Constant::Position::MIDDLE, 1092);
	ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
	ImGui::SetNextWindowSize(ImVec2(1108, 569));
	ImGui::Begin("##", &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
	ImGui::PushFont(basicFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	std::string string = std::format("{0} {1}", ShipVersion::versionToYear(ship.version), ShipType::shipTypeToString(ship.type).c_str());
	createTitleWithPosition(string.c_str(), ImGui::GetCursorPosX() + 30.0f, 65);

	setIcon(ImGui::GetCursorPosY(), ImGui::GetCursorPosX() + 200, Hull::typeToString(ship.hull), shipIconNames.find(ship.hull)->second, UnitType::Type::Ship);

	int index = 0;
	for (auto& module : ship.customModule) {
		std::string fileName;
		if (module.type == Module::None) {
			fileName = "none";
		}
		else {
			fileName = std::format("{0}_{1}", Module::typeToImagesString(module.type, module.subType, ship.type), (module.version + 1));
		}
		setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, getModulePos(index) + 5.0f, "modules", fileName, UnitType::Type::Ship);
		index++;
	}
	index = 0;
	for (auto& module : ship.fixedModule) {
		std::string fileName;
		if (module.subType == Module::Empty) {
			fileName = "none";
		}
		else {
			fileName = std::format("{0}_{1}", Module::typeToImagesString(module.type, module.subType, ship.type), (module.version + 1));
		}
		setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f, getModulePos(index), "modules", fileName, UnitType::Type::Ship);
		index++;
	}
	ImGui::PopStyleColor();
	ImGui::PopFont();
}

void Renderer::renderStats(bool windowOpen, Plane plane, std::map<PlaneType::Type, std::string> planeIconNames, std::unordered_map<PlaneRole::Role, Stats> newPlaneStats)
{
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[2];
	ImFont* statsFont = io.Fonts->Fonts[4];

	auto off = calculatePos(Constant::Position::MIDDLE, 1092);
	ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
	ImGui::SetNextWindowSize(ImVec2(1108, 569));
	ImGui::Begin("Light Tank", &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
	ImGui::PushFont(basicFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	std::string string = std::format("{0} {1}", PlaneVersion::versionToYear(plane.version), PlaneRole::roleToString(plane.role).c_str());
	createTitleWithPosition(string.c_str(), 35.0f, Constant::TextPos::TANK_NAME_HEIGHT + 5.0f);

	setIcon(ImGui::GetCursorPosY() - 20.0f, ImGui::GetCursorPosX() + 325.0f, PlaneType::typeToString(plane.type), planeIconNames.find(plane.type)->second, UnitType::Type::Plane);

	int index = 0;
	for (auto& module : plane.fixed) {
		std::string fileName;
		if (module.type == PlaneModule::Type::None) {
			fileName = "none";
		}
		else {
			fileName = PlaneModule::typeToImagesString(plane.type, module.subType, module.version, module.number);
		}
		setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, getModulePos(index) + 10.0f, "modules", fileName, UnitType::Type::Plane);
		index++;
	}

	std::string fileName = std::format("{0}", PlaneEngine::engineToImageString(plane.engine));
	setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 22.5f, "modules", fileName, UnitType::Type::Plane);

	/*for (auto& module : plane.fixed) {
		std::string fileName;
		if (module.type == PlaneModule::Type::None) {
			fileName = "none";
		}
		else {
			fileName = PlaneModule::typeToImagesString(plane.type, module.subType, module.version, module.number);
		}
		setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f, getModulePos(index) + 10.0f, "modules", fileName, UnitType::Type::Plane);
		index++;
	}*/
	ImGui::PopStyleColor();
	ImGui::PopFont();
}