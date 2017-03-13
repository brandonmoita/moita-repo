#ifndef LOSESCREEN_H
#define LOSESCREEN_H

#include "../../Engine/HumbleEngine.h"
#include "../Actions.h"


using namespace ENGINE;


namespace GAME {

	class LoseScreen : public Scene
	{
	public:
		LoseScreen();
		~LoseScreen();
		virtual bool Initialize();
		virtual void Update();
		virtual void Render();
		virtual void Draw();
		virtual bool GetMute();
		virtual void SetMute(bool newMute_);

	private:

		GuiObject* losescreen;
		LoadH2DLayout* H2DLoader;
		std::vector<GuiObject*>* guiObjectList;
		bool muteScene;
	};

}

#endif