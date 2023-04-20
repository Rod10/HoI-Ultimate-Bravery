#include "app_base.hpp"

#include <iostream>
#include <chrono>
#include <numbers>


class MyApp : public AppBase
{
public:
    bool mainWindowOpen = true;
    MyApp()
    {
    }
    ~MyApp() = default;

    virtual void StartUp() final
    {

    }

    virtual void Update() final
    {
        ImDrawList* draw = ImGui::GetForegroundDrawList();
        //draw->AddText(ImVec2((float)0, (float)0), 0xFFFFFFFF, "Text.Text.c_str()");
        char txt_def[] = "text default";

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("Main Window", &mainWindowOpen, 7); // Create a window called "Hello, world!" and append into it.
        ImGui::InputText("##Name", txt_def, sizeof(txt_def));
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
        ImGui::Text("Name");
        ImGui::PopStyleColor();
        ImGui::End();
    }

private:
};