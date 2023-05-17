#include "renderer.hpp"
void setIcon(float y, float x, std::string type, std::string name) {
        ImGui::SetCursorPosY(y);
        ImGui::SetCursorPosX(x);
        Texture texture = Icon::GetInstance()->getTankIconTextures(type, name);
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
}

void setImage(float y, float x, std::string type, std::string name) {
    ImGui::SetCursorPosY(y);
    ImGui::SetCursorPosX(x);
    Texture texture = Icon::GetInstance()->getTankModulesTextures(type, name);
    ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));
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

    setImage(Constant::TextPos::TANK_NAME_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "tank_name_bg");

    setImage(79.8, 329, "background", "tank_icon_bg");

    setImage(Constant::TextPos::TANK_ROLE_HEIGHT, ImGui::GetCursorPosX() + 20.0f, "background", "tank_role_bg");

    for (int i = 0; i <= 5; i++) {
        float x = ImGui::GetCursorPosX() + (76 * i) + (13.0f - (i * 3));
        if (i == 0) {
            x = 23.0f;
        }
        setImage(Constant::TextPos::TANK_MODULE_HEIGHT, x, "background", "equipment_icon_bg");
    }

    setImage(ImGui::GetCursorPosY() - 4.0f, ImGui::GetCursorPosX() + 16.0f, "background", "tank_blueprint_background");

    texture = Icon::GetInstance()->getTankModulesTextures("background", "equipment_icon_bg");;
    for (int i = 0; i <= 2; i++) {
        float x = ImGui::GetCursorPosX() + (76 * i) + (12.0f - (i * 3));
        if (i == 0) {
            x = 23.0f;
        }
        setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2, x, "background", "equipment_icon_bg");
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

void Renderer::renderStats(bool windowOpen, Tank tank, std::map<std::string, std::string> tankIconNames, std::unordered_map<TankType::Type, Stats> newTankStats)
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

    setIcon(ImGui::GetCursorPosY() - 20.0f, ImGui::GetCursorPosX() + 325.0f, Tank::tankTypeToString(tank.type), tankIconNames.find(Tank::tankTypeToString(tank.type))->second);

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 25.0f);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 30.0f);
    ImGui::Text(Tank::tankVersionToString(tank.version).c_str());

    std::string fileName = std::format("{0}_{1}", Gun::gunNameToString(tank.gun.name), Gun::typeToString(tank.gun.type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 22.0f, "modules", fileName);

    fileName = std::format("{0}_turret_{1}", TurretType::turretTypeToString(tank.turret.type), tank.turret.crew);
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 88.0f, "modules", fileName);

    fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[0].type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 170.0f, "modules", fileName);

    fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[1].type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 240.0f, "modules", fileName);

    fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[2].type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 315.0f, "modules", fileName);

    fileName = std::format("{0}", SpecialModule::typeToString(tank.specialModules[3].type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT + 2.0f, ImGui::GetCursorPosX() + 390.0f, "modules", fileName);

    setImage(ImGui::GetCursorPosY() - 4.0f, ImGui::GetCursorPosX() + 16.0f, "blueprint", std::format("ger_{0}_tank_blueprint", Tank::tankTypeToString(tank.type)));

    fileName = std::format("{0}", Suspension::typeToString(tank.suspension.type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 22.5f, "modules", fileName);

    fileName = std::format("{0}", Armor::typeToString(tank.armor.type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 100.0f, "modules", fileName);

    fileName = std::format("{0}", Engine::typeToString(tank.engine.type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 165.0f, "modules", fileName);

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