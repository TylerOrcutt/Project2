#ifndef __GAME_ITEM_H_
#define __GAME_ITEM_H_
#include <string>
#include <sstream>

#include "Sprite.h"
#include "SpriteSheet.h"
#include "GUI/TextRenderer.h"
class GameItem {
private:
  Sprite * sprite;
  int maxStack=5;
  int stackCount=1;
  std::string name;
  TextRenderer * textRend=nullptr;
	float posx = 0, posy = 0, width=32, height=32, imgx = 0, imgy = 0, imgw = 32, imgh = 32;

  void initText(){
    if(textRend !=nullptr){
      delete(textRend);
    }
    std::stringstream ss;
    ss<<stackCount;
      textRend = new TextRenderer(posx,posy,ss.str());
      textRend->setFont("arial bold");
      textRend->setFontSize(12);
  }
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
    if(textRend !=nullptr){
      textRend->setX(x+23);
      textRend->setY(y+12);
      textRend->Draw();
    }
  }
  void setName(std::string _name){
    name=_name;
  }
  std::string getName(){
    return name;
  }

  int getMaxStack(){
    return maxStack;
  }
  int getStackCount(){
    return stackCount;
  }
  void incCount(){
    if(stackCount<maxStack){
    stackCount++;
    initText();
  }
  }


};

#endif
