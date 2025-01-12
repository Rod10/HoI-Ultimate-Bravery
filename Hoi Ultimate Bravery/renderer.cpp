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
	else if (unitType == UnitType::Type::Division) {
		Texture texture = Icon::GetInstance()->getUnitsTextures(type, name);
		if (type != "Background") {
			texture.my_image_height = texture.my_image_height * 0.95;
			texture.my_image_width = texture.my_image_width * 0.95;
		}
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

void AlignForWidth(float width, float alignment = 0.5f) {
	ImGuiStyle& style = ImGui::GetStyle();
	float avail = ImGui::GetContentRegionAvail().x;
	float off = (avail - width) * alignment;
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
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
		{UnitType::Division, "Infantry"},
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
		windowsManagement->setButtons("import", false);
		windowsManagement->setSubWindow("generate", false);
		windowsManagement->setSubWindow("import", false);
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

void renderImportWindow(UnitType::Type unitType) {
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	std::map<UnitType::Type, std::vector<std::string>> icons {
		{UnitType::Tank, { "Light_tank", "Medium_tank", "Heavy_tank", "Super_heavy_tank", "Modern_tank" }},
		{ UnitType::Plane, {"Fighter", "CAS", "Naval_bomber", "Tactical_bomber", "Strategic_bomber"} },
		{ UnitType::Ship, {"Destroyer", "Cruiser", "Battleship", "Carrier", "Submarine"} },
		{ UnitType::Division, {"Infantry"} }
	};
	std::map<UnitType::Type, int> iconsColNumber{
		{UnitType::Tank, 3},
		{ UnitType::Plane, 3 },
		{ UnitType::Ship, 3 },
		{ UnitType::Division, countrySelected->getDivisionListSize() }
	};
	if (ImGui::BeginTable("table1", 3))
	{
		for (int row = 0; row < 5; row++)
		{
			ImGui::TableNextRow();
			for (int column = 0; column < iconsColNumber.find(unitType)->second; column++)
			{
				ImGui::TableSetColumnIndex(column);
				if (row == 0) {
					Texture texture = Icon::GetInstance()->getOthersTextures("icons", icons.find(unitType)->second[column]);
					ImVec2 size = ImVec2(texture.my_image_width, texture.my_image_height);
					ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
				}
				else if (row == 1) {
					/*std::string name = std::format("Import##{0}", column);
					if (ImGui::Button(name.c_str())) {
						switch (unitType)
						{
						case UnitType::Ship:
							countrySelected->setImport(unitType, static_cast<Hull::Type>(column), true);
							break;
						case UnitType::Tank:
							countrySelected->setImport(unitType, static_cast<TankType::Type>(column), true);
							break;
						case UnitType::Plane:
							countrySelected->setImport(unitType, static_cast<PlaneRole::Role>(column), true);
							break;
						case UnitType::Infantry:
							break;
						default:
							break;
						}
					}*/
				}
				else if (row == 2) {
					std::string icon;
					if (unitType == UnitType::Ship) {
						if (countrySelected->getImport(unitType, static_cast<Hull::Type>(column))) {
							icon = "check";
						} else {
							icon = "xmark";
						}
					}
					else if (unitType == UnitType::Tank) {
						if (countrySelected->getImport(unitType, static_cast<TankType::Type>(column))) {
							icon = "check";
						}
						else {
							icon = "xmark";
						}
					}
					else if (unitType == UnitType::Plane) {
						if (countrySelected->getImport(unitType, static_cast<PlaneRole::Role>(column))) {
							icon = "check";
						}
						else {
							icon = "xmark";
						}
					}
					else if (unitType == UnitType::Division) {
						if (countrySelected->getImport(unitType, column)) {
							icon = "check";
						}
						else {
							icon = "xmark";
						}
					}
					Texture texture = Icon::GetInstance()->getOthersTextures("icons", icon);
					ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width / 7, texture.my_image_height / 7));
				}
			}
		}
		ImGui::EndTable();
	}
	ImGui::SetCursorPosX(200.0f);
	ImGui::SetCursorPosY(center.y / 1.5f);
	if (unitType != UnitType::Division) {
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
						ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
					}
					else if (row == 1) {
						/*std::string name = std::format("Import##{0}", column);
						if (ImGui::Button(name.c_str())) {
							switch (unitType)
							{
							case UnitType::Ship:
								countrySelected->setImport(unitType, static_cast<Hull::Type>(column + 4), true);
								break;
							case UnitType::Tank:
								countrySelected->setImport(unitType, static_cast<TankType::Type>(column + 3), true);
								break;
							case UnitType::Plane:
								countrySelected->setImport(unitType, static_cast<PlaneRole::Role>(column + 3), true);
								break;
							case UnitType::Infantry:
								break;
							default:
								break;
							}
						}*/
					}
					else if (row == 2) {
						std::string icon;
						if (unitType == UnitType::Ship) {
							if (countrySelected->getImport(unitType, static_cast<Hull::Type>(column + 4))) {
								icon = "check";
							}
							else {
								icon = "xmark";
							}
						}
						else if (unitType == UnitType::Tank) {
							if (countrySelected->getImport(unitType, static_cast<TankType::Type>(column + 3))) {
								icon = "check";
							}
							else {
								icon = "xmark";
							}
						}
						else if (unitType == UnitType::Plane) {
							if (countrySelected->getImport(unitType, static_cast<PlaneRole::Role>(column + 3))) {
								icon = "check";
							}
							else {
								icon = "xmark";
							}
						}
						Texture texture = Icon::GetInstance()->getOthersTextures("icons", icon);
						ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width / 7, texture.my_image_height / 7));
					}
				}
			}
			ImGui::EndTable();
		}
	}
	ImGui::SetCursorPosX(center.x / 2);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 50.0f);
	if (ImGui::Button("Reset File")) {
		if (unitType == UnitType::Ship) {
			for (int hull = Hull::Type::Destroyer; hull != Hull::Type::Last; hull++) {
				countrySelected->setImport(unitType, static_cast<Hull::Type>(hull), false);
			}
		}
		else if (unitType == UnitType::Tank) {
			for (int type = TankType::Type::Light; type != TankType::Type::Last; type++) {
				countrySelected->setImport(unitType, static_cast<TankType::Type>(type), false);
			}
		}
		else if (unitType == UnitType::Plane) {
			for (int role = PlaneRole::Role::Fighter; role != PlaneRole::Role::Last; role++) {
				countrySelected->setImport(unitType, static_cast<PlaneRole::Role>(role), false);
			}
		}
		else if (unitType == UnitType::Division) {
			countrySelected->setImport(unitType, 0, false);
		}
	}
	ImGui::SetCursorPosX(center.x / 2);
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 50.0f);
	if (ImGui::Button("Import all")) {
		if (unitType == UnitType::Ship) {
			for (int hull = Hull::Type::Destroyer; hull != Hull::Type::Last; hull++) {
				if (hull != Hull::Type::SuperHeavyShip) {
					countrySelected->setImport(unitType, static_cast<Hull::Type>(hull), true);
				}
			}
		}
		else if (unitType == UnitType::Tank) {
			for (int type = TankType::Type::Light; type != TankType::Type::Last; type++) {
				countrySelected->setImport(unitType, static_cast<TankType::Type>(type), true);
			}
		}
		else if (unitType == UnitType::Plane) {
			for (int role = PlaneRole::Role::Fighter; role != PlaneRole::Role::Last; role++) {
				countrySelected->setImport(unitType, static_cast<PlaneRole::Role>(role), true);
			}
		}
		else if (unitType == UnitType::Division) {
			countrySelected->setImport(unitType, 0, true);
		}
		if (allCountries) {
			for (auto& country : *countryList) {
				Files::generateCountryFile(&country, converterToGameName);
				Files::generateIdeaFile(&country);
			}
		}
		else {
			if (unitType == UnitType::Division) {
				Files::generateUnitsFiles(countrySelected);
			}
			else {
				Files::generateCountryFile(countrySelected, converterToGameName);
				Files::generateIdeaFile(countrySelected);
			}
		}
	}
}

