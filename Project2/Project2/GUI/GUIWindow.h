#ifndef __GUIWINDOW_H_
#define __GUIWINDOW_H_
//base gui window
#include "GUIObject.h"
#include "GUIButton.h"
#include "../Sprite.h"
#include "../SpriteSheet.h"
#include <vector>
class GUIWindow:public GUIObject{
private:
	//TODO the width and height have to be divisible by 32 - fix this!
	float width=160, height=256;

        std::vector<GUIObject*> components;
public:
	GUIWindow(SpriteSheet * sp) :GUIObject(sp){}
	GUIWindow(SpriteSheet * sp, float pos_x, float pos_y) :GUIObject(sp, pos_x, pos_y){}
	GUIWindow(SpriteSheet * sp, float pos_x, float pos_y, float image_x, float image_y, float image_width, float image_height) :GUIObject(sp, pos_x, pos_y, image_x, image_y, image_width, image_height){}
~GUIWindow(){
	//delete all component objects
	for(int i=0;i<components.size();i++){
		delete(components[i]);
	}
}
	void Update(){
		GUIObject::Update();
	}

	void Draw(){
		if (!GUIObject::isVisible()){
			return;
		}

		//should predraw this
		float px = GUIObject::getX();
		float py = GUIObject::getY();
		for (int h = 0; h < height; h += 32){
			for (int w = 0; w < width; w += 32){
				//top left cornor
				if (h == 0 && w == 0){
					GUIObject::getSprite()->Draw(px, py, 0, 0);

				}
				//top mid
				if (h == 0 && w < width - 32 && w >0){
					GUIObject::getSprite()->Draw(px, py, 32, 0);

				}
				//top right cornor
				if (h == 0 && w == width - 32 && w >0){
					GUIObject::getSprite()->Draw(px, py, 64, 0);

				}
				//left side
				if (h > 0 && h <height-32 && w == 0){
					GUIObject::getSprite()->Draw(px, py, 0, 32);

				}
				//right side
				if (h>0 &&h<height-32 && w == width-32){
					GUIObject::getSprite()->Draw(px, py, 64, 32);

				}

				//bottomleft cornor
				if (h == height - 32 && w == 0){
					GUIObject::getSprite()->Draw(px, py, 0, 64);
				}
				//bottom
				if (h == height - 32 && w >0 && w<width-32){
					GUIObject::getSprite()->Draw(px, py, 32, 64);
				}

				//bottom right cornor
				if (h == height - 32 &&  w==width - 32){
					GUIObject::getSprite()->Draw(px, py, 64, 64);
				}
				//middle
				if (h>0 && h<height - 32 && w>0 && w < width - 32){
					GUIObject::getSprite()->Draw(px, py, 32, 32);
				}

				px += 32;
			}
			px = GUIObject::getX();
			py += 32;
		}
	//MARK - draw components
	for(int i=0;i<components.size();i++){

		components[i]->Draw();

	}
	}

bool checkMouseClick(double mousex, double mousey){
	if(GUIObject::isVisible()){
	for(int i=0;i<components.size();i++){
		if(components[i]->checkMouseClick(mousex, mousey)){
			    //  std::cout<<"button clicked\n";
			return true;
		}
	}
}
	return false;
}

void addComponent(GUIObject *component){
	components.push_back(component);
}
void clearComponents(){
	for(int i=0;i<components.size();i++){
		delete(components[i]);
	}
	components.clear();
}

float getWidth(){
	return width;
}
float getHeight(){
	return height;
}

void resize(float _width, float _height){
if((int)_width%32==0){
width=_width;
}
if((int)_height%32==0){
	height=_height;
}
}



};

#endif
