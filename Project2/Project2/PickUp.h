#ifndef __GAME_PICKUP_H
#define __GAME_PICKUP_H
#include "GameObject.h"

class PickUp:public GameObject{

private:

public:

  PickUp(SpriteSheet * sp, float pos_x, float pos_y):GameObject(sp,pos_x,pos_y){

	}
  void Draw(Camera * cam){
    GameObject::Draw(cam);
  }




};

#endif
