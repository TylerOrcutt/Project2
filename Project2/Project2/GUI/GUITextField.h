/**************************************
*GUITextField.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __GUI_TEXTFIELD_H
#define __GUI_TEXTFIELD_H

#include "GUIObject.h"
#include "TextRenderer.h"

#include <string>
class GUITextField : public GUIObject {

  private:
bool editable;
bool multiline=false;
TextRenderer *textRenderer = nullptr;
std::string text;

void updateText(){
  if(textRenderer!=nullptr){
    delete(textRenderer);
  }
  textRenderer = new TextRenderer(GUIObject::getX(),GUIObject::getY(),text);
  textRenderer->setObjectWidth(GUIObject::getWidth());
  textRenderer->setObjectHeight(GUIObject::getHeight());
  textRenderer->setPadding(5);
  textRenderer->setFontSize(11);
  int x = GUIObject::getX();
    int y = GUIObject::getY();
  textRenderer->setX(x);
  textRenderer->setY(y);
  //std::cout<<GUIObject::getHeight()<<std::endl;
textRenderer->setText(text);
}

  public:
  GUITextField(SpriteSheet *sp):GUIObject(sp){
    GUIObject::setX(10);
    GUIObject::setY(560);
    GUIObject::setImgH(32);
    GUIObject::setImgW(32);
    GUIObject::setWidth(300);

    text = "";
    updateText();
  }
  GUITextField(SpriteSheet *sp, float posx, float posy):GUIObject(sp,posx,posy){}
GUITextField(SpriteSheet * sp, float pos_x, float pos_y, float image_x, float image_y, float image_width, float image_height):GUIObject(sp, pos_x, pos_y, image_x, image_y, image_width, image_height){

}
    void Update(){}
  void Draw(){

    GUIObject::Draw();
    if(textRenderer!=nullptr){
      textRenderer->Draw();
    }
  }

void setEditable(bool _editable){
  editable=_editable;
}
bool isEditable(){
  return editable;
}
void setText(std::string _text){
  text=_text;
  updateText();
}
void setMultiLine(bool _multiline){
  multiline=_multiline;
}
bool isMultiLine(){
  return multiline;
}
std::string getText(){
  return text;
}
};

#endif
