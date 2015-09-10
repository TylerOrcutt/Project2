/**************************************
*GUI.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
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
#include "GUIMessagebox.h"
#include "../GameItem.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <locale>
#include "KeyMap.h"
#include "../Network/NetworkClient.h"

class GUI{
private:
	//Engine *engine;
NetworkClient * network;

//login Stuff
GUITextField *textUser,*textPass;
GUIButton *loginBtn;
GUIWindow * gmenu;
GUIWindow * bagWindow,*actionBar;
	GUIObject *hud;

	SpriteSheet *gmenu_sprite;
	SpriteSheet *hud_sprite, *fireSprite, *teleSprite, *actionBarItemBlank, *textFieldBg, *test_button;

	GUIObject *fireball,*teleport;
		GUIObject *hpHud;
		GUIObject *hpBar;
		GUIObject*  target_hphud;
		GUIObject * target_hpbar;

		std::vector<GUIObject *> actionBarItems;
		int actionBarItemCount=10;

		TextRenderer *textRend;

		GUITextField *textfield;
		GUITextField *textArea;

		std::vector<GameItem *> *inventory;

		bool typing=false;
		bool capsLock=false;
		bool shiftDown=false;

	GUITextField * focusText=nullptr;

	GUIMessagebox *msgbox=nullptr;

public:
	 static void gameMenuExit_onClick (GUIButton *owner) {
		std::cout<<owner->getText()<<"  - Button clicked\n";
		running=false;
	}
	GUI(){
	//	msgbox = new GUIMessagebox("Login Failed");
		gmenu_sprite = new SpriteSheet("GUIWindow");

		fireSprite= new SpriteSheet("fireball");
		teleSprite= new SpriteSheet("teleport_icon");
	actionBarItemBlank= new SpriteSheet("actionBarItem_blank");
	test_button = new SpriteSheet("test_button");
		textFieldBg = new SpriteSheet("textFieldBg");
			gmenu = new GUIWindow(gmenu_sprite,350,200);
			gmenu->setVisible(false);

			 bagWindow= new GUIWindow(gmenu_sprite,600,224);
			 bagWindow->resize(160,256);
			 bagWindow->setVisible(false);

			 actionBar= new GUIWindow(gmenu_sprite,350,540);
			actionBar->resize(320+64,64);

			float abix= actionBar->getX()+15;
			float abiy=actionBar->getY()+15;
			for(int i=0;i<actionBarItemCount;i++){
				actionBarItems.push_back(new GUIObject(actionBarItemBlank,abix+(i*36), abiy));
			}
delete(actionBarItems[0]);
delete(actionBarItems[1]);
			actionBarItems[0]=(new GUIObject(fireSprite,abix,abiy));
			actionBarItems[1]=(new GUIObject(teleSprite,abix+36, abiy));




			//void (*testCall)(GUIButton *)=testClickCallback;
			gmenu->addComponent(new GUIButton(test_button, "Exit", gameMenuExit_onClick, gmenu->getX() + 15, gmenu->getY() + 15, 0, 0, 128, 32));
			hud_sprite = new SpriteSheet("GUIHud");
			hud= new GUIObject(hud_sprite, 0, 0,0,0,32,32);

      hpHud = new GUIObject(hud_sprite, 36, 0, 0, 32, 160, 32);
			hpBar= new GUIObject(hud_sprite, 40,20, 0, 64, 32, 32);

			target_hphud = new GUIObject(hud_sprite, 300, 0, 0, 32, 160, 32);
			target_hpbar = new GUIObject(hud_sprite, 304, 0, 0, 64, 32, 32);

			textfield = new GUITextField(textFieldBg);
			textfield->setPadding(15);
			
			textArea = new GUITextField(textFieldBg);
				textArea->setY(textArea->getY()-155);
				textArea->setHeight(150);
				textArea->setPadding(15);
				textArea->setMultiLine(true);


				textUser = new GUITextField(textFieldBg);
	textUser->setWidth(200);
		textUser->setPadding(17);
	textUser->setPosition((SCREEN_WIDTH/2)-(textUser->getWidth()/2),(SCREEN_HEIGHT/2)-(textUser->getHeight()/2)-20);
	textPass = new GUITextField(textFieldBg);
					textPass->setPadding(17);
						textPass->setWidth(200);
					textPass->setPosition((SCREEN_WIDTH/2)-(textPass->getWidth()/2),(SCREEN_HEIGHT/2)-(textPass->getHeight()/2)+20);
textPass->setPasswordText(true);
loginBtn = new GUIButton(test_button, "Login", NULL, 400, 500, 0, 0, 128, 32);
	}


	void Update(){


	}
	void DrawLoginMenu(){
		textUser->Draw();
		textPass->Draw();
		loginBtn->Draw();
		if(msgbox!=nullptr){
			msgbox->Draw();
		}
	}

	void Draw(Entity *player){

		gmenu->Draw();

if(bagWindow->isVisible()){
		bagWindow->Draw();

			float startX = bagWindow->getX()+26;
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

		actionBar->Draw();
		for(int i=0;i<actionBarItems.size();i++){
			if(actionBarItems[i]!=nullptr){
			actionBarItems[i]->Draw();
		}
		}
	//	hpBar->Draw();
	}

	bool checkMouseClick(double mousex, double mousey){
   if(gmenu->checkMouseClick(mousex,  mousey)){
		 return true;
	 }
	 if(loginMenu){
	 if(textUser->checkMouseClick(mousex,mousey)){
		 focusText=textUser;
		 typing=true;
		 return true;
	 }
	 if(textPass->checkMouseClick(mousex,mousey)){
		 focusText=textPass;
		 typing=true;
		 return true;
	 }
	 if(loginBtn->checkMouseClick(mousex,mousey)){
		 std::cout<<"Login button click\n";
		 focusText=nullptr;

		 if (!network->sendLogin(textUser->getText(), textPass->getText())){
			 createMessageBox("Failed to connect to server.");
		 }
		return true;
	}
 }
 if(msgbox!=nullptr){
	 if(msgbox->checkMouseClick(mousex,mousey)){
		 delete(msgbox);
		 msgbox=nullptr;
		 return true;
	 }
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
void clearChat(){
	textArea->setText("");
}
void keyPressed(int key){
//	textfield->setText((std::string)textfield->getText()+key);
//std::cout<<key<<std::endl;
std::string text;
if(focusText ==nullptr){
text= textfield->getText();
}else{
	text = focusText->getText();
}

if(key==257){
	if(typing && text!=""){

	network->sendMessage(text);
	if(focusText ==nullptr){
	textfield->setText("");
}
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
	if(focusText ==nullptr){
textfield->setText(text);
}else{
	focusText->setText(text);
}
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

void setMsgBox(GUIMessagebox *_msgbox){
	if(msgbox!=nullptr){
		delete(msgbox);
	}
	msgbox=_msgbox;
}
void createMessageBox(std::string msg){
	setMsgBox(new GUIMessagebox( msg));
}
void setNetworkClient(NetworkClient * client){
	network = client;
}
};

#endif
