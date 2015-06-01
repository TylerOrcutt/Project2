#ifndef __CAMERA_H_
#define __CAMERA_H_
class Camera{
private:
	float x=0, y=0,width=1024,height=768;
	bool moving = false;
	int direction = 0;//0-up  1-right 2-down 3-left
public:
	Camera(){

	}
	void Update(){


	}

	float getX(){
		return x;
	}
	float getY(){
		return y;
	}
	void setX(float _x){
		x = _x;
	}
	void setY(float _y){
		y = _y;
	}
	float getWidth(){
		return width;
	}
	void setWidth(float _width){
		width=_width;
	}
		
	float getHeight(){
		return height;
	}
	void setHeight(float _height){
		height=_height;
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
 

};
#endif