void renderGenerateImportSubWindow() {
	ImGuiIO& io = ImGui::GetIO();
	ImFont* statsFont = io.Fonts->Fonts[4];
	WindowsManagement* windowsManagement = WindowsManagement::GetInstance();
	std::string window;
	for (auto& it : windowsManagement->getSubWindow()) {
		if (it.second == true) {
			window = it.first;
		}
	}
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
		{UnitType::Ship, {"Destroyer", "Cruiser", "Battleship", "Carrier", "Submarine"}},
		{UnitType::Division, {"Infantry"}}
	};
	std::map<UnitType::Type, int> iconsColNumber{
		{UnitType::Tank, 3},
		{UnitType::Plane, 3},
		{UnitType::Ship, 3},
		{UnitType::Division, countrySelected->getDivisionListSize()}
	};
	if (window == "generate") {
		ImGui::PushFont(statsFont);
		if (ImGui::BeginTable("table1", 3)) {
			for (int row = 0; row < 5; row++) {
				ImGui::TableNextRow();
				for (int column = 0; column < iconsColNumber.find(unitType)->second; column++) {
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
									if (allCountries) {
										for (auto& country : *countryList) {
											Ship ship = Ship::generateRandomShip(static_cast<Hull::Type>(column));
											ship.iconName = Icon::GetInstance()->getShipIcon(ship);
											country.setNewUnits(unitType, ship);
										}
									} else {
										Ship ship = Ship::generateRandomShip(static_cast<Hull::Type>(column));
										ship.iconName = Icon::GetInstance()->getShipIcon(ship);
										countrySelected->setNewUnits(unitType, ship);
									}
								}
							}
							else if (unitType == UnitType::Tank) {
								unitTypeSelected = unitType;
								columnSelected = column;
								if (countrySelected->getTankTypeListSize(column) == 0) {
									if (allCountries) {
										for (auto& country : *countryList) {
											Tank tank = Tank::generateRandomTank(static_cast<TankType::Type>(column));
											tank.iconName = Icon::GetInstance()->getRandomIcon(tank.type);
											country.setNewUnits(unitType, tank);
										}
									}
									else {
										Tank tank = Tank::generateRandomTank(static_cast<TankType::Type>(column));
										tank.iconName = Icon::GetInstance()->getRandomIcon(tank.type);
										countrySelected->setNewUnits(unitType, tank);
									}
								}
							}
							else if (unitType == UnitType::Plane) {
								unitTypeSelected = unitType;
								columnSelected = column;
								if (countrySelected->getPlaneRoleListSize(column) == 0) {
									if (allCountries) {
										for (auto& country : *countryList) {
											Plane plane = Plane::generateRandomPlane(static_cast<PlaneRole::Role>(column));
											plane.iconName = Icon::GetInstance()->getPlaneIcon(plane);
											country.setNewUnits(unitType, plane);
										}
									}
									else {
										Plane plane = Plane::generateRandomPlane(static_cast<PlaneRole::Role>(column));
										plane.iconName = Icon::GetInstance()->getPlaneIcon(plane);
										countrySelected->setNewUnits(unitType, plane);
									}
								}
							}
							else if (unitType == UnitType::Division) {
								unitTypeSelected = unitType;
								columnSelected = column;
							}
							windowsManagement->setTypeSubWindow(unitType, true);
							windowsManagement->setSubWindow("generate", false);
							windowsManagement->setSubWindow("designer", true);
						}
					}
					else {
						if (unitType == UnitType::Ship) {
							if (countrySelected->getShipHullListSize(column) == 0) {
								ImGui::Text("Not Created", row, column);
							}
							else {
								ImGui::Text("Not Implemented", row, column);
							}
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
							if (countrySelected->getPlaneRoleListSize(column) == 0) {
								ImGui::Text("Not Created", row, column);
							}
							else {
								ImGui::Text("Not Implemented", row, column);
							}
						}
					}
				}
				if (unitType == UnitType::Division) {
					ImGui::TableSetColumnIndex(iconsColNumber.find(unitType)->second);
					if (row == 0 && countrySelected->getDivisionListSize() == 0) {
						if (ImGui::Button("Add a division")) {
							icons.find(unitType)->second.push_back("Infantry");
							if (allCountries) {
								for (auto& country : *countryList) {
										Division division = Division::generateRandom();
										country.setNewUnits(unitType, division);
								}
							}
							else {
								Division division = Division::generateRandom();
								countrySelected->setNewUnits(unitType, division);
							}
							windowsManagement->setTypeSubWindow(unitType, true);
							windowsManagement->setSubWindow("generate", false);
							windowsManagement->setSubWindow("designer", true);
						}
					}
				}
			}
			ImGui::EndTable();
		}
		ImGui::SetCursorPosX(200.0f);
		ImGui::SetCursorPosY(center.y / 1.5f);
		if(unitType != UnitType::Division) {
			if (ImGui::BeginTable("table2", 2)) {
				for (int row = 0; row < 5; row++) {
					ImGui::TableNextRow();
					for (int column = 0; column < 2; column++) {
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
									unitTypeSelected = unitType;
									columnSelected = column + 4;
									if (countrySelected->getShipHullListSize(column + 4) == 0) {
										Ship ship = Ship::generateRandomShip(static_cast<Hull::Type>(column + 4));
										ship.iconName = Icon::GetInstance()->getShipIcon(ship);
										countrySelected->setNewUnits(unitType, ship);
									}
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
									unitTypeSelected = unitType;
									columnSelected = column + 3;
									if (countrySelected->getPlaneRoleListSize(column + 3) == 0) {
										Plane plane = Plane::generateRandomPlane(static_cast<PlaneRole::Role>(column + 3));
										plane.iconName = Icon::GetInstance()->getPlaneIcon(plane);
										countrySelected->setNewUnits(unitType, plane);
									}
								}
								windowsManagement->setTypeSubWindow(unitType, true);
								windowsManagement->setSubWindow("generate", false);
								windowsManagement->setSubWindow("designer", true);
							}
						}
						else {
							if (unitType == UnitType::Ship) {
								if (countrySelected->getShipHullListSize(column + 4) == 0) {
									ImGui::Text("Not Created", row, column);
								}
								else {
									ImGui::Text("Not Implemented", row, column);
								}
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
								if (countrySelected->getPlaneRoleListSize(column + 3) == 0) {
									ImGui::Text("Not Created", row, column);
								}
								else {
									ImGui::Text("Not Implemented", row, column);
								}
							}
						}
					}
				}
				ImGui::EndTable();
			}
		}
		ImGui::PopFont();
	}
	else if (window == "import") {
		renderImportWindow(unitType);
	}
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

