#ifndef __ENGINE_H_
#define __ENGINE_H_
#include "Entity.h"
#include "Player.h"
#include "SpriteSheet.h"
#include "Map.h"
#include "Camera.h"
#include "GUI.h"
#include <vector>
#include <string>
#include<ctime>
#include "TextRenderer.h"
class Engine{
private:

	std::vector<Entity*> entities;
	SpriteSheet * peon;
	 Map *map;
	 Entity*player;
	 Camera camera;
	 long double curtime=0, lastframe=0;
	 long frames=0;
	 int WIDTH = 1024, HEIGHT = 768;
	 GUI gui;
	 TextRenderer textrend;
public:

	Engine(){
		 map = new Map("map001");
		
	  peon = new SpriteSheet("weddingguy02");
	 
	  player = new Player(peon, 200, 200, 0, 0, 32, 64);

		Entity *ent = new Entity(peon,200,100,0,0,32,64);
		ent->setName("Test");
		ent->setHP(35);
		entities.push_back(ent);
		curtime = clock();
		lastframe = clock();

		
	
	}

	void Update(){
		player->Update();

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
			entities[i]->Update();
		}
	
		

	
	}

	void Draw(){
		frames++;
		curtime = clock();
		long elp = curtime-lastframe;
		//std::cout << elp << std::endl;
		if (elp>1000.0){
			//std::cout << (frames / (elp/1000)) << std::endl;
			lastframe = curtime;
			frames = 0;
		}
	//	
		map->Draw(camera);
		for (unsigned int i = 0; i < entities.size(); i++){
			entities[i]->Draw(camera);
		}
		player->Draw(camera);
		gui.Draw(player);
		textrend.DrawText("The quick brown fox jumped \nover the lazy dog....\n\nHello World", 100, 100);
	}


	void MouseClick(int button, double MouseX, double MouseY){
		MouseX += camera.getX();
		MouseY += camera.getY();
		//std::cout << "MouseButton:" << button << "  X:" << MouseX << " Y:" << MouseY << "\n";
		if (button == 0){
		//	std::cout << "RightClick: X:" << MouseX << " Y:" << MouseY << "\n";
			for (unsigned int i = 0; i < entities.size(); i++){
				if (entities[i]->checkMouseClick(MouseX, MouseY)){
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
