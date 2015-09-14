/**************************************
*TextRenderer.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __TEXTRENDERER_H_
#define __TEXTRENDERER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <sstream>
#include <iostream>
#include <pango/pangocairo.h>
#include <string>
#include <stdlib.h>
#pragma comment(lib, "gobject-2.0.lib")
class TextRenderer{
private:
	GLuint texture;
	int width, height;
	float x = 0, y = 0;
	float objectWidth = 32, objectHeight = 32;
	std::string text;
	int fontSize = 16;
	int padding = 0;
	std::string font = "arial";
public:
	~TextRenderer(){
		glDeleteTextures(1, &texture);
	}
	TextRenderer(float posx,float posy,std::string text_str){
		text=text_str;
		x=posx;
		y=posy;
		initText();
	}
	
	void initText(){
		glDeleteTextures(1, &texture);
		std::string temp_text=text;
		cairo_t *render_context;
		cairo_surface_t *surface;
		unsigned char * surface_data = NULL;
		PangoFontDescription *desc;

		cairo_t *layout_context = create_layout_context();
		PangoLayout *layout= pango_cairo_create_layout(layout_context);

		if(objectHeight>32.f){
			pango_layout_set_width(layout,objectWidth*PANGO_SCALE);
			pango_layout_set_wrap(layout,PANGO_WRAP_WORD);
		}
	
		pango_layout_set_text(layout,temp_text.c_str(),-1);
		pango_layout_set_markup(layout, temp_text.c_str(), strlen(temp_text.c_str()));
		std::stringstream ssize;
		ssize<<fontSize;
		
		desc = pango_font_description_from_string(((std::string)(font + " " + ssize.str())).c_str());
		pango_layout_set_font_description(layout,desc);
		pango_font_description_free(desc);
		
		//get size
		pango_layout_get_size(layout,&width,&height);
		width/=PANGO_SCALE;
		height/=PANGO_SCALE;
		
		//create context
		surface_data=(unsigned char*)calloc(4*width*height,sizeof(unsigned char));
		surface =cairo_image_surface_create_for_data(surface_data, CAIRO_FORMAT_ARGB32,width,height,4 * width);
		render_context=cairo_create(surface);
		
		cairo_set_source_rgba(render_context,1.0f,1.0f,1.0f,1.0f);
		pango_cairo_update_layout(render_context, layout);
		pango_cairo_show_layout(render_context, layout);
		
		unsigned char *data=cairo_image_surface_get_data (surface);
		create_texture(data);
		//cairo_surface_write_to_png (surface, "Test.png");
		g_object_unref(layout);
		free (surface_data);
		
		cairo_destroy (layout_context);
		cairo_destroy (render_context);
		cairo_surface_destroy (surface);
		
	}

	cairo_t * create_layout_context(){
		cairo_surface_t *temp;
		cairo_t * context;
		temp = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 0, 0);
		context= cairo_create(temp);
		cairo_surface_destroy(temp);
		return context;
	}

	void create_texture(unsigned char *pixels){
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D (GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_BGRA,GL_UNSIGNED_BYTE, pixels);
	}

	void Draw(){
		glBindTexture (GL_TEXTURE_2D, texture);
		glColor3f (1.f,1.f,1.f);

		float w=0,h=0;
		float maxW=1.f,maxH=1.f;
		float	maxWidth=width;
		float maxHeight=height;

if(width+(padding)<objectWidth){
	maxWidth+=padding;
}
		if(objectWidth>32 && objectHeight==32.f){
			if(width>(objectWidth-padding)){
				maxWidth=(objectWidth-padding);
				w=1.f-((1.0f/width)*(objectWidth-padding));
			}
		}

		if(objectHeight>32){
			if(width>objectWidth){
				maxWidth=objectWidth;
				maxW =((1.f/width)*objectWidth);
			}
			if(height>(objectHeight-(padding))){
				maxHeight=(objectHeight-(padding));
				h=1.f-((1.0f/height)*(objectHeight-(padding)));
			}
		}

		glBegin (GL_QUADS);
		glTexCoord2f (w, h);
		glVertex2f ((x+padding), y+5);

		glTexCoord2f (maxW, h);
		glVertex2f (x+maxWidth, y+5);

		glTexCoord2f (maxW, maxH);
		glVertex2f (x+maxWidth , y+maxHeight+5);

		glTexCoord2f (w, maxH);
		glVertex2f (x+padding, y+maxHeight+5);
		glEnd ();
	}

	//getters/setters
	void setText(std::string _text){
		text=_text;
		initText();
	}

	std::string getText(){
		return text;
	}

	int getWidth(){
		return width;
	}

	int getHeight(){
		return height;
	}

	void setX(float _x){
		x=_x;
	}

	float getX(){
		return x;
	}

	void setY(float _y){
		y=_y;
	}

	float getY(){
		return y;
	}

	void setFont(std::string _font){
		font=_font;
		initText();
	}

	void setFontSize(int _fontSize){
		fontSize = _fontSize;
		initText();
	}

	void setObjectWidth(float _width){
		objectWidth=_width;
	}

	void setObjectHeight(float _height){
		objectHeight=_height;
	}

	void setPadding(float _padding){
		padding=_padding;
	}
};
#endif
