#ifndef __GUI_H_
#define __GUI_H_
//manage all gui things
#include "../Settings.h"
#include "../Sprite.h"
#include "../SpriteSheet.h"
#include "GUIObject.h"
#include "GUIWindow.h"
#include "../Player.h"
#include "TextRenderer.h"
#include "GUIButton.h"
#include "GUITextField.h"

#include "../GameItem.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include "KeyMap.h"
class GUI{
private:
	//Engine *engine;
	GUIWindow * gmenu;
		GUIWindow * bagWindow;
	SpriteSheet *gmenu_sprite;
	GUIObject *hud;
		SpriteSheet *hud_sprite;

		GUIObject *hpHud;
		GUIObject *hpBar;

		GUIObject*  target_hphud;
		GUIObject * target_hpbar;
		TextRenderer *textRend;

		GUITextField *textfield;
		GUITextField *textArea;

		std::vector<GameItem *> *inventory;

		bool typing=false;
		bool capsLock=false;
		bool shiftDown=false;


public:
	 static void gameMenuExit_onClick (GUIButton *owner) {
		std::cout<<owner->getText()<<"  - Button clicked\n";
		running=false;
	}
	GUI(){
		gmenu_sprite = new SpriteSheet("GUIWindow");
			gmenu = new GUIWindow(gmenu_sprite,350,200);
			gmenu->setVisible(false);

			 bagWindow= new GUIWindow(gmenu_sprite,600,224);
			 bagWindow->resize(160,256);
			//	bagWindow->setVisible(false);

			//void (*testCall)(GUIButton *)=testClickCallback;
			gmenu->addComponent(new GUIButton(new SpriteSheet("test_button"),"Exit",gameMenuExit_onClick,gmenu->getX()+15,gmenu->getY()+15,0,0,128,32));
			hud_sprite = new SpriteSheet("GUIHud");
			hud= new GUIObject(hud_sprite, 0, 0,0,0,32,32);

      hpHud = new GUIObject(hud_sprite, 36, 0, 0, 32, 160, 32);
			hpBar= new GUIObject(hud_sprite, 40,20, 0, 64, 32, 32);

			target_hphud = new GUIObject(hud_sprite, 300, 0, 0, 32, 160, 32);
			target_hpbar = new GUIObject(hud_sprite, 304, 0, 0, 64, 32, 32);

			textfield = new GUITextField(new SpriteSheet("textFieldBg"));
				textArea = new GUITextField(new SpriteSheet("textFieldBg"));
				textArea->setY(textArea->getY()-155);
				textArea->setHeight(150);
	}


	void Update(){


	}

	void Draw(Entity *player){
		gmenu->Draw();

if(bagWindow->isVisible()){
		bagWindow->Draw();

			float startX = bagWindow->getX()+20;
			float startY = bagWindow->getY()+20;
			float itemX=startX;
			float itemY=startY;
		for(int i=0;i<inventory->size();i++){
			if(itemX+36 > bagWindow->getX()+bagWindow->getWidth()-10) {
				itemX=startX;
				itemY+=36;
			}
			(*inventory)[i]->Draw(itemX,itemY);
			itemX+=36;
		}
	}

		hud->Draw();
		hpHud->Draw();
		textfield->Draw();
		textArea->Draw();
		float maxbarlen = 153;
		float hp = (float)player->getHP() / (float)player->getMaxHP();


		hpBar->getSprite()->Draw(40, 0, hp*maxbarlen,32,0, 64, 32, 32);

		if (player->getTarget() != nullptr){

			target_hphud->Draw();
			maxbarlen = 153;

			hp = (float)player->getTarget()->getHP() / (float)player->getTarget()->getMaxHP();
			target_hpbar->getSprite()->Draw(304, 0, hp*maxbarlen,32,0,64,32, 32);


		}


	//	hpBar->Draw();
	}

	bool checkMouseClick(double mousex, double mousey){
   if(gmenu->checkMouseClick(mousex,  mousey)){
		 return true;
	 }
	 return false;
	}
	void setGameMenuVisible(bool vis){
		gmenu->setVisible(vis);

	}
bool getGameMenuVisible(){
	return gmenu->isVisible();
	}
bool isTyping(){
	return typing;
}
void setTyping(bool _typing){
	typing=_typing;
}

void addChatLogText(std::string text){
		textArea->setText(textArea->getText()+"\n"+text);
}
void keyPressed(int key){
//	textfield->setText((std::string)textfield->getText()+key);
//std::cout<<key<<std::endl;

std::string text = textfield->getText();

if(key==257){
	if(typing && text!=""){
		if(text=="/nod"){
			text="You nod.";
		}
		if(text=="/caw"){
			text="You caaawwww.";
		}
		if(text=="/lol"){
			text="You laugh.";
		}
		if(text=="/rofl"){
			text="You roll on the floor laughing.";
		}
	textArea->setText(textArea->getText()+"\n"+text);
	textfield->setText("");
}
	return;
}
if(key == 259){
	text = text.substr(0,text.length()-1);
}else if(key == 280){
//	upperCase=!upperCase;
return;
}else {
std::stringstream ss;
char k = key;
ss<<k;
std::string _key = ss.str();
if(!shiftDown && !capsLock ){

std::locale loc;
_key = std::tolower(_key[0],loc);
}else{
	if(key<65){
		k=key;
		std::stringstream sss;

		sss<<k;
		_key=getShiftKey(sss.str());
	}
}

text = text + _key;
}
textfield->setText(text);
}

void setCapsLock(bool _capsLock){
capsLock = _capsLock;
}
bool isCapsLock(){
	return capsLock;
}

void setShiftDown(bool _shiftDown){
	shiftDown= _shiftDown;
}
bool isShiftDown(){
	return shiftDown;
}

std::vector<GameItem *>* getInventory(){
	return inventory;
}
void setInventory (std::vector<GameItem *> *_inventory){
	inventory= _inventory;
}

GUIWindow * getBagWindow(){
	return bagWindow;
}
};

#endif
