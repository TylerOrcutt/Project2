/**************************************
*GUIObject.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __GUIOBJECT_H_
#define __GUIOBJECT_H_
//manage all gui things
#include "../Sprite.h"
#include "../SpriteSheet.h"
#include "TextRenderer.h"
#include <string>
class GUIObject{
private:
	Sprite *sprite;
	float posx = 0, posy = 0, width=32, height=32, imgx = 0, imgy = 0, imgw = 32, imgh = 32;
	bool visible = true;
std::string  Name;


public:
	~GUIObject(){
		//delete sprite;

	}
	GUIObject(){
		
	}
	GUIObject(SpriteSheet * sp){
		sprite = new Sprite(sp);
	}

	GUIObject(SpriteSheet * sp, float pos_x, float pos_y){
		sprite = new Sprite(sp);
		posx = pos_x;
		posy = pos_y;
	}
	GUIObject(SpriteSheet * sp, float pos_x, float pos_y, float image_x, float image_y){
		sprite = new Sprite(sp);
		posx = pos_x;
		posy = pos_y;
		imgx = image_x;
		imgy = image_y;


	}

	GUIObject(SpriteSheet * sp, float pos_x, float pos_y, float image_x, float image_y, float image_width, float image_height){
		sprite = new Sprite(sp);
		posx = pos_x;
		posy = pos_y;
		imgx = image_x;
		imgy = image_y;
		imgw = image_width;
		imgh = image_height;
		width=image_width;
		height=image_height;

	}

	virtual void Update(){


	}

	virtual void Draw(){
		if(visible){
		sprite->Draw(posx , posy, width,height, imgx, imgy, imgw, imgh);
	}
	}

	virtual bool checkMouseClick(float mousex, float mousey){
		if(visible){
		if (mousex >= posx && mousex <= posx + width && mousey >= posy && mousey <= posy + height){
			return true;
		}
	}
		return false;

	}
	//getters and setters
	float getX(){
		return posx;
	}
	void setX(float _x){
		posx = _x;
	}
	float getY(){
		return posy;
	}
	void setY(float _y){
		posy = _y;
	}
void setPosition(float x, float y){
	posx=x;
	posy=y;
}
void setWidth(float _width){
	width=_width;
}
float getWidth(){
	return width;
}

float setHeight(float _height){
	height=_height;
}
float getHeight(){
	return height;
}

	float getImgX(){
		return imgx;
	}
	void setImgX(float x){
		imgx = x;
	}

	float getImgY(){
		return imgy;
	}
	void setImgY(float y){
		imgy = y;
	}


	float getImgW(){
		return imgw;
	}
	void setImgW(float w){
		imgw = w;
	}


	float getImgH(){
		return imgh;
	}
	void setImgH(float h){
		imgh = h;
	}

	bool isVisible(){
		return visible;
	}
	void setVisible(bool vis){
		visible = vis;
	}
	Sprite* getSprite(){
		return sprite;
	}
	void setSprite(Sprite *sp){
		sprite = sp;
	}

std::string name(){
return Name;
}
void  name(std::string _name){
	Name=_name;
}
	virtual std::string kindOf(){
		return "GUIObject";
	}
};

#endif
