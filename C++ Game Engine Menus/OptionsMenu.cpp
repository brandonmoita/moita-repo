#include "OptionsMenu.h"

using namespace GAME;

OptionsMenu::OptionsMenu() : muteScene(false) {
}


OptionsMenu::~OptionsMenu() {

	for (auto a : *guiObjectList)
	{
		delete a;
		a = nullptr;
	}

	guiObjectList->clear();
	guiObjectList = nullptr;

	delete H2DLoader;
	H2DLoader = nullptr;
}


bool OptionsMenu::Initialize() {

	ActionHandler::CreateListener("Exit", (bool*)Actions::ExitGameFunction);
	ActionHandler::CreateListener("Back", (bool*)Actions::OptionsBackFunction);

	ActionHandler::CreateListener("Mute", (bool*)Actions::MuteAudio);
	ActionHandler::CreateListener("UnMute", (bool*)Actions::UnMuteAudio);


	H2DLoader = new LoadH2DLayout();

	guiObjectList = &HumbleEngine::getInstance()->guiObjectList;

	HumbleEngine::getInstance()->camera = new RTSCamera(glm::vec3(2.0f, 15.0f, 12.0f), glm::vec2(HumbleEngine::getInstance()->windowInstance.GetWidth(), HumbleEngine::getInstance()->windowInstance.GetHeight()));

	TextureHandler::getInstance()->CreateTexture("optionsmenu", "Resources/GUI/Menu/mainmenu.png");

	float midX = HumbleEngine::getInstance()->windowInstance.GetWidth() / 2;
	float midY = HumbleEngine::getInstance()->windowInstance.GetHeight() / 2;

	optionsmenu = new GuiObject("optionsmenu", Vec2(midX, midY));

	H2DLoader->LoadLayout("Resources/GUI/OptionsMenu.H2D", optionsmenu, Vec2(HumbleEngine::getInstance()->windowInstance.GetWidth(), HumbleEngine::getInstance()->windowInstance.GetHeight()));

	SkyboxSetUp setup;
	setup.skyboxName = "mmSkybox";
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Right.png");
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Left.png");
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Top.png");
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Bottom.png");
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Back.png");
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Front.png");

	oSkybox = new Skybox(setup);

	guiObjectList->push_back(optionsmenu);

	return true;

}

void OptionsMenu::Update() {
}

void OptionsMenu::Render() {
	glUseProgram(ShaderHandler::GetShader("skyboxShader"));
	oSkybox->Render(ShaderHandler::GetShader("skyboxShader"), HumbleEngine::getInstance()->camera);
}

void OptionsMenu::Draw() {

	glUseProgram(ShaderHandler::GetShader("spriteShader"));
	for (auto g : *guiObjectList) {
		g->Draw(HumbleEngine::getInstance()->camera, HumbleEngine::getInstance()->timer.GetDeltaTime());
	}
}

bool OptionsMenu::GetMute() {
	return muteScene;
}

void OptionsMenu::SetMute(bool newMute_) {
	muteScene = newMute_;
}