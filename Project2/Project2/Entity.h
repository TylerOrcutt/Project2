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
class Entity{
private:
	Sprite *sprite;
	float posx=0, posy=0, imgx=0, imgy=0, imgw=32, imgh=32;
	bool moving = false;
	int direction = 0;//0-up  1-right 2-down 3-left

	 Entity * target=nullptr;
//stats and shiiit
	std::string name;
	int hp = 100;
	int max_hp = 100;
	float speed = 3;
public:

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

	}



	virtual void Draw(Camera cam){
		if (posx >= cam.getX() - imgw && posx <= cam.getX() + cam.getWidth() && posy >= cam.getY() - imgh && posy <= cam.getY() + cam.getHeight()){

			sprite->Draw(posx - cam.getX(), posy - cam.getY(), imgw, imgh, imgx, imgy);
		}


	}

	virtual void Update(double dt){
		if(hp<=0){
			//visible=false;
		}

	}

	bool checkMouseClick(double mousex, double mousey){
		if (mousex >= posx && mousex <= posx + imgw && mousey >= posy && mousey <= posy + imgh){
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
	}
	int getSpeed(){
		return speed;
	}
void setSpeed(int _speed){
	speed=_speed;
}
};
#endif
