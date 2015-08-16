#ifndef __GAME_ITEM_H_
#define __GAME_ITEM_H_
#include <string>

#include "Sprite.h"
#include "SpriteSheet.h"
class GameItem {
private:
  Sprite * sprite;
  int maxStack=1;
  int stackCount=1;
  std::string name;
	float posx = 0, posy = 0, width=32, height=32, imgx = 0, imgy = 0, imgw = 32, imgh = 32;
public:
  GameItem(){

  }
  GameItem(SpriteSheet *sp){
    sprite = new Sprite(sp);
  }
  GameItem(Sprite *sp){
    sprite = sp;
  }
  virtual void Draw(){
    sprite->Draw(posx , posy, width,height, imgx, imgy, imgw, imgh);
  }
  virtual void Draw(float x,float y){
    sprite->Draw(x , y, width,height, imgx, imgy, imgw, imgh);
  }


};

#endif
