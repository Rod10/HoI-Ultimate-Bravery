#include "renderer.hpp"

ImVec2 Renderer::getBlockSize() {
	const int windowHeightSize = ImGui::GetIO().DisplaySize.y;
	const int windowWidthSize = ImGui::GetIO().DisplaySize.x;

	const float mainBlocHeightSize = windowHeightSize - ((20 * windowHeightSize) / 100);
	const float mainBlocWidthtSize = windowWidthSize - ((10 * windowWidthSize) / 100);
	return ImVec2(mainBlocWidthtSize, mainBlocHeightSize);
}

ImVec2 Renderer::getButtonSize() {
	const ImVec2 blocSize = Renderer::getBlockSize();
	const float buttonHeight = (blocSize.y / 5) - ((5 * ((0.5 * blocSize.y) / 100)));
	const float buttonWidth = (blocSize.x / 3) - ((5 * blocSize.x) / 100);
	return ImVec2(buttonWidth, buttonHeight);
}

ImVec2 Renderer::getGenerateBlockSize() {
	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 buttonBlockSize = Renderer::getButtonSize();
	const float mainBlocWidthtMargin = (5 * mainBlockSize.x) / 100;
	return ImVec2(mainBlockSize.x - buttonBlockSize.x - mainBlocWidthtMargin, mainBlockSize.y);
}

ImVec2 getGenerateMargin() {
	const ImVec2 buttonBlockSize = Renderer::getButtonSize();
	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	const float testGenerateBlocWidthtMargin = (5 * mainBlockSize.x) / 100;
	const float mainBlocHeightMargin = (10 * mainBlockSize.y) / 100;
	const float testGenerateBlocHeightMargin = ((5 * generateBlockSize.y) / 100) + mainBlocHeightMargin;
	return ImVec2(buttonBlockSize.x + (testGenerateBlocWidthtMargin * 2), testGenerateBlocHeightMargin);
}

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

void setIcon(float x, float y, ImVec2 ratio, std::string type, std::string name, UnitType::Type unitType) {
	ImGui::SetCursorPosY(y);
	ImGui::SetCursorPosX(x);
	if (unitType == UnitType::Type::Tank) {
		Texture texture = Icon::GetInstance()->getTankIconTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width * ratio.x, texture.my_image_height * ratio.y));
	}
	else if (unitType == UnitType::Type::Ship) {
		Texture texture = Icon::GetInstance()->getShipIconTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width * ratio.x, texture.my_image_height * ratio.y));
	}
	else if (unitType == UnitType::Type::Plane) {
		Texture texture = Icon::GetInstance()->getPlaneIconTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width * ratio.x, texture.my_image_height * ratio.y));
	}
}

void setImage(float x, float y, std::string type, std::string name, UnitType::Type unitType) {
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

void setImage(float x, float y, ImVec2 ratio, std::string type, std::string name, UnitType::Type unitType) {
	ImGui::SetCursorPosY(y);
	ImGui::SetCursorPosX(x);
	if (unitType == UnitType::Type::Tank) {
		Texture texture = Icon::GetInstance()->getTankModulesTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width * ratio.x, texture.my_image_height * ratio.y));
	}
	else if (unitType == UnitType::Type::Ship) {
		Texture texture = Icon::GetInstance()->getShipModulesTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width * ratio.x, texture.my_image_height * ratio.y));
	}
	else if (unitType == UnitType::Type::Plane) {
		Texture texture = Icon::GetInstance()->getPlaneModulesTextures(type, name);
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width * ratio.x, texture.my_image_height * ratio.y));
	}
	else if (unitType == UnitType::Type::Division) {
		Texture texture = Icon::GetInstance()->getUnitsTextures(type, name);
		if (type != "Background") {
			texture.my_image_height = texture.my_image_height * 0.90;
			texture.my_image_width = texture.my_image_width * 0.90;
		}
		ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width * ratio.x, texture.my_image_height * ratio.y));
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

float calculateTextLenght(const char* label) {
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x / 2.0f;
	return size;
}

bool createButtonWithSize(const char* label, ImVec2 size) {
	ImGuiStyle& style = ImGui::GetStyle();
	const auto test = Renderer::getButtonSize();
	return ImGui::Button(label, test);
}

