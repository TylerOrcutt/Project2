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
  float posx = 0, posy = 0, width=32, height=32, imgx = 0, imgy = 0, imgw = 32, imgh = 32;
  bool visible=true;
  float damage=10;
  float targetX=0,targetY=0;
  float speed=10;
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
    float angle = atan2(posy-target->getY(),posx-target->getX());
    posx+=(cos(angle*speed));
    posy+=(sin(angle*speed));
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
