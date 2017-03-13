#ifndef SCENEMAINMENU_H
#define SCENEMAINMENU_H

#include "../../Engine/HumbleEngine.h"
#include "../Actions.h"
#include "../GameObjects/MainMenuObjects/OrbitObject.h"

using namespace ENGINE;

namespace GAME {
	class SceneMainMenu : public Scene
	{
	public:
		SceneMainMenu();
		~SceneMainMenu();
		virtual bool Initialize();
		virtual void Update();
		virtual void Render();
		virtual void Draw();
		virtual bool GetMute();
		virtual void SetMute(bool newMute_);

	private:

		GuiObject* mainmenu;
		LoadH2DLayout* H2DLoader;
		LoadOBJModel* OBJLoader;
		std::vector<GuiObject*>* guiObjectList;
		OrbitObject* planet;
		OrbitObject* ship;
		Skybox* mmSkybox;
		bool muteScene;
	};
}

#endif