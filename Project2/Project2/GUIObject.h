#ifndef __GUIOBJECT_H_
#define __GUIOBJECT_H_
//manage all gui things
#include "Sprite.h"
#include "SpriteSheet.h"

class GUIObject{
private:
	Sprite *sprite;
	float posx = 0, posy = 0, imgx = 0, imgy = 0, imgw = 32, imgh = 32;
	bool visible = true;


public:
	~GUIObject(){
		//delete sprite;
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

	}

	virtual void Update(){


	}

	virtual void Draw(){
		sprite->Draw(posx , posy, imgx, imgy, imgw, imgh);
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
};

#endif