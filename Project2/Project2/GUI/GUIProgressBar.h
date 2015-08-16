/**************************************
*GUIProgressBar.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __GUIPROGRESSBAR_H_
#define __GUIPROGRESSBAR_H_
#include "TextRenderer.h"
#include <string>
class GUIProgressBar : public GUIObject{
private:

     	TextRenderer *text;
	float text_x=0,text_y=0;

public:
        GUIProgressBar(SpriteSheet * sp) :GUIObject(sp){

	}
	GUIProgressBar(SpriteSheet * sp, float pos_x, float pos_y) :GUIObject(sp, pos_x, pos_y){}
	GUIProgressBar(SpriteSheet * sp, float pos_x, float pos_y, float image_x, float image_y, float image_width, float image_height) :GUIObject(sp, pos_x, pos_y, image_x, image_y, image_width, image_height){}

	void Draw(){
		GUIObject::Draw();
	}


};




#endif
