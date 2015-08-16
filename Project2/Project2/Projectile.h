/**************************************
* Projectile.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __PROJECTILE_H_
#define __PROJECTILE_H_
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Camera.h"
#include "Entity.h"
#include <math.h>
class Projectile {
private:
  Sprite *sprite;
  float posx = 0, posy = 0, width=16, height=16, imgx = 0, imgy = 0, imgw = 32, imgh = 32;
  bool visible=true;
  float damage=10;
  float targetX=0,targetY=0;
  float speed=5;
  float maxDistance = 500;
  float distance=0;
  Entity * target=nullptr;
public:
  Projectile(SpriteSheet *sp){
    sprite = new Sprite(sp);
  }
  Projectile(SpriteSheet *sp,float x, float y){
    sprite = new Sprite(sp);
    posx=x;
    posy=y;
  }

  virtual void Update( double dt){
    if(!visible){
      return;
    }
    if(target==nullptr){
      visible=false;
      return;
    }
    float angle = atan2(target->getY()-posy,target->getX()-posx);

    float incX=(cos(angle)*speed)*dt;
    float incY=(sin(angle)*speed)*dt;
    posx+=incX;
    posy+= incY;
    distance+=abs(incX)+abs(incY);
    //std::cout<<distance<<std::endl;
    if(distance >=maxDistance){
      visible=false;
      return;
    }
    if(collide()){
      visible=false;
      target->setHP(target->getHP()-damage);
    }

  }
  virtual bool collide(){
    if(target==nullptr){
      return true;
    }
    if(target->getX()>posx && target->getX()<posx+width && target->getY()>posy && target->getY()<posy+height){
      return true;
    }
    return false;
  }

  virtual void Draw(Camera *cam){
    if(visible){
      if (posx >= cam->getX() - imgw && posx <= cam->getX() + cam->getWidth() && posy >= cam->getY() - imgh && posy <= cam->getY() + cam->getHeight()){

        sprite->Draw(posx - cam->getX(), posy - cam->getY(),  width, height, imgx, imgy,imgw, imgh);
      }
  }
  }
  virtual void Draw(float x,float y){

  }
void setTarget(Entity *ent){
  target=ent;
}
  void setPosition(float x, float y){
    posx=x;
    posy=y;
  }
  void setTargetPosition(float x, float y){
    targetX=x;
    targetY=y;

  }
  bool isVisible(){
    return visible;
  }

};
#endif
