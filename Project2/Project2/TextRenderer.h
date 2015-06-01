#ifndef __TEXTRENDERER_H_
#define __TEXTRENDERER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
class TextRenderer{
private:
	FT_Library  library;
	FT_Face face;
	GLuint * textures;
	GLuint  list_base;

public:
	TextRenderer(){
		FT_Error error;
		error = FT_Init_FreeType(&library);
		if (error)
		{
			std::cout << "Error loading freetype\n";
		}

		error = FT_New_Face(library, "./fonts/arial.ttf", 0, &face);
		if (error){
			std::cout << "Error loading font\n";
		}
	/*	error = FT_Set_Pixel_Sizes(face, 0, 20);
		
		*/
	error=	FT_Set_Char_Size(
			face,    /* handle to face object           */
			0,       /* char_width in 1/64th of points  */
			16 * 64,   /* char_height in 1/64th of points */
			300,     /* horizontal device resolution    */
			300);
		
		
			if (error){
			std::cout << "Error setting char size\n";
		}

		textures = new GLuint[128];
		list_base = glGenLists(128);
		glGenTextures(128, textures);
		for (unsigned char i = 0; i < 128; i++){
			createFontChar(i);
		}


	}



	void createFontChar(char ch){
		if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT)){
			std::cout << "Failed to load char:" << ch << std::endl;
		}
		FT_Glyph glyph;
		if (FT_Get_Glyph(face->glyph, &glyph)){

			std::cout << "Failed to load glyph:" << ch << std::endl;
		}

		FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
		FT_GlyphSlot g=face->glyph;
		FT_BitmapGlyph bitmap_g = (FT_BitmapGlyph)glyph;
		FT_Bitmap &bitmap = bitmap_g->bitmap;

		

		//int width = next_p2(bitmap.width);
		//int height = next_p2(bitmap.rows);

		int width = (bitmap.width);
		int height = (bitmap.rows);
		GLubyte *data = new GLubyte[2*width*height];
		/*
		
		for (int j = 0; j <height; j++) {
			for (int i = 0; i < width; i++) {
				data[2 * (i + j * width)] = 255;
				data[2 * (i + j * width) + 1] =
					(i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
			}
		}
		/*
	  for (int j = 0; j < height; j++){
			for (int i = 0; i < width; i++){
				data[i+j] = bitmap.buffer[i+j];
			}
		}
		*/
		glBindTexture(GL_TEXTURE_2D, textures[ch]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);

glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RGBA,
      g->bitmap.width,
      g->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      g->bitmap.buffer
    );
		delete[] data;

		FT_Done_Glyph(glyph);
	}

	int next_p2(int a){
		int rval = 2;
		while (rval < a){
			rval <<= 1;
		}
		return rval;
	}

	void DrawText(std::string txt, float x, float y){
		float basex = x;
		for (unsigned int i = 0; i < txt.length(); i++){
			if (txt.substr(i, 1) == "\n"){
				y += 30;
				x = basex;
				continue;
			}
			//	glColor3f(1.f, 0.f, 0.f);
			glBindTexture(GL_TEXTURE_2D, textures[txt.c_str()[i]]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(x, y);

			glTexCoord2f(0, 1);
			glVertex2f(x, y + 20);

			glTexCoord2f(1, 1);
			glVertex2f(x + 20, y + 20);


			glTexCoord2f(1, 0);
			glVertex2f(x + 20, y);

			glEnd();

			x += 20;
		}
		/**/
	}



	
};



#endif
