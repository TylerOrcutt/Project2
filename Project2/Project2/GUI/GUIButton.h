#ifndef __GUIBUTTON_H_
#define __GUIBUTTON_H_
#include "TextRenderer.h"
#include "GUI.h"
#include <string>
#include <iostream>
class GUIButton : public GUIObject{
private:

     	TextRenderer *textRenderer=nullptr;
      void(*onClickCallback)(GUIButton *);
			std::string text;
			float text_x=0,text_y=0;
      void initText(){
        textRenderer = new TextRenderer(GUIObject::getX(),GUIObject::getY(),text);
        int x = GUIObject::getX()+(GUIObject::getImgW()/2)-(textRenderer->getWidth()/2);
          int y = GUIObject::getY()+(GUIObject::getImgH()/2)-(textRenderer->getHeight()/2);
        textRenderer->setX(x);
        textRenderer->setY(y-2);
        std::cout<<"text initialized\n";
      }

public:
	GUIButton(SpriteSheet * sp, std::string _text ) :GUIObject(sp){
		text=_text;
		initText();
  //  std::cout<<"text initialized\n";
	}
	GUIButton(SpriteSheet * sp,std::string _text, float pos_x, float pos_y) :GUIObject(sp, pos_x, pos_y){
    text=_text;
  //    std::cout<<"text initialized\n";
    this->initText();

  }
	GUIButton(SpriteSheet * sp, std::string _text,void (*_onClickCallback)(GUIButton *), float pos_x, float pos_y, float image_x, float image_y, float image_width, float image_height):GUIObject(sp, pos_x, pos_y, image_x, image_y, image_width, image_height){
		text=_text;
    onClickCallback=_onClickCallback;
  //    std::cout<<"text initialized\n";
		this->initText();

	}
bool checkMouseClick(float mousex, float mousey){
  if(GUIObject::checkMouseClick((float)mousex,(float)mousey)){
    onClickCallback(this);

    return true;
  }
  return false;
  }

 void Draw(){
   GUIObject::Draw();
		if(textRenderer!=nullptr && GUIObject::isVisible()){
			textRenderer->Draw();
			//std::cout<<"drawing text \n";

		}
	}

	void setText(std::string _text){
		text=_text;
    initText();
	}

	std::string getText() {
		return text;
	}

  std::string kindOf(){
		return "GUIButton";
	}

};




#endif
