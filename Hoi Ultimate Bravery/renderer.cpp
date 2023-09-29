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
    } else if (unitType == UnitType::Type::Ship) {
        Texture texture = Icon::GetInstance()->getShipModulesTextures(type, name);
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
    } else if (unitType == UnitType::Type::Plane) {
        Texture texture = Icon::GetInstance()->getPlaneModulesTextures(type, name);
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
    }
}

bool Renderer::createButtonWithPosition(const char* label, Constant::Position position)
{
    ImGuiStyle& style = ImGui::GetStyle();

    float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;

    float off = (avail - size) * (position / 1000.f);
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

    return ImGui::Button(label);
}

void Renderer::createLabelWithPosition(const char* label, Constant::Position position)
{
    ImGuiStyle& style = ImGui::GetStyle();

    float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;

    float off = (avail - size) * (position / 1000.f);
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

    return ImGui::Text(label);
}

void Renderer::createLabelWithPosition(const char* label, Constant::Position position, ImGuiInputTextFlags_ flag)
{
    ImGuiStyle& style = ImGui::GetStyle();

    float size = ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;

    float off = (avail - size) * (position / 1000.f);
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

    return ImGui::Text(label, flag);
}

void Renderer::createLabelWithPosition(const char* label, float x, float y)
{
    ImGui::SetCursorPosY(y);
    ImGui::SetCursorPosX(x - ImGui::CalcTextSize(label).x);
    return ImGui::Text(label);
}

void Renderer::createTitleWithPosition(const char* label, float x, float y)
{
    ImGui::SetCursorPosY(y);
    ImGui::SetCursorPosX(x);
    return ImGui::Text(label);
}

float Renderer::calculatePos(Constant::Position position, std::string text) {
    ImGuiStyle& style = ImGui::GetStyle();

    float size = ImGui::CalcTextSize(text.c_str()).x - style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;

    float off = (avail - size) * (position / 1000.f);
    return off;
}

float Renderer::calculatePos(Constant::Position position, int width) {
    ImGuiStyle& style = ImGui::GetStyle();

    float size = width - style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;

    float off = (avail - size) * (position / 1000.f);
    return off;
}

float Renderer::calculatePos(float position, std::string text) {
    ImGuiStyle& style = ImGui::GetStyle();

    float size = ImGui::CalcTextSize(text.c_str()).x - style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;

    float off = (avail - size) * (position / 1000.f);
    return off;
}

float Renderer::calculatePos(float position, int width) {
    ImGuiStyle& style = ImGui::GetStyle();

    float size = width - style.FramePadding.x * 2.0f;
    float avail = ImGui::GetContentRegionAvail().x;

    float off = (avail - size) * (position / 1000.f);
    return off;
}

