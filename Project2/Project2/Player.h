/**************************************
*Player.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __PLAYER_H_
#define __PLAYER_H_
#include "Entity.h"
#include <GLFW/glfw3.h>
#include<ctime>
#include<iostream>
class Player: public Entity{

private:
	double lastUpdate=0, curtime=0;

public:
	Player(SpriteSheet * sp):Entity(sp){
		// lastupdate=clock(); curtime=clock();
	}

	Player(SpriteSheet * sp, float pos_x, float pos_y):Entity(sp,pos_x,pos_y){
 //lastupdate=clock(); curtime=clock();
	}

	Player(SpriteSheet * sp, float pos_x, float pos_y, float image_x, float image_y, float image_width, float image_height) :Entity(sp, pos_x, pos_y,image_x,image_y,image_width,image_height){

		//lastupdate=clock(); curtime=clock();
	}



	void Update(long dt){
		if (Entity::isMoving()){


			int dir = Entity::getDirection();
			float distance = ((float)Entity::getSpeed()*dt)/1000;
			if (dir == 0){
				Entity::setY(Entity::getY() - distance);
				Entity::setImgY(192);
			//	std::cout<<<<std::endl;
			}

			if (dir == 1){
				Entity::setX(Entity::getX() + distance);
				Entity::setImgY(128);
			}
			if (dir == 2){
				Entity::setY(Entity::getY() + distance);
				Entity::setImgY(0);

			}
			if (dir == 3){
				Entity::setX(Entity::getX() - distance);
				Entity::setImgY(64);

			}

			curtime = glfwGetTime();
		curtime*=1000;
		//	 dt = dt- lastUpdate;
		//	long dt =curtime-lastupdate;
		//std::cout << dt << std::endl;
			if ( (curtime-lastUpdate)> (50)){

			Entity::setImgX(Entity::getImgX()+32);
				if (Entity::getImgX() >=128){
					Entity::setImgX(0);
				}
				lastUpdate=curtime;
			}

		}else{
		Entity::setImgX(0);

		}
	}



};
#endif
