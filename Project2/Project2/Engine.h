#ifndef __ENGINE_H_
#define __ENGINE_H_
#include "Entity.h"
#include "Player.h"
#include "SpriteSheet.h"
#include "Map.h"
#include "Camera.h"
#include "GUI/GUI.h"
#include "GUI/TextRenderer.h"

#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <GLFW/glfw3.h>
class Engine{
private:
	//TODO data struct, hash?
	std::vector<Entity*> entities;

	SpriteSheet * peon;
	 Map *map;
	 Entity*player;
	 Camera camera;
	 double curtime=0, lastframe=0,lastUpdate;
	 long frames=0;
	 int WIDTH = 1024, HEIGHT = 768;

	 GUI gui;
	TextRenderer *fpsText;
	std::string fps_str;
public:

	Engine(){
		 map = new Map("map001");

	  peon = new SpriteSheet("weddingguy02");

	  player = new Player(peon, 200, 200, 0, 0, 32, 64);

	  fpsText  = new TextRenderer(camera.getWidth()-50,10,"");

		Entity *ent = new Entity(peon,200,100,0,0,32,64);
		ent->setName("Test");
		ent->setHP(50);
		entities.push_back(ent);
		//curtime = clock();
		curtime=glfwGetTime();
		lastframe=glfwGetTime();
		//lastframe = clock();

	//textrend.initText("Hello worldssss\n  sss sssssssssss");

	}

	void Update(){
		frames++;
	//	time(&curtime);
	lastUpdate=curtime;
	curtime = glfwGetTime();

//double dt = curtime-lastUpdate;
		double elp = curtime - lastframe;


		//std::cout << elp << std::endl;
		if (elp>1){
			std::stringstream stream;
			stream<<((frames)/(elp));
			fpsText->setText(stream.str());
			//std::cout << (frames / (elp)) << std::endl;
			lastframe = curtime;
			frames = 0;
		}
	//
		player->Update(curtime);

		camera.setX(player->getX() - ((WIDTH / 2) - (player->getImgW() / 2)));
		camera.setY(player->getY() - ((HEIGHT / 2) - (player->getImgH() / 2)));
		camera.Update();
		//probably will need to be fixed later
		if (camera.getX() < map->getMinX()){
			camera.setX(map->getMinX());
		}
		if (camera.getX() + camera.getWidth() > map->getMaxX()){
			camera.setX(map->getMaxX() - camera.getWidth());
		}
		if (camera.getY() < map->getMinY()){
			camera.setY(map->getMinY());
		}
		if (camera.getY() + camera.getHeight() > map->getMaxY()){
			camera.setY(map->getMaxY() - camera.getHeight());
		}


		for (unsigned int i = 0; i < entities.size(); i++){
			entities[i]->Update(curtime);
		}




	}

	void Draw(){

		map->Draw(camera);
		for (unsigned int i = 0; i < entities.size(); i++){
			entities[i]->Draw(camera);
		}
		player->Draw(camera);
		gui.Draw(player);
		fpsText->Draw();
		//textrend.Draw();


	}


	void MouseClick(int button, double MouseX, double MouseY){
	double	gMouseX = MouseX+camera.getX();
	double	gMouseY = MouseY+camera.getY();
		//std::cout << "MouseButton:" << button << "  X:" << MouseX << " Y:" << MouseY << "\n";

		if (button == 0){
			if(gui.checkMouseClick(MouseX, MouseY)){
			  return;
			}
		//	std::cout << "RightClick: X:" << MouseX << " Y:" << MouseY << "\n";
			for (unsigned int i = 0; i < entities.size(); i++){
				if (entities[i]->checkMouseClick(gMouseX, gMouseY)){
					std::cout << entities[i]->getName() << " Selected\n";
					player->setTarget(entities[i]);
					break;
				}
				else{
					player->setTarget(nullptr);
				}
			}
		}
	}
	Camera &getCamera(){
		return camera;
	}
	Entity*  getPlayer(){
		return player;
	}
	Map * getMap(){
		return map;
	}
	GUI& getGUI(){
		return gui;
	}
};


#endif
