#ifndef __KAL__SHADERS_H__
#define __KAL__SHADERS_H__
#include <string>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/glew.h>
#define  COLOR_ATTRIB 0 
class Shaders{
public:
	static const GLchar* VertexShaderSource;
	static const GLchar *FragmentShaderSource;
	GLuint prog;
	 void compileShaders(){
		std::cout << "Building shader programs\n";
		GLuint vertextShader, fragmentShader;
		prog = glCreateProgram();
    	vertextShader = glCreateShader(GL_VERTEX_SHADER_ARB);
     	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER_ARB);
		glShaderSourceARB(vertextShader, 1,&VertexShaderSource,NULL );
		glShaderSourceARB(fragmentShader, 1, &FragmentShaderSource, NULL);
		GLint compiled;
		glCompileShaderARB(vertextShader);
		glCompileShaderARB(fragmentShader);
		glAttachObjectARB(prog, vertextShader);
		glAttachObjectARB(prog, fragmentShader);
		glBindAttribLocation(prog, COLOR_ATTRIB, "color");
		glLinkProgramARB(prog);
		glUseProgramObjectARB(prog);
	
		
	}
	 void disableShaders(){
		 glUseProgramObjectARB(0);

	 }
	 void enableShaders(){
		 glUseProgramObjectARB(prog);

	 }
	 GLuint getProgram(){
		 return prog;
	 }
};
const GLchar *Shaders::VertexShaderSource = ""

"void main(void) {"


		"}";
const GLchar *Shaders::FragmentShaderSource = ""
"varying LOWP vec4 vColor;"
"varying vec2 vTexCoord;"
"uniform sampler2D u_texture;"
"uniform LOWP vec4 ambientColor;"
"void main(void) {"
"vec4 diffuseColor = texture2D(u_texture, vTexCoord);"
"  vec3 ambient = ambientColor.rgb * ambientColor.a;"
"vec3 final = vColor * diffuseColor.rgb * ambient;"
"gl_FragColor = vec4(1.0,0.0,0.0, 1.0);"
"}";

#endif