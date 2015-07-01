#ifndef __GUI_H_
#define __GUI_H_
//manage all gui things
#include "../Sprite.h"
#include "../SpriteSheet.h"
#include "GUIObject.h"
#include "GUIWindow.h"
#include "../Entity.h"
#include "../Player.h"
#include "TextRenderer.h"
#include "GUIButton.h"
class GUI{
private:
	GUIWindow * gmenu;
	SpriteSheet *gmenu_sprite;
	GUIObject *hud;
		SpriteSheet *hud_sprite;

		GUIObject *hpHud;
		GUIObject *hpBar;

		GUIObject*  target_hphud;
		GUIObject * target_hpbar;
		TextRenderer *textRend;
				

public:

	GUI(){
		gmenu_sprite = new SpriteSheet("GUIWindow");
			gmenu = new GUIWindow(gmenu_sprite,350,200);
			gmenu->setVisible(false);
			hud_sprite = new SpriteSheet("GUIHud");
			hud= new GUIObject(hud_sprite, 0, 0,0,0,32,32);
			
                        hpHud = new GUIObject(hud_sprite, 36, 0, 0, 32, 160, 32);
			hpBar= new GUIObject(hud_sprite, 40,20, 0, 64, 32, 32);

			target_hphud = new GUIObject(hud_sprite, 300, 0, 0, 32, 160, 32);
			target_hpbar = new GUIObject(hud_sprite, 304, 0, 0, 64, 32, 32);
			
	}
	void Update(){


	}

	void Draw(Entity *player){
		gmenu->Draw();
		hud->Draw();
		hpHud->Draw();
		float maxbarlen = 153;
		float hp = (float)player->getHP() / (float)player->getMaxHP();


		hpBar->getSprite()->Draw(40, 0, 0, 64, 32, 32, hp*maxbarlen, 32);

		if (player->getTarget() != nullptr){
	
			target_hphud->Draw();
			maxbarlen = 153;

			hp = (float)player->getTarget()->getHP() / (float)player->getTarget()->getMaxHP();
			target_hpbar->getSprite()->Draw(304, 0, 0, 64, 32, 32, hp*maxbarlen, 32);
			//textRend = new TextRenderer(350,3,player->getTarget()->getName());
			//textRend->Draw();
			//delete(textRend);

		}
		

	//	hpBar->Draw();
	}

	void setGameMenuVisible(bool vis){
		gmenu->setVisible(vis);

	}
bool getGameMenuVisible(){
	return gmenu->isVisible();
	}


};

#endif
