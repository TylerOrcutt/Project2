/**************************************
*GUIMessagebox.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __GUIMESSAGEBOX_H_
#define __GUIMESSAGEBOX_H_
#include <string>
#include "GUIObject.h"
#include "GUIButton.h"
#include "GUIWindow.h"
#include "TextRenderer.h"
class GUIMessagebox : public GUIObject{
private:
  GUIWindow *window;
  GUIButton * button;
  TextRenderer *textRenderer= nullptr;
std::string text="";
  void initText(){
    if(textRenderer!=nullptr){
      delete(textRenderer);
    }
    textRenderer = new TextRenderer(GUIObject::getX(),GUIObject::getY(),text);
      textRenderer->setPadding(0);
    int x = (SCREEN_WIDTH/2) - (textRenderer->getWidth()/2);
      int y =(SCREEN_HEIGHT/2) - (textRenderer->getHeight()/2);
    textRenderer->setX(x);
    textRenderer->setY(y);
    window->setX(x-32);
    window->setY(y-32);
    window->resize(textRenderer->getWidth()+32,textRenderer->getHeight()+64);
button->setX(window->getX() +((window->getWidth()/2) -( button->getWidth()/2)));
button->setY(textRenderer->getY()+textRenderer->getHeight()+16);
  }
public:
	~GUIMessagebox(){
	//	std::cout << "Freeing messagebox\n";
		button->getSprite()->freeSpriteSheet();
		window->getSprite()->freeSpriteSheet();
	//	delete(button->getSprite());
		//delete(window->getSprite());
		delete (textRenderer);
		delete(button);
		delete(window);
	}
GUIMessagebox(std::string _text){
  window= new GUIWindow(new SpriteSheet("GUIWindow"),SCREEN_WIDTH/2-256,SCREEN_HEIGHT/2 - 64);
  window->resize(256,128);
  window->setVisible(true);
  text=_text;
    button =new GUIButton(new SpriteSheet("test_button"),"Ok",NULL,400,500,0,0,128,32);
    initText();
}
void Update(){

}
bool checkMouseClick(double mousex, double mousey){
	if(GUIObject::isVisible()){
    if(button->checkMouseClick(mousex,mousey)){

      return true;
    }
    return false;
  }
  return false;
}
void Draw(){
window->Draw();
  if(textRenderer!=nullptr){
  textRenderer->Draw();
}
button->Draw();
}
};
#endif
