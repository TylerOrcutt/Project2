/**************************************
*Entity.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __ENTITY_H_
#define __ENTITY_H_
#include "Sprite.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include "GUI/TextRenderer.h"
class Entity{
private:
	Sprite *sprite;
	float posx=0, posy=0, imgx=0, imgy=0, imgw=32, imgh=32,width=32,height=32;
	bool moving = false;
	int direction = 0;//0-up  1-right 2-down 3-left

	 Entity * target=nullptr;
//stats and shiiit
	 TextRenderer *textRend = nullptr;
	std::string name;
	int hp = 100;
	int max_hp = 100;
	float speed = 3;

	void initNameText(){
		if (textRend != nullptr){
			delete(textRend);
		}
		textRend = new TextRenderer(0, 0, name);
		textRend->setPadding(0);

	}
public:
	~Entity(){
		delete (sprite);
		if (textRend != nullptr){
			delete(textRend);
		}
	}
	Entity(SpriteSheet * sp){
		sprite= new Sprite(sp);
	}

	Entity(SpriteSheet * sp, float pos_x, float pos_y){
		sprite = new Sprite(sp);
		posx = pos_x;
		posy = pos_y;
	}
	Entity(SpriteSheet * sp, float pos_x, float pos_y, float image_x, float image_y ){
		sprite = new Sprite(sp);
		posx = pos_x;
		posy = pos_y;
		imgx = image_x;
		imgy = image_y;
	}

	Entity(SpriteSheet * sp, float pos_x, float pos_y, float image_x, float image_y, float image_width, float image_height){
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


	//should switch camera to a pointer
	virtual void Draw(Camera cam){
		
		if (posx >= cam.getX() - imgw && posx <= cam.getX() + cam.getWidth() && posy >= cam.getY() - imgh && posy <= cam.getY() + cam.getHeight()){
			DrawNameText(&cam);
			sprite->Draw(posx - cam.getX(), posy - cam.getY(), width,height, imgx, imgy,imgw, imgh);
		}


	}
	virtual void DrawNameText(Camera *cam){
		if (textRend != nullptr){
			float x = (posx - cam->getX())+(width/2)-(textRend->getWidth()/2);
			float y = (posy - cam->getY())-textRend->getHeight()-3;
			textRend->setX(x);
			textRend->setY(y);
			textRend->Draw();
		}
	}

	virtual void Update(double dt){
		if(hp<=0){
			//visible=false;
		}

	}

	bool checkMouseClick(double mousex, double mousey){
		if (mousex >= posx && mousex <= posx + width && mousey >= posy && mousey <= posy + height){
			return true;
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

	void resize(float w,float h){
		width=w;
		height=h;
	}
	float getWidth(){
		return width;
	}
	float getHeight(){
		return height;
	}

	float getImgW(){
		return imgw;
	}
	void setImgW(float w){
		imgw= w;
	}


	float getImgH(){
		return imgh;
	}
	void setImgH(float h){
		imgh = h;
	}


	bool isMoving(){
		return moving;
	}
	void setMoving(bool mov){
		moving = mov;
	}
	int getDirection(){
		return direction;
	}
	void setDirection(int dir){
		direction = dir;
	}

	Sprite* getSprite(){
		return sprite;
	}
	void setSprite(Sprite *sp){
		sprite = sp;
	}


	Entity * getTarget(){
		return target;
	}
	void setTarget(Entity * _target){
		target = _target;
	}

	int getHP(){
		return hp;
	}
	void setHP(int _hp){
		hp = _hp;
	}
	int getMaxHP(){

		return max_hp;
	}
	void setMaxHP(int _maxhp){
		max_hp = _maxhp;
	}

	std::string getName(){
		return name;
	}
	void setName(std::string _name){
		name = _name;
		initNameText();
	}
	int getSpeed(){
		return speed;
	}
void setSpeed(int _speed){
	speed=_speed;
}
};
#endif
