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
std::vector<std::string> text_multi;
int maxStoredLines =50;
int max_lines = 8;
float padding=0;
bool passwordText=false;
void updateText(){
  if(textRenderer!=nullptr){
    delete(textRenderer);
  }
  textRenderer = new TextRenderer(GUIObject::getX(),GUIObject::getY(),"");
  textRenderer->setObjectWidth(GUIObject::getWidth());
  textRenderer->setObjectHeight(GUIObject::getHeight());
  textRenderer->setPadding(5);
  textRenderer->setFontSize(11);
  int x = GUIObject::getX();
    int y = GUIObject::getY();
  textRenderer->setX(x);
  textRenderer->setY(y);
  textRenderer->setPadding(padding);
  //std::cout<<GUIObject::getHeight()<<std::endl;
  std::string temp=text;
  if (multiline){
	  //really should use a linked list for this...
	//  std::cout << "text arraysize: " << text_multi.size() << std::endl;
	  temp = "";
	  if (max_lines < text_multi.size()){
		  for (int i = text_multi.size() - max_lines; i < text_multi.size(); i++){
			  temp += text_multi[i];
		  }
	  }
	  else{
		  for (int i = 0; i < text_multi.size();i++){
			  temp += text_multi[i];
		  }
	  }
  } 
if(passwordText){
  temp = "";
  for(int i=0;i<text.length();i++){
    temp +="*";
  }
}
textRenderer->setText(temp);
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
	  updateText();
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
	if (!multiline){
		text = _text;
	}
	else{
		if (text_multi.size() >= maxStoredLines){
			text_multi.erase(text_multi.begin());
		}
		text_multi.push_back(_text);
		
	}
 //updateText();
}
void setMultiLine(bool _multiline){
  multiline=_multiline;
}
bool isMultiLine(){
  return multiline;
}
void setPadding(float _padding){
  padding=_padding;
}
bool isPasswordText(){
  return passwordText;
}
void setPasswordText(bool _passwd){
  passwordText=_passwd;
}
std::string getText(){
  return text;
}
};

#endif
