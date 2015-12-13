/**************************************
*main.cpp
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>
// Include GLFW

#define GLFW_INCLUDE_GL3
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/glm.hpp>
#include <SOIL/SOIL.h>

#pragma comment(lib, "glfw3")
#pragma comment(lib, "OpenGl32")
#pragma comment(lib, "glew32")

#pragma comment(lib, "SOIL")

#pragma comment(lib, "pango-1.0.lib")
//#pragma comment(lib, "pangowin32-1.0.lib")
#pragma comment(lib, "pangocairo-1.0.lib")
#pragma comment(lib, "cairo")

#pragma comment(lib, "ssleay32.lib")
#pragma comment(lib, "libeay32.lib")
//#pragma comment(lib, "freetype240")
#ifdef _WIN32
//#include<Windows.h>

#endif

#include "Engine.h"
#include "Network/NetworkClient.h"
#include "Settings.h"
#include "LUA/LUAManager.h"
#include "Shaders/Shaders.h"
Engine *engine;
GLFWwindow* window;
//NetworkClient * network;
double mouseX, mouseY;



static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void MouseClick_callback(GLFWwindow * window, int button, int action, int mode){
	/*if (button == 0){
		std::cout << "MouseBTN-left clicked\n X:"<<mouseX<<" Y:"<<mouseY<<"\n";
	}*/
	if (action == GLFW_PRESS){
		engine->MouseClick(button, mouseX, mouseY);
	}
}



static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		// glfwSetWindowShouldClose(window, GL_TRUE);
		//
		if(loginMenu){
		 running=false;
		}
		engine->getGUI()->setGameMenuVisible(!engine->getGUI()->getGameMenuVisible());

	}
	//std::cout<<key<<std::endl;
		if(key == GLFW_KEY_ENTER &&action == GLFW_PRESS){
	//	std::cout<<"enter\n";
		engine->getGUI()->keyPressed(key);
	engine->getGUI()->setTyping(!engine->getGUI()->isTyping());
	return;
}
if(engine->getGUI()->isTyping()){
	if(action == GLFW_PRESS && (key == 340  || key==344)){
		engine->getGUI()->setShiftDown(true);
	//	std::cout<<"ShiftDown\n";
		return;
	}
	if(action == GLFW_RELEASE && (key == 340  || key==344)){
			engine->getGUI()->setShiftDown(false);
	//		std::cout<<"shiftUp\n";
				return;
	}
if(action==GLFW_PRESS){
//	std::cout<<scancode<<std::endl;
	engine->getGUI()->keyPressed(key);
	return;
}
return;
}

if ((key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D) && action == GLFW_RELEASE){
	engine->getPlayer()->setMoving(false);
	engine->getCamera().setMoving(false);
	engine->sendMoving();
	return;
}

if (key == GLFW_KEY_W && action == GLFW_PRESS){
		//engine->getCamera().setMoving(true);
		engine->getCamera().setDirection(0);
		engine->getPlayer()->setMoving(true);
		engine->getPlayer()->setDirection(0);

		engine->sendMoving();
		return;
	} else
	if (key == GLFW_KEY_S && action == GLFW_PRESS){
		//engine->getCamera().setMoving(true);
		engine->getCamera().setDirection(2);
		engine->getPlayer()->setMoving(true);
		engine->getPlayer()->setDirection(2);
		engine->sendMoving();
		return;

	} else

	if (key == GLFW_KEY_A  && action == GLFW_PRESS){
		//engine->getCamera().setMoving(true);
		engine->getCamera().setDirection(3);
		engine->getPlayer()->setMoving(true);
		engine->getPlayer()->setDirection(3);
		engine->sendMoving();
		return;

	}else
	if (key == GLFW_KEY_D && action == GLFW_PRESS){
	//	engine->getCamera().setMoving(true);
		//engine->getCamera().setDirection(1);
		engine->getPlayer()->setMoving(true);
        engine->getPlayer()->setDirection(1);
		engine->sendMoving();
		return;
	}
if ((key == GLFW_KEY_1 || key == GLFW_KEY_2 ) && action == GLFW_PRESS){
	engine->actionBarKey(key);
}



	if (key == GLFW_KEY_B && action == GLFW_PRESS){
		engine->getGUI()->getBagWindow()->setVisible(!	engine->getGUI()->getBagWindow()->isVisible());
	}


}


#if  defined(_WIN32) && !defined(_DEBUG)
	int WINAPI WinMain(
		_In_  HINSTANCE hInstance,
		_In_opt_  HINSTANCE hPrevInstance,
		_In_  LPSTR lpCmdLine,
		_In_  int nCmdShow
		){
#else
int main(int args, char **argv)
{
#endif
	mouseX = 0;
	mouseY = 0;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
std::string title=" v:";
	title.append(GAME_VERSION);

	SCREEN_WIDTH = 800; //1920
	SCREEN_HEIGHT=600; //1080
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str(), NULL, NULL);

	/*
	SCREEN_WIDTH = 1920;
	SCREEN_HEIGHT=1080;
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str(),  glfwGetPrimaryMonitor(), NULL);
	/**///GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
	//glfwSetCursor(window, cursor);

	running=true;
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, MouseClick_callback);
	//GLint GlewInitResult = glewInit();
	//glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);

	Shaders shaders;
	shaders.compileShaders();
	glEnable(GL_LIGHT0);
	
	GLfloat position[] = { 0.f, 0.f, 0.f, -1.f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	GLfloat ambient[] = { 0.5f,0.5f, 0.5f, 1.f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	
	/*
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	GLfloat a[] = { 2.0, 2.0, 2.0, 0.0 };
	GLfloat b[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, a);
	glLightfv(GL_LIGHT0, GL_AMBIENT, b);
	*/
	
	engine = new Engine(&shaders);
//LUAManager lua;
LUAManager::executeLUAFile("",engine->getGUI());

	while (!glfwWindowShouldClose(window) && 	running )
	{
		glfwGetCursorPos(window, &mouseX, &mouseY);
		engine->getGUI()->setMousePos(mouseX, mouseY);
		engine->Update();

		/*
		float ratio;

		ratio = width / (float)height;
		*/

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT);


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glOrtho(-1, 1, -1.f, 1.f, 1.f, -1.f);
		glOrtho(0.0f, 800, 600, 0.0f, 0.0f, 1.0f);
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT=height;
	// update camara
		engine->getCamera().setWidth((float)800);
		engine->getCamera().setHeight((float)600);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();





		glEnable(GL_TEXTURE_2D);
	//	glBindTexture(GL_TEXTURE_2D, texture);



		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glEnable(GL_ALPHA);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);

		glColor3f(1.f,1.f, 1.f);

	//	peon.Draw(0,192,0,0);

	
			engine->Draw();
	

	//	Te


		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);







		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//glfwDestroyCursor(cursor);
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
