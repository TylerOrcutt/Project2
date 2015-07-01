#ifndef __GUIBUTTON_H_
#define __GUIBUTTON_H_
#include "TextRenderer.h"
#include <string>
class GUIButton : public GUIObject{
private:
	
     	TextRenderer *text;
	float text_x=0,text_y=0;
        
public:
        GUIButton(SpriteSheet * sp) :GUIObject(sp){
		
	}
	GUIButton(SpriteSheet * sp, float pos_x, float pos_y) :GUIObject(sp, pos_x, pos_y){}
	GUIButton(SpriteSheet * sp, float pos_x, float pos_y, float image_x, float image_y, float image_width, float image_height) :GUIObject(sp, pos_x, pos_y, image_x, image_y, image_width, image_height){}

	void Draw(){
		GUIObject::Draw();
	}


};

	


#endif
