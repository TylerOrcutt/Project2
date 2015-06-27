#ifndef __TEXTRENDERER_H_
#define __TEXTRENDERER_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <pango/pangocairo.h>
#include <string>
#include <stdlib.h>


class TextRenderer{
private: GLuint texture;
	int width, height;
float x,y;

   public:
	void initText(std::string text){
		x=300.f;
		y=300.f;
		cairo_t *render_context;
		cairo_surface_t *temp_surface;
		cairo_surface_t *surface;
     		unsigned char * surface_data = NULL;
		PangoFontDescription *desc;
		
		cairo_t *layout_context = create_layout_context();
		PangoLayout *layout=pango_cairo_create_layout (layout_context);
		pango_layout_set_text(layout,text.c_str(),-1);
		
		desc = pango_font_description_from_string("Sans Bold 27");
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

		 cairo_set_source_rgba(render_context,1.f,1.f,1.f,1.f);

		
pango_cairo_update_layout(render_context, layout);
	pango_cairo_show_layout(render_context, layout);
		texture=create_texture(width,height,surface_data);

    free (surface_data);
    g_object_unref (layout);
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



 GLuint create_texture(unsigned int width,unsigned int height, unsigned char *pixels){
	GLuint texture;
	
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D,texture);
       glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D (GL_TEXTURE_2D,
                  0,
                  GL_RGBA,
                  width,
                  height,
                  0,
                  GL_BGRA,
                  GL_UNSIGNED_BYTE,
                  pixels);

	return texture;
}

	

	void Draw(){
		 glBindTexture (GL_TEXTURE_2D, texture);
                     glColor3f (0.f,0.f,0.f);

                      glBegin (GL_QUADS);
                      
                       glTexCoord2f (0.0f, 0.0f);
                       glVertex2f (x, y);
   
                       glTexCoord2f (1.0f, 0.0f);
                       glVertex2f (x+width, y);
  
                       glTexCoord2f (1.0f, 1.0f);
                       glVertex2f (x+width , y+height);
   
                       glTexCoord2f (0.0f, 1.0f);
                       glVertex2f (x, y+height);
                       glEnd ();

	            }


};


#endif
