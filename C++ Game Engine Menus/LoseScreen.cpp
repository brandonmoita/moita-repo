#include "LoseScreen.h"


using namespace GAME;


LoseScreen::LoseScreen() : muteScene(false) {
}


LoseScreen::~LoseScreen() {

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

bool LoseScreen::Initialize() {

	ActionHandler::CreateListener("New_Game", (bool*)Actions::NewGameFunction);

	ActionHandler::CreateListener("Exit", (bool*)Actions::ExitGameFunction);

	H2DLoader = new LoadH2DLayout();

	guiObjectList = &HumbleEngine::getInstance()->guiObjectList;

	HumbleEngine::getInstance()->camera = new RTSCamera(glm::vec3(2.0f, 15.0f, 12.0f), glm::vec2(HumbleEngine::getInstance()->windowInstance.GetWidth(), HumbleEngine::getInstance()->windowInstance.GetHeight()));

	TextureHandler::getInstance()->CreateTexture("losescreen", "Resources/GUI/Menu/mainmenu.png");

	float midX = HumbleEngine::getInstance()->windowInstance.GetWidth() / 2;
	float midY = HumbleEngine::getInstance()->windowInstance.GetHeight() / 2;

	losescreen = new GuiObject("losescreen", Vec2(midX, midY));

	H2DLoader->LoadLayout("Resources/GUI/LoseScreen.H2D", losescreen, Vec2(HumbleEngine::getInstance()->windowInstance.GetWidth(), HumbleEngine::getInstance()->windowInstance.GetHeight()));


	guiObjectList->push_back(losescreen);

	return true;

}

void LoseScreen::Update() {

}

void LoseScreen::Render() {

}

void LoseScreen::Draw() {

	glUseProgram(ShaderHandler::GetShader("spriteShader"));
	for (auto g : *guiObjectList) {
		g->Draw(HumbleEngine::getInstance()->camera, HumbleEngine::getInstance()->timer.GetDeltaTime());
	}
}

bool LoseScreen::GetMute() {
	return muteScene;
}

void LoseScreen::SetMute(bool newMute_) {
	muteScene = newMute_;
}
