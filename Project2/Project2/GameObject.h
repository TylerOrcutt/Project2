/**************************************
*GameObject.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __GAME_OBJECT_H_
#define __GAME_OBJECT_H_
#include <string>
#include "Sprite.h"
#include "Camera.h"
class GameObject {
private:
  Sprite *sprite;
	float posx = 0, posy = 0, width=32, height=32, imgx = 0, imgy = 0, imgw = 32, imgh = 32;
  bool visible=true;
  std::string name;
public:
  GameObject(SpriteSheet * sp, float pos_x, float pos_y){
		sprite = new Sprite(sp);
		posx = pos_x;
		posy = pos_y;
	}
  virtual void Update(double dt){

  }
  virtual void Draw(Camera* cam){
    if(visible){
      if (posx >= cam->getX() - imgw && posx <= cam->getX() + cam->getWidth() && posy >= cam->getY() - imgh && posy <= cam->getY() + cam->getHeight()){

        sprite->Draw(posx - cam->getX(), posy - cam->getY(),  width, height, imgx, imgy,imgw, imgh);
      }
  }
  }
  virtual	bool checkMouseClick(double mousex, double mousey){
    if(!visible){
      return false;
    }
  		if (mousex >= posx && mousex <= posx + imgw && mousey >= posy && mousey <= posy + imgh){
  			return true;
  		}
  		return false;

  	}


  float getX(){
    return posx;
  }
  void setX(float _x){
    posx=_x;
  }

  float getY(){
    return posy;
  }
  void setY(float _y){
    posy=_y;
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


    void setName(std::string _name){
      name=_name;
    }
    std::string getName(){
      return name;
    }

};
#endif
