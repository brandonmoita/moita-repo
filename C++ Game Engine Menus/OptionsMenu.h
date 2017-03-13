#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "../../Engine/HumbleEngine.h"
#include "../Actions.h"

using namespace ENGINE;

namespace GAME {
	class OptionsMenu: public Scene
	{
	public:
		OptionsMenu();
		~OptionsMenu();
		virtual bool Initialize();
		virtual void Update();
		virtual void Render();
		virtual void Draw();
		virtual bool GetMute();
		virtual void SetMute(bool newMute_);

	private:

		GuiObject* optionsmenu;
		LoadH2DLayout* H2DLoader;
		std::vector<GuiObject*>* guiObjectList;
		Skybox* oSkybox;
		bool muteScene;
	};

}

#endif