/**************************************
*SpriteSheet.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __SPRITESHEET_H_
#define __SPRITESHEET_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <string>
#include <iostream>
class SpriteSheet{

private:
	GLuint texture;
	int texture_height;
	int texture_width;
public:
	SpriteSheet(){
	Load("peon");
    }
	SpriteSheet(std::string file){
		Load(file);
    }
	void Load(std::string file){
		//std::cout << file << std::endl;
		file = "./images/" + file + ".png";
		texture = SOIL_load_OGL_texture(file.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
			);
		glBindTexture(GL_TEXTURE_2D, texture);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texture_width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texture_height);

		}
	GLuint getTexture(){
		return texture;
	}
	int getWidth() { return texture_width; }
	int getHeight() { return texture_height; }
};

#endif
