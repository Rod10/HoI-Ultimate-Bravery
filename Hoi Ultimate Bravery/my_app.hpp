#include "app_base.hpp"

#include "constant.hpp"
#include "renderer.hpp"
#include "windowsmanagement.hpp"

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
		ImGui::SetCursorPosX(center.x);
		ImGui::Text("HoI Ultimate Bravery");
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopFont();

		const ImVec2 mainBlockSize = Renderer::getBlockSize();

		const float mainBlocHeightMargin = (10 * mainBlockSize.y) / 100;
		const float mainBlocWidthtMargin = (5 * mainBlockSize.x) / 100;

		const ImVec2 buttonBlockSize = Renderer::getButtonSize();
		
		const float generateBlockXPos = ((10 * mainBlockSize.x) / 100) + buttonBlockSize.x;

		bool opened = true;
		ImGui::PushStyleColor(ImGuiCol_WindowBg, windowColor);
		ImGui::SetNextWindowPos(ImVec2(mainBlocWidthtMargin, mainBlocHeightMargin));
		ImGui::SetNextWindowSize(ImVec2(buttonBlockSize.x, mainBlockSize.y));
		ImGui::Begin("buttonBlock", &opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
		ImGui::PopStyleColor();
		ImGui::PushFont(basicFont);
		ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
		Renderer::renderButtonBlock(150.0f);
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::End();
		
		if (windowManagement->getButtons().find("mainMenu")->second == false) {
			const float test = mainBlockSize.x - buttonBlockSize.x;
			bool opened = !windowManagement->getButtons().find("mainMenu")->second;
			ImGui::SetNextWindowPos(ImVec2(generateBlockXPos, mainBlocHeightMargin));
			ImGui::PushStyleColor(ImGuiCol_WindowBg, greyWindowColor);
			ImGui::SetNextWindowSize(ImVec2(mainBlockSize.x - buttonBlockSize.x, mainBlockSize.y));
			ImGui::Begin("generate", &opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
			Renderer::renderSubWindow();
			ImGui::PopStyleColor();
			ImGui::End();
		}
		ImGui::End();
	}

private:
	std::vector<Language> languageList = Language::getLanguageList();
	Language* language;
	Settings* settings = Settings::getInstance();

	bool mainWindowOpen = true;

	WindowsManagement* windowManagement = WindowsManagement::GetInstance();

	std::string languageFile;
	std::string languageFilePath;
	std::unordered_map<int, std::string> localizedStrings;
	std::unordered_map<int, std::string> converterToGameName = Utils::loadConverter();

	ImVec4 backgroundColor = ImVec4(0.831f, 0.902f, 0.945f, 1.00f);
	ImVec4 windowColor = ImVec4(0.149f, 0.137f, 0.125f, 1.00f);
	ImVec4 greyWindowColor = ImVec4(0.851f, 0.851f, 0.851f, 1.00f);
	ImVec4 buttonColor = ImVec4(0.231f, 0.255f, 0.224f, 1.00f);

	const char* getLocalizedString(std::string text) {
		int id = Utils::hash(text.c_str());
		return localizedStrings[id].c_str();
	}

};