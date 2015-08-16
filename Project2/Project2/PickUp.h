#ifndef __GAME_PICKUP_H
#define __GAME_PICKUP_H
#include "GameObject.h"
#include <GLFW/glfw3.h>
class PickUp:public GameObject{

private:
double respawnStart=0;
int respawnTime=5;
public:

  PickUp(SpriteSheet * sp, float pos_x, float pos_y):GameObject(sp,pos_x,pos_y){

	}
  void Draw(Camera * cam){
    GameObject::Draw(cam);
  }

  void Update(double dt){
    if(GameObject::isVisible()){
      return;
    }
    if( glfwGetTime()-respawnStart>=respawnTime){
      GameObject::setVisible(true);
    }

  }
bool checkMouseClick(double mousex, double mousey){
  if(GameObject::checkMouseClick(mousex,mousey)){
    if(respawnTime!=0){
      respawnStart= glfwGetTime();
    }
    return true;
  }
  return false;
}



};


#endif
