#ifndef __SPRITE_H_
#define __SPRITE_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SpriteSheet.h"
#include <iostream>
class Sprite{
private:
	
	SpriteSheet* sprite;

public:
	/*
	Sprite(){
 	
		//init(0,0,0,0);
	}*/
	Sprite(SpriteSheet *sp){
		sprite = sp;
		//init();
	}
	~Sprite(){
		delete sprite;
	}
	void Draw(float posx, float posy, float x, float y){
		float w = 32.f, h = 32.f;
		glBindTexture(GL_TEXTURE_2D, sprite->getTexture());

		glBegin(GL_QUADS);


		float swidth = (1.0f / sprite->getWidth())*w;
		float sheight = (1.0f / sprite->getHeight())*h;


		//std::cout << swidth << std::endl;
		x = (1.0f / sprite->getWidth())*x;
		y = (1.0f / sprite->getHeight())*y;
	//	float y = (((0.0f) / 7.0f));
		//float x = 1, y = 1;
		//float posx = 0;
		//float posy = 0;
	//	float h = 32.f, w = 32.f;
		//top left
		glTexCoord2f(x, y);
		//	glVertex2f(-1+posx, 1.f -(posy+h));
		glVertex2f(posx, (posy));
		//	std::cout << y << std::endl;

		//top right
		glTexCoord2f(x + swidth, y);
		glVertex2f(posx + w, (posy));

		//bottom right

		glTexCoord2f(x + swidth, y + sheight);
		glVertex2f(posx + w, posy + h);

		//bottom left
		glTexCoord2f(x, y + sheight);
		glVertex2f(posx, posy + h);
		/**/
		
		glEnd();
	}

	void Draw(float posx, float posy, float x, float y,float w,float h){
	//	float w = 32.f, h = 32.f;
		glBindTexture(GL_TEXTURE_2D, sprite->getTexture());

		glBegin(GL_QUADS);


		float swidth = (1.0f / sprite->getWidth())*w;
		float sheight = (1.0f / sprite->getHeight())*h;


		//std::cout << swidth << std::endl;
		x = (1.0f / sprite->getWidth())*x;
		y = (1.0f / sprite->getHeight())*y;
	
		glTexCoord2f(x, y);
	
		glVertex2f(posx, (posy));
	

		//top right
		glTexCoord2f(x + swidth, y);
		glVertex2f(posx + w, (posy));

		//bottom right

		glTexCoord2f(x + swidth, y + sheight);
		glVertex2f(posx + w, posy + h);

		//bottom left
		glTexCoord2f(x, y + sheight);
		glVertex2f(posx, posy + h);
		/**/

		glEnd();
	}
	
	void Draw(float posx, float posy, float x, float y, float w, float h, float width, float height ){
		glBindTexture(GL_TEXTURE_2D, sprite->getTexture());

		glBegin(GL_QUADS);


		float swidth = (1.0f / sprite->getWidth())*w;
		float sheight = (1.0f / sprite->getHeight())*h;


		//std::cout << swidth << std::endl;
		x = (1.0f / sprite->getWidth())*x;
		y = (1.0f / sprite->getHeight())*y;
		//	float y = (((0.0f) / 7.0f));
		//float x = 1, y = 1;
		//float posx = 0;
		//float posy = 0;
		//	float h = 32.f, w = 32.f;
		//top left
		glTexCoord2f(x, y);
		//	glVertex2f(-1+posx, 1.f -(posy+h));
		glVertex2f(posx, (posy));
		//	std::cout << y << std::endl;

		//top right
		glTexCoord2f(x + swidth, y);
		glVertex2f(posx + width, (posy));

		//bottom right

		glTexCoord2f(x + swidth, y + sheight);
		glVertex2f(posx + width, posy + height);

		//bottom left
		glTexCoord2f(x, y + sheight);
		glVertex2f(posx, posy + height);
		

		glEnd();
	}

};


#endif