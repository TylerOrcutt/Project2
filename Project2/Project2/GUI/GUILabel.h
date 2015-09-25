/**************************************
*GUITextLabel.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __GUI_LABEL_H
#define __GUI_LABEL_H

#include "GUIObject.h"
#include "TextRenderer.h"

#include <string>
class GUILabel : public GUIObject {
private:
	TextRenderer *textRenderer = nullptr;
	std::string text;
	void initText(){
		if (textRenderer != nullptr){
			delete(textRenderer);
		}
		textRenderer = new TextRenderer(GUIObject::getX(), GUIObject::getY(), text);
		textRenderer->setPadding(0);
	}
public:
	 GUILabel():GUIObject(){

	}
	 GUILabel(float x,float y) :GUIObject(x,y){ }
	 
	 GUILabel(std::string _text, float  x, float y):GUIObject(x, y){ 
		 text = _text;
		 	 initText();

	 }
	 void Draw(){
		 if (textRenderer != nullptr){
			 textRenderer->Draw();
		 }
	 }
	 void setText(std::string _text){
		 text = _text;
		 initText();
	 }
	 std::string getText(){
		 return text;
	 }
};
#endif