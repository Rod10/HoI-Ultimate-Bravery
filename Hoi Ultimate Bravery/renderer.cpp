#include "renderer.hpp"

void Renderer::renderStats(bool windowOpen, Tank tank)
{
    /*ImGuiIO& io = ImGui::GetIO();
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

    setImage(ImGui::GetCursorPosY() - 4.0f, ImGui::GetCursorPosX() + 16.0f, "blueprint", std::format("ger_{0}_tank_blueprint", Tank::tankTypeToString(typeToShow)));

    fileName = std::format("{0}", Suspension::typeToString(tank.suspension.type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 22.5f, "modules", fileName);

    fileName = std::format("{0}", Armor::typeToString(tank.armor.type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 100.0f, "modules", fileName);

    fileName = std::format("{0}", Engine::typeToString(tank.engine.type));
    setImage(Constant::TextPos::TANK_MODULE_HEIGHT_2 + 2.0f - 4.0f, ImGui::GetCursorPosX() + 165.0f, "modules", fileName);

    off = calculatePos(MIDDLE, std::to_string(tank.engineLevel).c_str());
    createLabelWithPosition(std::to_string(tank.engineLevel).c_str(), off - 130.0f, Constant::TextPos::TANK_MODULE_HEIGHT_2 + 20.0f);

    off = calculatePos(MIDDLE, std::to_string(tank.armorLevel).c_str());
    createLabelWithPosition(std::to_string(tank.armorLevel).c_str(), off - 55.0f, Constant::TextPos::TANK_MODULE_HEIGHT_2 + 20.0f);

    ImGui::PushFont(statsFont);
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));

    //Base stats
    std::string speed = std::format("{:.1f} km/h", newTankStats.find(typeToShow)->second.speed);
    createLabelWithPosition(speed.c_str(), Constant::TextPos::BASE_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 60.0f);

    std::string reliability = std::format("{:.1f}", newTankStats.find(typeToShow)->second.reliability);
    createLabelWithPosition(reliability.c_str(), Constant::TextPos::BASE_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 80.0f);

    std::string supplyUse = std::format("{:.2f}", newTankStats.find(typeToShow)->second.supplyUse);
    createLabelWithPosition(supplyUse.c_str(), Constant::TextPos::BASE_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 100.0f);
    //Base stats

    //Combat stats
    std::string softAttack = std::format("{:.2f}", newTankStats.find(typeToShow)->second.softAttack);
    createLabelWithPosition(softAttack.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 60.0f);

    std::string hardAttack = std::format("{:.2f}", newTankStats.find(typeToShow)->second.hardAttack);
    createLabelWithPosition(hardAttack.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 80.0f);

    std::string piercing = std::format("{:.2f}", newTankStats.find(typeToShow)->second.piercing);
    createLabelWithPosition(piercing.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 100.0f);

    std::string hardness = std::format("{:.2f}", newTankStats.find(typeToShow)->second.hardness);
    createLabelWithPosition(hardness.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 120.0f);

    std::string armor = std::format("{:.2f}", newTankStats.find(typeToShow)->second.armor);
    createLabelWithPosition(armor.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 140.0f);

    std::string breakthrough = std::format("{:.2f}", newTankStats.find(typeToShow)->second.breakthrough);
    createLabelWithPosition(breakthrough.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 160.0f);

    std::string defense = std::format("{:.2f}", newTankStats.find(typeToShow)->second.defense);
    createLabelWithPosition(defense.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 180.0f);

    std::string airAttack = std::format("{:.2f}", newTankStats.find(typeToShow)->second.airAttack);
    createLabelWithPosition(airAttack.c_str(), Constant::TextPos::COMBAT_STATS_POS, Constant::TextPos::TITLE_HEIGHT + 200.0f);
    //Combat stats

    //Misc Stats
    std::string fuelCapacity = std::format("{:.2f}", newTankStats.find(typeToShow)->second.fuelCapacity);
    createLabelWithPosition(fuelCapacity.c_str(), 1060.0f, Constant::TextPos::TITLE_HEIGHT + 60.0f);

    std::string fuelUsage = std::format("{:.2f}", newTankStats.find(typeToShow)->second.fuelUsage);
    createLabelWithPosition(fuelUsage.c_str(), 1060.0f, Constant::TextPos::TITLE_HEIGHT + 80.0f);

    //TODO research suppression value
    createLabelWithPosition("???", 1060.0f, Constant::TextPos::TITLE_HEIGHT + 100.0f);

    //TODO research reconnaissance value
    createLabelWithPosition("???", 1060.0f, Constant::TextPos::TITLE_HEIGHT + 120.0f);

    std::string entrenchment = std::format("{:.2f}", newTankStats.find(typeToShow)->second.entrenchment);
    createLabelWithPosition(entrenchment.c_str(), 1060.0f, Constant::TextPos::TITLE_HEIGHT + 140.0f);
    //Misc Stats

    ImGui::PopStyleColor();
    ImGui::PopFont();*/
}

void Renderer::setIcon(float y, float x, std::string type, std::string name) {
        /*ImGui::SetCursorPosY(y);
        ImGui::SetCursorPosX(x);
        Texture texture = Icon::GetInstance()->getTankIconTextures(type, name);
        ImGui::Image((void*)(intptr_t)texture.my_image_texture, ImVec2(texture.my_image_width, texture.my_image_height));*/
}