void Renderer::renderTankDesignerWindow(bool windowOpen, Tank tank)
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
    ImGui::Begin(Tank::tankTypeToString(tank.type).c_str(), &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::PushFont(titleFont);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
    ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
    ImGui::SetCursorPosY(Constant::TextPos::TITLE_HEIGHT);
    createLabelWithPosition("Equipment Designer", Constant::Position::MIDDLE);
    ImGui::PopFont();
    ImGui::PopStyleColor();

    setImage(Constant::TextPos::TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "tank_name_bg", UnitType::Type::Tank);

    setImage(79.8, 329, "background", "tank_icon_bg", UnitType::Type::Tank);

    setImage(Constant::TextPos::TANK_ROLE_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "tank_role_bg", UnitType::Type::Tank);

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

    ImGui::PushFont(textFont);
    createTitleWithPosition("Engine", Constant::Position::MIDDLE - 100.0f, Constant::TextPos::TANK_MODULE_HEIGHT_2);
    createTitleWithPosition("Armor", Constant::Position::MIDDLE - 20.0f, Constant::TextPos::TANK_MODULE_HEIGHT_2);
    ImGui::PopFont();

    ImGui::End();
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

    auto off = Utils::calculatePos(Constant::Position::MIDDLE, 1092);
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
        if (module.type == Module::None) {
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

void Renderer::renderStats(bool windowOpen, Tank tank, std::map<TankType::Type, std::string> tankIconNames, std::unordered_map<TankType::Type, Stats> newTankStats)
{
    ImGuiIO& io = ImGui::GetIO();
    ImFont* basicFont = io.Fonts->Fonts[2];
    ImFont* statsFont = io.Fonts->Fonts[4];

    auto off = Utils::calculatePos(Constant::Position::MIDDLE, 1092);
    ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
    ImGui::SetNextWindowSize(ImVec2(1108, 569));
    ImGui::Begin("Light Tank", &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
    ImGui::PushFont(basicFont);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 61.0f);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 30.0f);
    ImGui::Text(Tank::tankTypeToString(tank.type).c_str());

    setIcon(ImGui::GetCursorPosY() - 20.0f, ImGui::GetCursorPosX() + 325.0f, Tank::tankTypeToString(tank.type), tankIconNames.find(tank.type)->second, UnitType::Type::Tank);

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 25.0f);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 30.0f);
    ImGui::Text(Tank::tankVersionToString(tank.version).c_str());

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
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 22.5f, "modules", fileName, UnitType::Type::Tank);

    fileName = std::format("{0}", Armor::typeToString(tank.armor.type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 100.0f, "modules", fileName, UnitType::Type::Tank);

    fileName = std::format("{0}", Engine::typeToString(tank.engine.type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 165.0f, "modules", fileName, UnitType::Type::Tank);

    off = Utils::calculatePos(Constant::Position::MIDDLE, std::to_string(tank.engineLevel).c_str());
    createLabelWithPosition(std::to_string(tank.engineLevel).c_str(), off - 130.0f, Constant::TextPos::TANK_MODULE_HEIGHT_2 + 20.0f);

    off = calculatePos(Constant::Position::MIDDLE, std::to_string(tank.armorLevel).c_str());
    createLabelWithPosition(std::to_string(tank.armorLevel).c_str(), off - 55.0f, Constant::TextPos::TANK_MODULE_HEIGHT_2 + 20.0f);

    ImGui::PushFont(statsFont);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));

    //Base stats
    std::string speed = std::format("{:.1f} km/h", newTankStats.find(tank.type)->second.speed);
    createLabelWithPosition(speed.c_str(), Constant::TextPos::BASE_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 60.0f);

    std::string reliability = std::format("{:.1f}", newTankStats.find(tank.type)->second.reliability);
    createLabelWithPosition(reliability.c_str(), Constant::TextPos::BASE_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 80.0f);

    std::string supplyUse = std::format("{:.2f}", newTankStats.find(tank.type)->second.supplyUse);
    createLabelWithPosition(supplyUse.c_str(), Constant::TextPos::BASE_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 100.0f);
    //Base stats

    //Combat stats
    std::string softAttack = std::format("{:.2f}", newTankStats.find(tank.type)->second.softAttack);
    createLabelWithPosition(softAttack.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 60.0f);

    std::string hardAttack = std::format("{:.2f}", newTankStats.find(tank.type)->second.hardAttack);
    createLabelWithPosition(hardAttack.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 80.0f);

    std::string piercing = std::format("{:.2f}", newTankStats.find(tank.type)->second.piercing);
    createLabelWithPosition(piercing.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 100.0f);

    std::string hardness = std::format("{:.2f}", newTankStats.find(tank.type)->second.hardness);
    createLabelWithPosition(hardness.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 120.0f);

    std::string armor = std::format("{:.2f}", newTankStats.find(tank.type)->second.armor);
    createLabelWithPosition(armor.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 140.0f);

    std::string breakthrough = std::format("{:.2f}", newTankStats.find(tank.type)->second.breakthrough);
    createLabelWithPosition(breakthrough.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 160.0f);

    std::string defense = std::format("{:.2f}", newTankStats.find(tank.type)->second.defense);
    createLabelWithPosition(defense.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 180.0f);

    std::string airAttack = std::format("{:.2f}", newTankStats.find(tank.type)->second.airAttack);
    createLabelWithPosition(airAttack.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 200.0f);
    //Combat stats

    //Misc Stats
    std::string fuelCapacity = std::format("{:.2f}", newTankStats.find(tank.type)->second.fuelCapacity);
    createLabelWithPosition(fuelCapacity.c_str(), 1060.0f, Constant::TextPos::TITLE_HEIGHT + 60.0f);

    std::string fuelUsage = std::format("{:.2f}", newTankStats.find(tank.type)->second.fuelUsage);
    createLabelWithPosition(fuelUsage.c_str(), 1060.0f, Constant::TextPos::TITLE_HEIGHT + 80.0f);

    //TODO research suppression value
    createLabelWithPosition("???", 1060.0f, Constant::TextPos::TITLE_HEIGHT + 100.0f);

    //TODO research reconnaissance value
    createLabelWithPosition("???", 1060.0f, Constant::TextPos::TITLE_HEIGHT + 120.0f);

    std::string entrenchment = std::format("{:.2f}", newTankStats.find(tank.type)->second.entrenchment);
    createLabelWithPosition(entrenchment.c_str(), 1060.0f, Constant::TextPos::TITLE_HEIGHT + 140.0f);
    //Misc Stats

    ImGui::PopStyleColor();
    ImGui::PopFont();
}

void Renderer::renderStats(bool windowOpen, Plane plane, std::map<PlaneType::Type, std::string> planeIconNames, std::unordered_map<PlaneRole::Role, Stats> newPlaneStats)
{
    ImGuiIO& io = ImGui::GetIO();
    ImFont* basicFont = io.Fonts->Fonts[2];
    ImFont* statsFont = io.Fonts->Fonts[4];

    auto off = Utils::calculatePos(Constant::Position::MIDDLE, 1092);
    ImGui::SetNextWindowPos(ImVec2(off, 200.0f));
    ImGui::SetNextWindowSize(ImVec2(1108, 569));
    ImGui::Begin("Light Tank", &windowOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);
    ImGui::PushFont(basicFont);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 255, 255));
    std::string string = std::format("{0} {1}", PlaneVersion::versionToYear(plane.version), PlaneRole::roleToString(plane.role).c_str());
    createTitleWithPosition(string.c_str(), 35.0f, Constant::TextPos::TANK_NAME_HEIGHT + 5.0f);

    setIcon(ImGui::GetCursorPosY() - 20.0f, ImGui::GetCursorPosX() + 325.0f, PlaneType::typeToString(plane.type), planeIconNames.find(plane.type)->second, UnitType::Type::Plane);

    int index = 0;
    for (auto& module : plane.custom) {
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