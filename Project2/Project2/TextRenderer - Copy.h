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
	error=FT_Init_FreeType(&library);
	if (error)
	{
		std::cout << "Error loading freetype\n";
	}
	
	error=FT_New_Face(library, "./fonts/arial.ttf", 0, &face);
	if (error){
		std::cout << "Error loading font\n";
	}
	error=FT_Set_Pixel_Sizes(face, 0, 20);
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
		FT_BitmapGlyph bitmap_g = (FT_BitmapGlyph)glyph;
		FT_Bitmap &bitmap = bitmap_g->bitmap;
     	int width = next_p2(bitmap.width);
		int height = next_p2(bitmap.rows);


		GLubyte *data = new GLubyte[2 * width*height];
		for (int j = 0; j < height; j++) for (int i = 0; i < width; i++) {
			data[2 * (i + j*width)] = 255;
			data[2 * (i + j*width) + 1] =
				(i >= bitmap.width || j >= bitmap.rows) ?
				0 : bitmap.buffer[i + bitmap.width*j];
		}
		glBindTexture(GL_TEXTURE_2D, textures[ch]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, data);
		delete[] data;
		glNewList(list_base + ch, GL_COMPILE);

		glBindTexture(GL_TEXTURE_2D, textures[ch]);

		glPushMatrix();

		// First We Need To Move Over A Little So That
		// The Character Has The Right Amount Of Space
		// Between It And The One Before It.
		glTranslatef(bitmap_g->left, 0, 0);

		// Now We Move Down A Little In The Case That The
		// Bitmap Extends Past The Bottom Of The Line
		// This Is Only True For Characters Like 'g' Or 'y'.
		glTranslatef(0, bitmap_g->top - bitmap.rows, 0);

		// Now We Need To Account For The Fact That Many Of
		// Our Textures Are Filled With Empty Padding Space.
		// We Figure What Portion Of The Texture Is Used By
		// The Actual Character And Store That Information In
		// The x And y Variables, Then When We Draw The
		// Quad, We Will Only Reference The Parts Of The Texture
		// That Contains The Character Itself.
		float   x = (float)bitmap.width / (float)width,
			y = (float)bitmap.rows / (float)height;

		// Here We Draw The Texturemapped Quads.
		// The Bitmap That We Got From FreeType Was Not
		// Oriented Quite Like We Would Like It To Be,
		// But We Link The Texture To The Quad
		// In Such A Way That The Result Will Be Properly Aligned.
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2f(0, bitmap.rows);
		glTexCoord2d(0, y); glVertex2f(0, 0);
		glTexCoord2d(x, y); glVertex2f(bitmap.width, 0);
		glTexCoord2d(x, 0); glVertex2f(bitmap.width, bitmap.rows);
		glEnd();
		glPopMatrix();
		glTranslatef(face->glyph->advance.x >> 6, 0, 0);

		// Increment The Raster Position As If We Were A Bitmap Font.
		// (Only Needed If You Want To Calculate Text Length)
		// glBitmap(0,0,0,0,face->glyph->advance.x >> 6,0,NULL);

		// Finish The Display List
		glEndList();
		FT_Done_Glyph(glyph);
	}

	int next_p2(int a){
		int rval = 2;
		while (rval < a){
			rval <<= 1;
		}
		return rval;
	}

	inline void pushScreenCoordinateMatrix() {
		glPushAttrib(GL_TRANSFORM_BIT);
		GLint   viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
		glPopAttrib();
	}

	// Pops The Projection Matrix Without Changing The Current
	// MatrixMode.
	inline void pop_projection_matrix() {
		glPushAttrib(GL_TRANSFORM_BIT);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();
	}
	void DrawText(const char *fmt, float x, float y){
	  pushScreenCoordinateMatrix();
	  /**/
	  GLuint font = ft_font.list_base;
	  // We Make The Height A Little Bigger.  There Will Be Some Space Between Lines.
	  float h = ft_font.h / .63f;
	  char    text[256];                                  // Holds Our String
	  va_list ap;                                     // Pointer To List Of Arguments

	  if (fmt == NULL)                                    // If There's No Text
		  *text = 0;                                    // Do Nothing
	  else {
		  va_start(ap, fmt);                              // Parses The String For Variables
		  vsprintf(text, fmt, ap);                            // And Converts Symbols To Actual Numbers
		  va_end(ap);                                 // Results Are Stored In Text
	  }

	  // Here Is Some Code To Split The Text That We Have Been
	  // Given Into A Set Of Lines. 
	  // This Could Be Made Much Neater By Using
	  // A Regular Expression Library Such As The One Available From
	  // boost.org (I've Only Done It Out By Hand To Avoid Complicating
	  // This Tutorial With Unnecessary Library Dependencies).
	  const char *start_line = text;
	  vector<string> lines;
	  for (const char *c = text; *c; c++) {
		  if (*c == '\n') {
			  string line;
			  for (const char *n = start_line; n<c; n++) line.append(1, *n);
			  lines.push_back(line);
			  start_line = c + 1;
		  }
	  }
	  if (start_line) {
		  string line;
		  for (const char *n = start_line; n<c; n++) line.append(1, *n);
		  lines.push_back(line);
	  }

	  glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
	  glMatrixMode(GL_MODELVIEW);
	  glDisable(GL_LIGHTING);
	  glEnable(GL_TEXTURE_2D);
	  glDisable(GL_DEPTH_TEST);
	  glEnable(GL_BLEND);
	  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	  glListBase(font);




	/*  float basex = x;
		for(unsigned int i=0;i<txt.length();i++){
			if (txt.substr(i, 1) == "\n"){
				y += 30;
				x = basex;
				continue;
			}
		//	glColor3f(1.f, 0.f, 0.f);
			glBindTexture(GL_TEXTURE_2D, textures[txt.c_str()[i]]);
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);
			    glVertex2f(x, y);

				glTexCoord2f(0, 1);
				glVertex2f(x, y+20);

				glTexCoord2f(1, 1);
				glVertex2f(x+20, y + 20);


				glTexCoord2f(1, 0);
				glVertex2f(x + 20, y );

			glEnd();

			x += 20;
			}
			/**/
		}


	
};



#endif
