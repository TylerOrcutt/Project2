/**************************************
*main.cpp
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/

#define GAME_VERSION "0.1.0"

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>
// Include GLFW
#define GLFW_INCLUDE_GLU
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
}
	if (key == GLFW_KEY_W){
		//engine->getCamera().setMoving(true);
		engine->getCamera().setDirection(0);
		engine->getPlayer()->setMoving(true);
		engine->getPlayer()->setDirection(0);

	} else
	if (key == GLFW_KEY_S){
		//engine->getCamera().setMoving(true);
		engine->getCamera().setDirection(2);
		engine->getPlayer()->setMoving(true);
		engine->getPlayer()->setDirection(2);

	} else

	if (key == GLFW_KEY_A){
		//engine->getCamera().setMoving(true);
		engine->getCamera().setDirection(3);
		engine->getPlayer()->setMoving(true);
		engine->getPlayer()->setDirection(3);


	}else
	if (key == GLFW_KEY_D){
	//	engine->getCamera().setMoving(true);
		//engine->getCamera().setDirection(1);
		engine->getPlayer()->setMoving(true);
        engine->getPlayer()->setDirection(1);
	}
if ((key == GLFW_KEY_1 || key == GLFW_KEY_2 ) && action == GLFW_PRESS){
	engine->actionBarKey(key);
}

	if ((key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S || key == GLFW_KEY_D) && action == GLFW_RELEASE){
		engine->getPlayer()->setMoving(false);
		engine->getCamera().setMoving(false);
	}

	if (key == GLFW_KEY_B && action == GLFW_PRESS){
		engine->getGUI()->getBagWindow()->setVisible(!	engine->getGUI()->getBagWindow()->isVisible());
	}


}
int main(int args, char **argv)
{

#ifdef _WIN32
	//  FreeConsole();
#endif
	mouseX = 0;
	mouseY = 0;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	//glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
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



engine = new Engine();



	while (!glfwWindowShouldClose(window) && 	running )
	{
		glfwGetCursorPos(window, &mouseX, &mouseY);

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
		glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT=height;
	// update camara
		engine->getCamera().setWidth((float)width);
		engine->getCamera().setHeight((float)height);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();





		glEnable(GL_TEXTURE_2D);
	//	glBindTexture(GL_TEXTURE_2D, texture);



		glEnable(GL_BLEND);
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