bool createButtonWithoutSize(const char* label) {
	ImGuiStyle& style = ImGui::GetStyle();
	const auto size = Renderer::getButtonSize();
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

/* void createLabelWithPosition(const char* label, float position, float height) {
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * (position / 1000.f);
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

	ImGui::SetCursorPosY(height);
	return ImGui::Text(label);
}*/

void createLabelWithPosition(const char* label, float x, float y, bool center = false) {
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x;
	if (center) {
		size = ImGui::CalcTextSize(label).x / 2.0f;

		float off = x - size;
		if (off > 0.0f)
			ImGui::SetCursorPosX(off);
	}
	else {
		ImGui::SetCursorPosX(x);
	}

	ImGui::SetCursorPosY(y);
	return ImGui::Text(label);
}

/* void createLabelWithPosition(const char* label, float position)
{
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
	float avail = ImGui::GetContentRegionAvail().x;

	float off = (avail - size) * (position / 1000.f);
	if (off > 0.0f)
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

	return ImGui::Text(label);
}*/

void createLabelWithPosition(const char* label, float position)
{
	ImGuiStyle& style = ImGui::GetStyle();

	float size = ImGui::CalcTextSize(label).x / 2.0f;

	float off = position - size;
	if (off > 0.0f)
		ImGui::SetCursorPosX(off);

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

void renderMainMenuButtonBlock() {
	auto windowsManagement = WindowsManagement::GetInstance();
	Settings* settings = Settings::getInstance();
	if (createButtonWithoutSize("Generate")) {
		windowsManagement->setButtons("mainMenu", false);
		windowsManagement->setButtons("generate", true);
		windowsManagement->setSubWindow("generate", true);
	}
	if (createButtonWithoutSize("Import")) {
		windowsManagement->setButtons("mainMenu", false);
		windowsManagement->setButtons("import", true);
		windowsManagement->setSubWindow("import", true);
	}
	if (createButtonWithoutSize("Multiplayer")) {
		windowsManagement->setButtons("mainMenu", false);
		windowsManagement->setButtons("multiplayer", true);
		windowsManagement->setSubWindow("multiplayer", true);
	}
	if (createButtonWithoutSize("Options")) {
		windowsManagement->setButtons("mainMenu", false);
		windowsManagement->setButtons("options", true);
		windowsManagement->setSubWindow("options", true);
	}
	if (createButtonWithoutSize("Quit")) {
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

void Renderer::renderButtonBlock()
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
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	if (window == "mainMenu") {
		renderMainMenuButtonBlock();
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
	ImGui::PopStyleColor();
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
	// TODO: Center column content
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

	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	const ImVec2 generateMargin = getGenerateMargin();
	const float mainBlocHeightMargin = (10 * mainBlockSize.y) / 100;
	const float firstRowWidth = generateBlockSize.x - ((10 * generateBlockSize.x) / 100);
	const float firstRowMargin = (5 * generateBlockSize.x) / 100;
	const float firstRowHeightMargin = (10 * generateBlockSize.x) / 100;
	const float firstRowCenter = (50 * generateBlockSize.x) / 100;

	ImGui::SetCursorPosX(firstRowMargin);

	if (window == "generate") {
		ImGui::PushFont(statsFont);
		ImGui::PushItemWidth(firstRowWidth);
		if (ImGui::BeginTable("table1", 3, ImGuiTableFlags_SizingStretchSame)) {
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
		ImGui::PopItemWidth();
		ImGui::SetCursorPosX((50 * firstRowCenter) / 100);
		ImGui::SetCursorPosY(center.y / 1.5f);
		if(unitType != UnitType::Division) {
			if (ImGui::BeginTable("table2", 2, ImGuiTableFlags_SizingStretchSame)) {
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

void renderStat(UnitType::Type type) {
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];

	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	const auto generateBlockMargin = getGenerateMargin();

	const float backgroundWidth = generateBlockSize.x - ((10.0f * generateBlockSize.x) / 100);
	const float backgroundHeight = generateBlockSize.y - ((10.0f * generateBlockSize.y) / 100);
	const float backgroundXMargin = (5.0f * generateBlockSize.x) / 100;
	const float backgroundYMargin = (5.0f * generateBlockSize.y) / 100;

	std::vector < std::string > baseShipStatsList = { "Max Speed:", "Max Range:", "Organization:", "HP:", "Reliability:", "Supply Use:", "Manpower:" };
	std::vector < std::string > combatShipStatsList = { "Light attack:", "Light Piercing:", "Hard Attack:", "Hard Piercing:", "Torpedo Attack:", "Breakthrough:", "Depth Charges:", "Armor:", "Anti-Air:" };
	std::vector < std::string > miscShipStatsList = { "Fuel Usage:", "Surface Visibility:", "Surface Detection:", "Sub Visibility:", "Sub Detection:", "Minelaying:", "Minesweeping:" };
	std::vector < std::string > baseTankStatsList = { "Max Speed:", "Reliability:", "Supply Use:"};
	std::vector < std::string > combaTankStatsList = { "Soft attack:", "Hard attack:", "Piercing:", "Hardness:", "Armor:", "Breakthrough:", "Defense:", "Air attack:", };
	std::vector < std::string > miscTankStatsList = { "Fuel Capacity:", "Fuel Usage:", "Suppression:", "Reconnaissance:", "Entrenchment:", };
	std::vector < std::string > basePlaneStatsList = { "Max Speed:", "Range:", "Supply Use:", "Weight:", "Thrust:", };
	std::vector < std::string > combatPlaneStatsList = { "Air Defense:", "Air Attack:", "Agility:", "Air Supperiority:", "Naval Attack:", "Naval Targeting:", "Ground Attack:", "Strat. Bombing:", };
	std::vector < std::string > miscPlaneStatsList = { "Reliability:", "Fuel Usage:", "Surface Detection:", "Sub Detection:", "Night Penalty:", "Minelaying:", "Minesweeping:", };

	std::map <Stats::Type, std::vector < std::string >> shipStat = {
		{Stats::Type::Base, baseShipStatsList},
		{Stats::Type::Combat, combatShipStatsList},
		{Stats::Type::Misc, miscShipStatsList},
	};

	std::map <Stats::Type, std::vector < std::string >> tankStat = {
		{Stats::Type::Base, baseTankStatsList},
		{Stats::Type::Combat, combaTankStatsList},
		{Stats::Type::Misc, miscTankStatsList},
	};

	std::map <Stats::Type, std::vector < std::string >> planeStat = {
		{Stats::Type::Base, basePlaneStatsList},
		{Stats::Type::Combat, combatPlaneStatsList},
		{Stats::Type::Misc, miscPlaneStatsList},
	};

	std::map < UnitType::Type, std::map <Stats::Type, std::vector < std::string >> > unitStats = {
		{UnitType::Ship, shipStat},
		{UnitType::Tank, tankStat},
		{UnitType::Plane, planeStat},
	};

	ImGui::PushFont(TitleStatsFont);
	createTitleWithPosition("Base Stats", (51.0f * generateBlockSize.x) / 100, (13.0f * generateBlockSize.y) / 100);
	createTitleWithPosition("Combat Stats", (65.0f * generateBlockSize.x) / 100, (13.0f * generateBlockSize.y) / 100);
	createTitleWithPosition("Misc. Stats", (79.0f * generateBlockSize.x) / 100, (13.0f * generateBlockSize.y) / 100);
	ImGui::PopFont();

	ImGui::PushFont(statsFont);
	for (auto& [type, stats] : unitStats.find(type)->second) {
		float baseYPos = 18.0f;
		float baseXPos;
		for (auto& stat : stats) {
			if (type == Stats::Type::Base) {
				baseXPos = 51.0f;
			}
			else if (type == Stats::Type::Combat) {
				baseXPos = 65.0f;
			}
			else if (type == Stats::Type::Misc) {
				baseXPos = 79.0f;
			}
			createTitleWithPosition(stat.c_str(), (baseXPos * generateBlockSize.x) / 100, (baseYPos * generateBlockSize.y) / 100);
			baseYPos += 3.1f;
		}
	}
	ImGui::PopFont();

}

//Ship Designer
void renderShipDesignerWindows() {
	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	const auto generateBlockMargin = getGenerateMargin();

	const float backgroundWidth = generateBlockSize.x - ((10.0f * generateBlockSize.x) / 100);
	const float backgroundHeight = generateBlockSize.y - ((10.0f * generateBlockSize.y) / 100);
	const float backgroundXMargin = (5.0f * generateBlockSize.x) / 100;
	const float backgroundYMargin = (5.0f * generateBlockSize.y) / 100;

	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];
	Texture texture = Icon::GetInstance()->getTankModulesTextures("background", "tank_designer_bg");
	const float newRatioWidth = backgroundWidth / texture.my_image_width;
	const float newRatioHeight = backgroundHeight / texture.my_image_height;
	newRatio = ImVec2(newRatioWidth, newRatioHeight);

	ImGui::SetCursorPosX(backgroundXMargin);
	ImGui::SetCursorPosY(backgroundYMargin);
	ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(backgroundWidth, backgroundHeight));

	setImage((6.2f * generateBlockSize.x) / 100, (13.5f * generateBlockSize.y) / 100, newRatio, "background", "ship_name_bg", UnitType::Type::Ship);

	setImage((32.5f * generateBlockSize.x) / 100, (16.5f * generateBlockSize.y) / 100, newRatio, "background", "ship_icon_bg", UnitType::Type::Ship);

	setImage((6.2f * generateBlockSize.x) / 100, (21.0f * generateBlockSize.y) / 100, newRatio, "background", "ship_name_bg", UnitType::Type::Ship);

	for (int i = 1; i <= 7; i++) {
		float x = ((6.2f * generateBlockSize.x) / 100) * i;
		setImage(x, (29.0f * generateBlockSize.y) / 100, newRatio, "background", "equipment_icon_bg", UnitType::Type::Ship);
	}

	setImage((6.2f * generateBlockSize.x) / 100, (37.0f * generateBlockSize.y) / 100, newRatio, "background", "ship_view_bg", UnitType::Type::Ship);

	for (int i = 1; i <= 7; i++) {
		float x = ((6.2f * generateBlockSize.x) / 100) * i;
		setImage(x, (77.6f * generateBlockSize.y) / 100, newRatio, "background", "equipment_icon_bg", UnitType::Type::Ship);
	}

	renderStat(UnitType::Ship);
}

//Tank Designer
void renderTankDesignerWindows() {
	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	const auto generateBlockMargin = getGenerateMargin();

	const float backgroundWidth = generateBlockSize.x - ((10.0f * generateBlockSize.x) / 100);
	const float backgroundHeight = generateBlockSize.y - ((10.0f * generateBlockSize.y) / 100);
	const float backgroundXMargin = (5.0f * generateBlockSize.x) / 100;
	const float backgroundYMargin = (5.0f * generateBlockSize.y) / 100;

	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];
	Texture texture = Icon::GetInstance()->getTankModulesTextures("background", "tank_designer_bg");
	const float newRatioWidth = backgroundWidth / texture.my_image_width;
	const float newRatioHeight = backgroundHeight / texture.my_image_height;
	newRatio = ImVec2(newRatioWidth, newRatioHeight);

	ImGui::SetCursorPosX(backgroundXMargin);
	ImGui::SetCursorPosY(backgroundYMargin);
	ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(backgroundWidth, backgroundHeight));

	setImage((6.2f * generateBlockSize.x) / 100, (13.5f * generateBlockSize.y) / 100, newRatio, "background", "tank_name_bg", UnitType::Type::Tank);

	setImage((32.5f * generateBlockSize.x) / 100, (16.5f * generateBlockSize.y) / 100, newRatio, "background", "tank_icon_bg", UnitType::Type::Tank);

	setImage((6.2f * generateBlockSize.x) / 100, (21.0f * generateBlockSize.y) / 100, newRatio, "background", "tank_role_bg", UnitType::Type::Tank);

	for (int i = 1; i <= 6; i++) {
		float x = ((6.2f * generateBlockSize.x) / 100) * i;
		setImage(x, (29.0f * generateBlockSize.y) / 100, newRatio, "background", "equipment_icon_bg", UnitType::Type::Tank);
	}

	setImage((6.2f * generateBlockSize.x) / 100, (37.0f * generateBlockSize.y) / 100, newRatio, "background", "tank_blueprint_background", UnitType::Type::Tank);

	for (int i = 1; i <= 3; i++) {
		float x = ((6.2f * generateBlockSize.x) / 100) * i;
		setImage(x, (77.6f * generateBlockSize.y) / 100, newRatio, "background", "equipment_icon_bg", UnitType::Type::Tank);
	}

	renderStat(UnitType::Tank);

	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
	ImGui::PushFont(textFont);
	createTitleWithPosition("Engine", (30.0f * generateBlockSize.x) / 100, (77.6f * generateBlockSize.y) / 100);
	createTitleWithPosition("Armor", (40.0f * generateBlockSize.x) / 100, (77.6f * generateBlockSize.y) / 100);
	ImGui::PopFont();
	ImGui::PopStyleColor();
}

//Plane Designer
void renderPlaneDesignerWindows() {
	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	const auto generateBlockMargin = getGenerateMargin();

	const float backgroundWidth = generateBlockSize.x - ((10.0f * generateBlockSize.x) / 100);
	const float backgroundHeight = generateBlockSize.y - ((10.0f * generateBlockSize.y) / 100);
	const float backgroundXMargin = (5.0f * generateBlockSize.x) / 100;
	const float backgroundYMargin = (5.0f * generateBlockSize.y) / 100;

	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];
	Texture texture = Icon::GetInstance()->getTankModulesTextures("background", "tank_designer_bg");
	const float newRatioWidth = backgroundWidth / texture.my_image_width;
	const float newRatioHeight = backgroundHeight / texture.my_image_height;
	newRatio = ImVec2(newRatioWidth, newRatioHeight);

	ImGui::SetCursorPosX(backgroundXMargin);
	ImGui::SetCursorPosY(backgroundYMargin);
	ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(backgroundWidth, backgroundHeight));

	setImage((6.2f * generateBlockSize.x) / 100, (13.5f * generateBlockSize.y) / 100, newRatio, "background", "tank_name_bg", UnitType::Type::Plane);

	setImage((32.5f * generateBlockSize.x) / 100, (16.5f * generateBlockSize.y) / 100, newRatio, "background", "tank_icon_bg", UnitType::Type::Plane);

	setImage((6.2f * generateBlockSize.x) / 100, (21.0f * generateBlockSize.y) / 100, newRatio, "background", "tank_role_bg", UnitType::Type::Plane);

	for (int i = 1; i <= 5; i++) {
		float x = ((6.2f * generateBlockSize.x) / 100) * i;
		setImage(x, (29.0f * generateBlockSize.y) / 100, newRatio, "background", "equipment_icon_bg", UnitType::Type::Plane);
	}

	setImage((6.2f * generateBlockSize.x) / 100, (37.0f * generateBlockSize.y) / 100, newRatio, "background", "plane_view_bg", UnitType::Type::Plane);

	for (int i = 1; i <= 7; i++) {
		float x = ((6.2f * generateBlockSize.x) / 100) * i;
		setImage(x, (77.6f * generateBlockSize.y) / 100, newRatio, "background", "equipment_icon_bg", UnitType::Type::Plane);
	}

	renderStat(UnitType::Plane);
}

void renderUnitDesignerWindows() {
	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	const auto generateBlockMargin = getGenerateMargin();

	const float backgroundWidth = generateBlockSize.x - ((10.0f * generateBlockSize.x) / 100);
	const float backgroundHeight = generateBlockSize.y - ((10.0f * generateBlockSize.y) / 100);
	const float backgroundXMargin = (5.0f * generateBlockSize.x) / 100;
	const float backgroundYMargin = (5.0f * generateBlockSize.y) / 100;

	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[0];
	ImFont* titleFont = io.Fonts->Fonts[1];
	ImFont* textFont = io.Fonts->Fonts[2];
	ImFont* TitleStatsFont = io.Fonts->Fonts[3];
	ImFont* statsFont = io.Fonts->Fonts[4];
	Texture texture = Icon::GetInstance()->getUnitsTextures("Background", "division_designer_popup_bg");
	const float newRatioWidth = backgroundWidth / texture.my_image_width;
	const float newRatioHeight = backgroundHeight / texture.my_image_height;
	newRatio = ImVec2(newRatioWidth, newRatioHeight);

	ImGui::SetCursorPosX(backgroundXMargin);
	ImGui::SetCursorPosY(backgroundYMargin);
	ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(backgroundWidth, backgroundHeight));

	for (int i = 0; i <= 4; i++) {
		setImage((7.0f * generateBlockSize.x) / 100, ((42.0f + (i * 8.1f)) * generateBlockSize.y) / 100, newRatio, "Background", "div_subunit_item_bg", UnitType::Type::Division);
	}

	for (int col = 0; col <= 4; col++) {
		for (int row = 0; row <= 4; row++) {
			setImage(((14.0f + (col * 6.9f)) * generateBlockSize.x) / 100, ((42.0f + (row * 8.1f)) * generateBlockSize.y) / 100, newRatio, "Background", "div_unit_item_bg", UnitType::Type::Division);
		}
	}
}

//Ship stats
void renderUnit(Ship ship) {
	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	const auto generateBlockMargin = getGenerateMargin();

	//auto& [tank, tankStats] = unit;
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[2];
	ImFont* statsFont = io.Fonts->Fonts[4];

	ImGui::PushFont(basicFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
	ImGui::SetCursorPosX((7.0f * generateBlockSize.x) / 100);
	ImGui::SetCursorPosY((15.5f * generateBlockSize.y) / 100);
	std::string string = std::format("{0} {1}", ShipVersion::versionToYear(ship.version), ShipType::shipTypeToString(ship.type).c_str());
	ImGui::InputText("##", &string);
	ImGui::PopStyleColor();
	ImGui::PopFont();

	setIcon((15.0f * generateBlockSize.x) / 100, (7.0f * generateBlockSize.y) / 100, Hull::typeToString(ship.hull), ship.iconName, UnitType::Type::Ship);

	int index = 0;
	for (auto& module : ship.customModule) {
		std::string fileName;
		if (module.type == Module::None) {
			fileName = "none";
		}
		else {
			fileName = std::format("{0}_{1}", Module::typeToImagesString(module.type, module.subType, ship.type), (module.version + 1));
		}
		setImage(((6.0f + (6.0f * index)) * generateBlockSize.x) / 100, (29.25f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Ship);
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
		setImage(((6.0f + (6.0f * index)) * generateBlockSize.x) / 100, (77.6f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Ship);
		index++;
	}
}

//Tank stats
void renderUnit(std::tuple<Tank, TankStats> unit) {
	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	const auto generateBlockMargin = getGenerateMargin();

	auto& [tank, tankStats] = unit;
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[2];
	ImFont* statsFont = io.Fonts->Fonts[4];

	ImGui::PushFont(basicFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
	ImGui::SetCursorPosX((7.0f * generateBlockSize.x) / 100);
	ImGui::SetCursorPosY((15.5f * generateBlockSize.y) / 100);
	std::string tankName = std::format("{0} {1}", Tank::tankVersionToString(tank.version).c_str(), Tank::tankTypeToString(tank.type).c_str());
	if (ImGui::InputText("##", &tank.name)) {
		std::cout << tank.name << std::endl;
		countrySelected->setTankName(tank.type, tank.name);
	}
	ImGui::PopStyleColor();
	
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));

	createLabelWithPosition(Role::typeToString(tank.role).c_str(), (7.0f * generateBlockSize.x) / 100, (23.0f * generateBlockSize.y) / 100);

	setIcon((32.5f * generateBlockSize.x) / 100, (16.5f * generateBlockSize.y) / 100, newRatio, Tank::tankTypeToString(tank.type), tank.iconName, UnitType::Type::Tank);

	std::string fileName = std::format("{0}_{1}", Gun::gunNameToString(tank.gun.name), Gun::typeToString(tank.gun.type));
	setImage((7.0f * generateBlockSize.x) / 100, (29.0f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}_turret_{1}", TurretType::turretTypeToString(tank.turret.type), tank.turret.crew);
	setImage((12.7f * generateBlockSize.x) / 100, (29.0f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[0].type));
	setImage((19.25f * generateBlockSize.x) / 100, (29.0f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[1].type));
	setImage((25.75f * generateBlockSize.x) / 100, (29.0f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[2].type));
	setImage((31.5f * generateBlockSize.x) / 100, (29.0f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[3].type));
	setImage((37.75f * generateBlockSize.x) / 100, (29.0f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Tank);

	setImage((6.2f * generateBlockSize.x) / 100, (29.0f * generateBlockSize.y) / 100, newRatio, "blueprint", std::format("ger_{0}_tank_blueprint", Tank::tankTypeToString(tank.type)), UnitType::Type::Tank);

	fileName = std::format("{0}", Suspension::typeToString(tank.suspension.type));
	setImage((7.0f * generateBlockSize.x) / 100, (77.6f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", Armor::typeToString(tank.armor.type));
	setImage((12.7f * generateBlockSize.x) / 100, (77.6f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Tank);

	fileName = std::format("{0}", Engine::typeToString(tank.engine.type));
	setImage((19.0f * generateBlockSize.x) / 100, (77.6f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Tank);

	createLabelWithPosition(std::to_string(tank.engineLevel).c_str(), (32.0f * generateBlockSize.x) / 100, (80.5f * generateBlockSize.y) / 100);
	createLabelWithPosition(std::to_string(tank.armorLevel).c_str(), (42.0f * generateBlockSize.x) / 100, (80.5f * generateBlockSize.y) / 100);
	ImGui::PopStyleColor();
	ImGui::PopFont();

	ImGui::PushFont(statsFont);
	//Base stats
	std::string speed = std::format("{:.1f} km/h", tankStats.speed);
	createLabelWithPosition(speed.c_str(), (59.0f * generateBlockSize.x) / 100, (18.0f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "speed");

	std::string reliability = std::format("{:.1f} %%", tankStats.reliability);
	createLabelWithPosition(reliability.c_str(), (60.5f * generateBlockSize.x) / 100, (21.2f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "reliability");

	std::string supplyUse = std::format("{:.2f}", tankStats.supplyUse);
	createLabelWithPosition(supplyUse.c_str(), (61.5f * generateBlockSize.x) / 100, (24.3f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "supplyUse");
	//Base stats

	//Combat stats
	std::string softAttack = std::format("{:.2f}", tankStats.softAttack);
	createLabelWithPosition(softAttack.c_str(), (75.75f * generateBlockSize.x) / 100, (18.0f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "softAttack");

	std::string hardAttack = std::format("{:.2f}", tankStats.hardAttack);
	createLabelWithPosition(hardAttack.c_str(), (75.75f * generateBlockSize.x) / 100, (21.2f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "hardAttack");

	std::string piercing = std::format("{:.2f}", tankStats.piercing);
	createLabelWithPosition(piercing.c_str(), (75.75f * generateBlockSize.x) / 100, (24.3f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "piercing");

	std::string hardness = std::format("{:.2f} %%", tankStats.hardnessP);
	createLabelWithPosition(hardness.c_str(), (75.0f * generateBlockSize.x) / 100, (27.4f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "hardness");

	std::string armor = std::format("{:.2f}", tankStats.armor);
	createLabelWithPosition(armor.c_str(), (75.75f * generateBlockSize.x) / 100, (30.5f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "armor");

	std::string breakthrough = std::format("{:.2f}", tankStats.breakthrough);
	createLabelWithPosition(breakthrough.c_str(), (75.75f * generateBlockSize.x) / 100, (33.6f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "breakthrough");

	std::string defense = std::format("{:.2f}", tankStats.defense);
	createLabelWithPosition(defense.c_str(), (75.75f * generateBlockSize.x) / 100, (36.7f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "defense");

	std::string airAttack = std::format("{:.2f}", tankStats.airAttack);
	createLabelWithPosition(airAttack.c_str(), (75.75f * generateBlockSize.x) / 100, (39.8f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "airAttack");
	//Combat stats

	//Misc Stats
	std::string fuelCapacity = std::format("{:.2f}", tankStats.fuelCapacity);
	createLabelWithPosition(fuelCapacity.c_str(), (90.5f * generateBlockSize.x) / 100, (18.0f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "fuelCapacity");

	std::string fuelUsage = std::format("{:.2f}", tankStats.fuelUsage);
	createLabelWithPosition(fuelUsage.c_str(), (90.25f * generateBlockSize.x) / 100, (21.2f * generateBlockSize.y) / 100);
	Tooltip::renderTankTooltip(tank, "fuelUsage");

	//TODO research suppression value
	createLabelWithPosition("???", (90.25f * generateBlockSize.x) / 100, (24.3f * generateBlockSize.y) / 100);

	//TODO research reconnaissance value
	createLabelWithPosition("???", (90.25f * generateBlockSize.x) / 100, (27.4f * generateBlockSize.y) / 100);
	
	std::string entrenchment = std::format("{:.2f}", tankStats.entrenchment);
	createLabelWithPosition(entrenchment.c_str(), (90.25f * generateBlockSize.x) / 100, (30.5f * generateBlockSize.y) / 100);
	//Misc Stats
	ImGui::PopFont();
}

//Plane stats
void renderUnit(Plane plane) {
	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	const auto generateBlockMargin = getGenerateMargin();

	//auto& [tank, tankStats] = unit;
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[2];
	ImFont* statsFont = io.Fonts->Fonts[4];

	ImGui::PushFont(basicFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
	ImGui::SetCursorPosX((7.0f * generateBlockSize.x) / 100);
	ImGui::SetCursorPosY((15.5f * generateBlockSize.y) / 100);
	std::string string = std::format("{0} {1}", PlaneVersion::versionToYear(plane.version), PlaneRole::roleToString(plane.role).c_str());
	ImGui::InputText("##", &string);
	ImGui::PopStyleColor();
	ImGui::PopFont();

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
		setImage(((6.0f + (6.0f * index)) * generateBlockSize.x) / 100, (29.25f * generateBlockSize.y) / 100, newRatio, "modules", fileName, UnitType::Type::Plane);
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
}

void renderUnit(Division* division) {
	const ImVec2 mainBlockSize = Renderer::getBlockSize();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	const auto generateBlockMargin = getGenerateMargin();

	//auto& [tank, tankStats] = unit;
	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[2];
	ImFont* statsFont = io.Fonts->Fonts[4];

	ImGui::PushFont(basicFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
	ImGui::SetCursorPosX((7.0f * generateBlockSize.x) / 100);
	ImGui::SetCursorPosY((15.5f * generateBlockSize.y) / 100);
	ImGui::InputText("##", &division->name);
	ImGui::PopStyleColor();
	ImGui::PopFont();
	
	if (division->support.size() >= 1) {
		for (int i = 0; i < division->support.size(); i++) {
			setImage((7.0f * generateBlockSize.x) / 100, ((45.0f + (i * 8.1f)) * generateBlockSize.y) / 100, newRatio, "Supports", UnitSubType::supportTypeToImageString(division->support[i].unitSubType), UnitType::Type::Division);
		}
	}

	for (int col = 0; col < division->regimentList.size(); col++) {
		for (int row = 0; row < division->regimentList[col].size(); row++) {
			setImage(((14.0f + (col * 6.9f)) * generateBlockSize.x) / 100, ((44.75f + (row * 8.1f)) * generateBlockSize.y) / 100, newRatio, RegimentType::regimentTypeToFolderString(division->regimentList[col][row].regimentType), UnitSubType::typeToImageString(division->regimentList[col][row].unitSubType), UnitType::Type::Division);
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
	ImGuiStyle& style = ImGui::GetStyle();
	const ImVec2 generateBlockSize = Renderer::getGenerateBlockSize();
	std::string window;
	WindowsManagement* windowsManagement = WindowsManagement::GetInstance();
	for (auto& it : windowsManagement->getSubWindow()) {
		if (it.second == true) {
			window = it.first;
		}
	}

	///// TEST

	/*const ImVec4 testButtonColor = ImVec4(0.453f, 0.874f, 0.652f, 0.50f);
	const ImVec2 mainBlockSize = Renderer::getBlockSize();

	const ImVec2 buttonBlockSize = Renderer::getButtonSize();

	const float generateBlockXPos = ((10 * mainBlockSize.x) / 100) + buttonBlockSize.x;

	const float mainBlocHeightMargin = (10 * mainBlockSize.y) / 100;
	//const float mainBlocWidthtMargin = (5 * mainBlockSize.x) / 100;

	const float testGenerateBlocHeightMargin = ((5 * generateBlockSize.y) / 100) + mainBlocHeightMargin;
	const float testGenerateBlocWidthtMargin = (5 * mainBlockSize.x) / 100;

	const float firstRowWidth = generateBlockSize.x - ((10 * generateBlockSize.x) / 100);
	const float firstRowMargin = (5 * generateBlockSize.x) / 100;
	const float firstRowCenter = (50 * generateBlockSize.x) / 100;

	bool opened = !windowsManagement->getButtons().find("mainMenu")->second;
	ImGui::SetNextWindowPos(ImVec2(buttonBlockSize.x + (testGenerateBlocWidthtMargin * 2) + firstRowMargin, testGenerateBlocHeightMargin));
	ImGui::SetNextWindowSize(ImVec2(firstRowWidth, generateBlockSize.y - ((10 * generateBlockSize.y) / 100)));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, testButtonColor);
	ImGui::Begin("generateTest", &opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoInputs);
	ImGui::End();
	ImGui::PopStyleColor();*/

	///// TEST

	ImGuiIO& io = ImGui::GetIO();
	ImFont* basicFont = io.Fonts->Fonts[1];
	ImGui::PushFont(basicFont);
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
	const float center = (50 * (generateBlockSize.x)) / 100;
	const float generateBlockHeightMargin = (5 * (generateBlockSize.y)) / 100;
	const float centerTextX = center - calculateTextLenght(window.c_str());
	createLabelWithPosition(window.c_str(), center, ImGui::GetCursorPosY(), true);
	//ImGui::SetCursorPosX(centerTextX);
	//ImGui::Text(window.c_str());
	ImGui::PopFont();

	if (window == "generate" || window == "import") {
		const float countryListWidth = generateBlockSize.x - ((20 * generateBlockSize.x) / 100);
		const ImVec2 textSize = ImGui::CalcTextSize("Country: ");
		const float comboSize = (countryListWidth - textSize.x - (style.ItemInnerSpacing.x * 2)) / 2;
		//ImGui::SetCursorPosX((10 * (generateBlockSize.x)) / 100);
		AlignForWidth(comboSize);
		ImGui::SetCursorPosY(generateBlockHeightMargin);
		//createLabelWithPosition("Country: ", (countryListWidth - textSize.x), generateBlockHeightMargin);
		ImGui::Text("Country :");
		ImGui::SameLine();
		static ImGuiComboFlags flags = 0;
		static int item_current_idx = 0; // Here we store our selection data as an index.
		std::vector<Country>* countryList = CountryList::GetInstance()->getList();
		const char* combo_preview_value = countryList->at(item_current_idx).name.c_str();  // Pass in the preview value visible before opening the combo (it could be anything)
		ImGui::PushItemWidth(comboSize);
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
		ImGui::PopItemWidth();
		//ImGui::SameLine();
		ImGui::SetCursorPosX(center - calculateTextLenght("All Countries") - style.ItemInnerSpacing.x);
		ImGui::Checkbox("All Countries", &allCountries);
	}

	if (window == "generate" || window == "import") {
		renderGenerateImportSubWindow();
	}
	else if (window == "multiplayer") {
		std::string text = "Not Done";
		createLabelWithPosition(text.c_str(), centerTextX, ImGui::GetCursorPosY() + (5 * generateBlockSize.y) / 100);
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
		if (createButtonWithPos("Back", (25.0f * (generateBlockSize.x)) / 100, (95.0f * (generateBlockSize.y)) / 100)) {
			windowsManagement->setSubWindow("generate", true);
			windowsManagement->setSubWindow("designer", false);
		}
		if (createButtonWithPos("Regenerate", (75.0f * (generateBlockSize.x)) / 100, (95.0f * (generateBlockSize.y)) / 100)) {
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