//Ship Designer
void renderShipDesignerWindows() {
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];
	//TODO Set Proper Ship background
	Texture texture = Icon::GetInstance()->getTankModulesTextures("background", "tank_designer_bg");
	ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));

	setImage(Constant::TextPos::TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "ship_name_bg", UnitType::Type::Ship);

	setImage(105, 90, "background", "ship_icon_bg", UnitType::Type::Ship);

	setImage(Constant::TextPos::TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 275.0f, "background", "ship_name_bg", UnitType::Type::Ship);

	for (int i = 0; i <= 6; i++) {
		float x = ImGui::GetCursorPosX() + (76 * i) + (12.0f - (i * 3));
		if (i == 0) {
			x = 21.0f;
		}
		setImage(Constant::TextPos::TANK_MODULE_HEIGHT, x, "background", "equipment_icon_bg", UnitType::Type::Ship);
	}

	setImage(ImGui::GetCursorPosY() - 4.0f, ImGui::GetCursorPosX() + 15.0f, "background", "ship_view_bg", UnitType::Type::Ship);

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
	createTitleWithPosition("Base Stats", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 45.0f);
	createTitleWithPosition("Combat Stats", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 45.0f);
	createTitleWithPosition("Misc. Stats", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 45.0f);
	ImGui::PopFont();

	//Base Stats 
	ImGui::PushFont(statsFont);
	createTitleWithPosition("Max Speed:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 75.0f);
	createTitleWithPosition("Max Range:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 95.0f);
	createTitleWithPosition("Organization:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 115.0f);
	createTitleWithPosition("HP:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 135.0f);
	createTitleWithPosition("Reliability:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 155.0f);
	createTitleWithPosition("Supply Use:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 175.0f);
	createTitleWithPosition("Manpower:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 195.0f);
	//Base Stats 

	//Combat Stats 
	createTitleWithPosition("Light attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 75.0f);
	createTitleWithPosition("Light Piercing:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 95.0f);
	createTitleWithPosition("Hard Attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 115.0f);
	createTitleWithPosition("Hard Piercing:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 135.0f);
	createTitleWithPosition("Torpedo Attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 155.0f);
	createTitleWithPosition("Breakthrough:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 175.0f);
	createTitleWithPosition("Depth Charges:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 195.0f);
	createTitleWithPosition("Armor:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 215.0f);
	createTitleWithPosition("Anti-Air:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 235.0f);
	//Combat Stats

	//Misc. Stats
	createTitleWithPosition("Fuel Usage:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 75.0f);
	createTitleWithPosition("Surface Visibility:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 95.0f);
	createTitleWithPosition("Surface Detection:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 115.0f);
	createTitleWithPosition("Sub Visibility:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 135.0f);
	createTitleWithPosition("Sub Detection:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 155.0f);
	createTitleWithPosition("Minelaying:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 175.0f);
	createTitleWithPosition("Minesweeping:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 195.0f);
	//Misc. Stats

	ImGui::PopFont();
	ImGui::PopStyleColor();

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
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];
	//TODO Get proper plane background
	Texture texture = Icon::GetInstance()->getTankModulesTextures("background", "tank_designer_bg");
	ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
	setImage(Constant::TextPos::TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "tank_name_bg", UnitType::Type::Plane);

	setImage(95.0f, 329, "background", "tank_icon_bg", UnitType::Type::Tank);

	setImage(Constant::TextPos::TANK_ROLE_HEIGHT + 5.0f, ImGui::GetCursorPosX() + 20.0f, "background", "tank_role_bg", UnitType::Type::Plane);

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
	createTitleWithPosition("Base Stats", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 45.0f);
	createTitleWithPosition("Combat Stats", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 45.0f);
	createTitleWithPosition("Misc. Stats", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 45.0f);
	ImGui::PopFont();

	//Base Stats 
	ImGui::PushFont(statsFont);
	createTitleWithPosition("Max Speed:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 75.0f);
	createTitleWithPosition("Range:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 95.0f);
	createTitleWithPosition("Supply Use:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 115.0f);
	createTitleWithPosition("Weight:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 135.0f);
	createTitleWithPosition("Thrust:", Constant::Position::MIDDLE + 60.0f, Constant::TextPos::TITLE_HEIGHT + 155.0f);
	//Base Stats 

	//Combat Stats 
	createTitleWithPosition("Air Defense:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 75.0f);
	createTitleWithPosition("Air Attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 95.0f);
	createTitleWithPosition("Agility:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 115.0f);
	createTitleWithPosition("Air Supperiority:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 135.0f);
	createTitleWithPosition("Naval Attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 155.0f);
	createTitleWithPosition("Naval Targeting:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 175.0f);
	createTitleWithPosition("Ground Attack:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 195.0f);
	createTitleWithPosition("Strat. Bombing:", Constant::Position::MIDDLE + 235.0f, Constant::TextPos::TITLE_HEIGHT + 215.0f);
	//Combat Stats

	//Misc. Stats
	createTitleWithPosition("Reliability:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 75.0f);
	createTitleWithPosition("Fuel Usage:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 95.0f);
	createTitleWithPosition("Surface Detection:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 115.0f);
	createTitleWithPosition("Sub Detection:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 135.0f);
	createTitleWithPosition("Night Penalty:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 155.0f);
	createTitleWithPosition("Minelaying:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 175.0f);
	createTitleWithPosition("Minesweeping:", Constant::Position::MIDDLE + 410.0f, Constant::TextPos::TITLE_HEIGHT + 195.0f);
	//Misc. Stats

	ImGui::PopFont();
	ImGui::PopStyleColor();
}

void renderUnitDesignerWindows() {
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];
	setImage(ImGui::GetCursorPosY(), ImGui::GetCursorPosX(), "Background", "division_designer_popup_bg", UnitType::Type::Division);

	for (int i = 0; i <= 4; i++) {
		setImage(250 + (i * 51), 32, "Background", "div_subunit_item_bg", UnitType::Type::Division);
	}

	for (int col = 0; col <= 4; col++) {
		for (int row = 0; row <= 4; row++) {
			setImage(250 + (row * 51), 111 + (86 * col), "Background", "div_unit_item_bg", UnitType::Type::Division);
		}
	}
}

//Ship stats
void renderUnit(Ship ship) {
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[2];
	ImFont* statsFont = io.Fonts->Fonts[4];

	ImGui::PushFont(basicFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	std::string string = std::format("{0} {1}", ShipVersion::versionToYear(ship.version), ShipType::shipTypeToString(ship.type).c_str());
	createTitleWithPosition(string.c_str(), ImGui::GetCursorPosX() + 30.0f, 75);

	setIcon(ImGui::GetCursorPosY(), ImGui::GetCursorPosX() + 100.0f, Hull::typeToString(ship.hull), ship.iconName, UnitType::Type::Ship);

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

	ImGui::PopFont();
	ImGui::PopStyleColor();
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
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[2];
	ImFont* statsFont = io.Fonts->Fonts[4];

	ImGui::PushFont(basicFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	std::string string = std::format("{0} {1}", PlaneVersion::versionToYear(plane.version), PlaneRole::roleToString(plane.role).c_str());
	createTitleWithPosition(string.c_str(), 35.0f, Constant::TextPos::TANK_NAME_HEIGHT + 5.0f);

	setIcon(ImGui::GetCursorPosY() - 20.0f, ImGui::GetCursorPosX() + 325.0f, PlaneType::typeToString(plane.type), plane.iconName, UnitType::Type::Plane);

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
	setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f, ImGui::GetCursorPosX() + 10.0f, "modules", fileName, UnitType::Type::Plane);

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

void renderUnit(Division* division) {
	ImGui::SetCursorPosY(80);
	ImGui::SetCursorPosX(32);
	std::cout << division->name << std::endl;
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	ImGui::InputText("##", &division->name);
	ImGui::PopStyleColor();
	if (division->support.size() >= 1) {
		for (int i = 0; i < division->support.size(); i++) {
			setImage(265 + (i * 51), 32, "Supports", UnitSubType::supportTypeToImageString(division->support[i].unitSubType), UnitType::Type::Division);
		}
	}

	for (int col = 0; col < division->regimentList.size(); col++) {
		for (int row = 0; row < division->regimentList[col].size(); row++) {
			setImage(260 + (row * 51), 111 + (86 * col), RegimentType::regimentTypeToFolderString(division->regimentList[col][row].regimentType), UnitSubType::typeToImageString(division->regimentList[col][row].unitSubType), UnitType::Type::Division);
		}
	}
}

void renderOptionsSubWindow() {
	Settings *settings = Settings::getInstance();
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
	ImGui::PopFont();

	if (window == "generate" || window == "import") {
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
		ImGui::SameLine();
		ImGui::Checkbox("All Countries", &allCountries);
	}

	if (window == "generate" || window == "import") {
		renderGenerateImportSubWindow();
	}
	else if (window == "multiplayer") {
		std::string text = "Not Done";
		createLabelWithPosition(text.c_str(), (float)center.x / 2.0f, (float)center.y / 2.0f);
	}
	else if (window == "options") {
		renderOptionsSubWindow();
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
			renderUnit(countrySelected->getPlaneByRole(columnSelected));
			break;
		case UnitType::Division:
			renderUnitDesignerWindows();
			renderUnit(countrySelected->getDivisionByIndex(columnSelected));
		default:
			break;
		}
		if (createButtonWithPos("Back", center.x / 3, 575.0f)) {
			windowsManagement->setSubWindow("generate", true);
			windowsManagement->setSubWindow("designer", false);
		}
		if (createButtonWithPos("Regenerate", center.x / 2, 575.0f)) {
			if (unitType == UnitType::Ship) {
				Ship ship = Ship::generateRandomShip(static_cast<Hull::Type>(columnSelected));
				ship.iconName = Icon::GetInstance()->getShipIcon(ship);
				countrySelected->setNewUnits(unitType, ship);
			}
			else if (unitType == UnitType::Tank) {
				Tank tank = Tank::generateRandomTank(static_cast<TankType::Type>(columnSelected));
				tank.iconName = Icon::GetInstance()->getRandomIcon(tank.type);
				countrySelected->setNewUnits(unitType, tank);
			}
			else if (unitType == UnitType::Plane) {
				Plane plane = Plane::generateRandomPlane(static_cast<PlaneRole::Role>(columnSelected));
				plane.iconName = Icon::GetInstance()->getPlaneIcon(plane);
				countrySelected->setNewUnits(unitType, plane);
			}
			else if (unitType == UnitType::Division) {
				Division division = Division::generateRandom();
				countrySelected->setNewUnits(unitType, division, columnSelected);
			}
		}
	}
	ImGui::PopStyleColor();
}