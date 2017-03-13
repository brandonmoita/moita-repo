#include "SceneMainMenu.h"

using namespace GAME;


SceneMainMenu::SceneMainMenu() : muteScene(false) {
}


SceneMainMenu::~SceneMainMenu() {
	for (auto a : *guiObjectList)
	{
		delete a;
		a = nullptr;
	}

	guiObjectList->clear();
	guiObjectList = nullptr;

	delete H2DLoader;
	H2DLoader = nullptr;

	delete OBJLoader;
	OBJLoader = nullptr;

	delete planet;
	planet = nullptr;

	delete ship;
	ship = nullptr;

	delete mmSkybox;
	mmSkybox = nullptr;
}

bool SceneMainMenu::Initialize() {

	SceneGraph::GetInstance()->ClearScene();

	ActionHandler::CreateListener("New_Game", (bool*)Actions::NewGameFunction);

	ActionHandler::CreateListener("Options_Menu", (bool*)Actions::OptionsFunction);

	ActionHandler::CreateListener("Exit", (bool*)Actions::ExitGameFunction);

	H2DLoader = new LoadH2DLayout();

	OBJLoader = new LoadOBJModel();

	guiObjectList = &HumbleEngine::getInstance()->guiObjectList;

	HumbleEngine::getInstance()->camera = new RTSCamera(glm::vec3(2.0f, 15.0f, 12.0f), glm::vec2(HumbleEngine::getInstance()->windowInstance.GetWidth(), HumbleEngine::getInstance()->windowInstance.GetHeight()));

	TextureHandler::getInstance()->CreateTexture("mainmenu", "Resources/GUI/Menu/mainmenu.png");

	float midX = HumbleEngine::getInstance()->windowInstance.GetWidth() / 2;
	float midY = HumbleEngine::getInstance()->windowInstance.GetHeight() / 2;

	mainmenu = new GuiObject("mainmenu", Vec2(midX, midY));
	//mainmenu->AddComponent("mainmenuImage", new GuiImageComponent("mainmenu", Vec2(0.0f), 0.5f));

	
	H2DLoader->LoadLayout("Resources/GUI/MainMenu.H2D", mainmenu, Vec2(HumbleEngine::getInstance()->windowInstance.GetWidth(), HumbleEngine::getInstance()->windowInstance.GetHeight()));

	//PLANET AND SHIP - 3D STUFF
	HumbleEngine::getInstance()->camera = new DefaultCamera(glm::vec3(0.0f, 3.0f, 12.0f), glm::vec2(HumbleEngine::getInstance()->windowInstance.GetWidth(), HumbleEngine::getInstance()->windowInstance.GetHeight()));
	HumbleEngine::getInstance()->camera->setRotation(-90, -15);
	HumbleEngine::getInstance()->camera->lightSourceList[0]->SetColor(Vec4(0.9f, 0.9f, 0.9f, 1.0f));

	SkyboxSetUp setup;
	setup.skyboxName = "mmSkybox";
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Right.png");
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Left.png");
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Top.png");
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Bottom.png");
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Back.png");
	setup.faces.push_back("Resources/Textures/Skybox/MainMenuSkybox/Front.png");

	mmSkybox = new Skybox(setup);

	Model* planetPrefab = new Model(ShaderHandler::GetShader("baseShader"));
	OBJLoader->LoadModel("Resources/Models/Planet_Eden.obj", "Resources/Models/Planet_Eden.mtl", planetPrefab);
	SceneGraph::GetInstance()->AddModel(planetPrefab);

	Model* shipPrefab = new Model(ShaderHandler::GetShader("baseShader"));
	OBJLoader->LoadModel("Resources/Models/MiniDropPod.obj", "Resources/Models/MiniDropPod.mtl", shipPrefab);
	SceneGraph::GetInstance()->AddModel(shipPrefab);

	planet = new OrbitObject("planetEden", planetPrefab, -4.5f);
	planet->SetRotationVelocity(0.4f);
	planet->SetOrbitRotation(0.0f);

	ship = new OrbitObject("dropPodShip", shipPrefab, 5.0f);
	ship->SetParentObject(planet);
	ship->SetRotationVelocity(0.05f);
	ship->SetOrbitRotation(1.5f);

	guiObjectList->push_back(mainmenu);


	HumbleEngine::getInstance()->camera->lightSourceList[0]->SetDirection(Vec3(1.0f, 0.0f, -0.5f));
	HumbleEngine::getInstance()->camera->lightSourceList[0]->SetAmbient(0.01f);
	HumbleEngine::getInstance()->camera->lightSourceList[0]->SetSpecular(0.5f);
	HumbleEngine::getInstance()->camera->lightSourceList[0]->SetColor(Vec4(0.9f, 0.9f, 0.9f, 1.0f));


	return true;

}

void SceneMainMenu::Update() {
	SceneGraph::GetInstance()->Update();
}

void SceneMainMenu::Render() {
	glUseProgram(ShaderHandler::GetShader("skyboxShader"));
	mmSkybox->Render(ShaderHandler::GetShader("skyboxShader"), HumbleEngine::getInstance()->camera);

	SceneGraph::GetInstance()->Render(ShaderHandler::GetShader("baseShader"), HumbleEngine::getInstance()->camera);
}

void SceneMainMenu::Draw() {

	glUseProgram(ShaderHandler::GetShader("spriteShader"));
	for (auto g : *guiObjectList) {
		g->Draw(HumbleEngine::getInstance()->camera, HumbleEngine::getInstance()->timer.GetDeltaTime());
	}
}

bool SceneMainMenu::GetMute() {
	return muteScene;
}

void SceneMainMenu::SetMute(bool newMute_) {
	muteScene = newMute_;
}

