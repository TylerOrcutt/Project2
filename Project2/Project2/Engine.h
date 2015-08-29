/**************************************
*Engine.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#ifndef __KAL_ENGINE_H_
#define __KAL_ENGINE_H_
#include "Entity.h"
#include "Player.h"
#include "SpriteSheet.h"
#include "Map.h"
#include "Camera.h"
#include "GUI/GUI.h"
#include "GUI/TextRenderer.h"

//game Objects
#include "GameObject.h"
#include "PickUp.h"

#include "GameItem.h"

#include "Projectile.h"

#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <GLFW/glfw3.h>
//#include <unistd.h>

#include "Network/NetworkClient.h"

class Engine{
private:
	NetworkClient * network;

	//TODO data struct, hash?
	std::vector<Entity*> entities;

	SpriteSheet * peon,*wedguy, *fireball;
	 Map *map;
	 Entity*player;
	 Camera camera;
	 double curtime=0, lastframe=0,lastUpdate;
	 long frames=0;
	 int WIDTH = 800, HEIGHT = 600;

   GameObject *pickup;
	 GUI gui;
	TextRenderer *fpsText;
	std::string fps_str;
std::vector<GameItem *>inventory;
Projectile *proj=nullptr;
public:

	Engine(){
		loginMenu=true;
	//	gui.setEngine(thiis);
network = new NetworkClient();

	gui.setNetworkClient(network);
	gui.setInventory(&inventory);
			 map = new Map("map001");
peon = new SpriteSheet("peon");
	  wedguy=new SpriteSheet("weddingguy02");
		fireball = new SpriteSheet("fireball");

	  player = new Player(wedguy, 200, 200, 0, 0, 32, 64);

	  fpsText  = new TextRenderer(camera.getWidth()-50,10,"");

		Entity *ent = new Entity(peon,200,100,0,0,32,32);
		ent->setName("Test");
		ent->setHP(50);
		ent->resize(64,64);
		entities.push_back(ent);
		//curtime = clock();
		curtime=glfwGetTime();
		lastframe=glfwGetTime();
		//lastframe = clock();
    pickup= new PickUp(new SpriteSheet("itemPickup"),200,200);
    pickup->setName("Stuff");


	}

	void Update(){
		handleNetworkData(network->getData());
		if (!network->isConnected() && !loginMenu){
		std::cout << "Disconnected\n";
		loginMenu = true;
			gui.setMsgBox(new GUIMessagebox("Connection to server lost"));
		}
		frames++;
	//	time(&curtime);
	lastUpdate=curtime;
	curtime = glfwGetTime();

double dt = (curtime-lastUpdate)*100;
		double elp = curtime - lastframe;
if(proj != nullptr){
	proj->Update(dt);
	if(!proj->isVisible()){
		delete(proj);
		proj=nullptr;
	}
}



		if (elp>1){
			std::stringstream stream;
			stream<<((frames)/(elp));
			fpsText->setText(stream.str());
			//std::cout << (frames / (elp)) << std::endl;
			lastframe = curtime;
			frames = 0;
		}
	//
	//std::cout<<dt<<std::endl;
		player->Update(dt);
    pickup->Update(dt);
		camera.setX((int)(player->getX() - ((WIDTH / 2) - (player->getImgW() / 2))));
		camera.setY((int)(player->getY() - ((HEIGHT / 2) - (player->getImgH() / 2))));
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
			entities[i]->setX(entities[i]->getX()+1);
			if(entities[i]->getX()>700){
					entities[i]->setX(300);
			}
			entities[i]->Update(curtime);
		}


dt *=10000;
		//std::cout << dt << std::endl;
//usleep(10000);
	}

	void Draw(){
		if(loginMenu){
			gui.DrawLoginMenu();
			fpsText->Draw();
			return;
		}

    map->Draw(camera);
        pickup->Draw(&camera);
		for (unsigned int i = 0; i < entities.size(); i++){
			entities[i]->Draw(camera);
		}
		player->Draw(camera);
		if(proj != nullptr){
			proj->Draw(&camera);
		}


		gui.Draw(player);
		fpsText->Draw();
		//textrend.Draw();


	}

void actionBarKey(int key){
	if(key==GLFW_KEY_2){
		int dir=player->getDirection();
		if(dir==0){
		player->setY(player->getY()-500);
	}
	if(dir==1){
	player->setX(player->getX()+500);
}
if(dir==2){
player->setY(player->getY()+500);
}
if(dir==3){
player->setX(player->getX()-500);
}

	}
if(key==GLFW_KEY_1){
	if(player->getTarget()!= nullptr){
		if(proj!=nullptr){
			delete (proj);
			proj=nullptr;
		}
	proj = new Projectile(fireball, player->getX(), player->getY()  +(player->getImgH()/2));
	proj->setTarget(player->getTarget());
//	proj->setTargetPosition(player->getTarget()->getX(),player->getTarget()->getY());

}
}
}
	void MouseClick(int button, double MouseX, double MouseY){
	double	gMouseX = MouseX+camera.getX();
	double	gMouseY = MouseY+camera.getY();
		//std::cout << "MouseButton:" << button << "  X:" << MouseX << " Y:" << MouseY << "\n";
    //right click
    if(button==1){
      if(pickup->checkMouseClick(gMouseX,gMouseY)){
       pickup->setVisible(false);
			 bool adNew=true;
       gui.addChatLogText("You looted " + pickup->getName()+".");
			 for(int i=0;i<inventory.size();i++){
				 if(inventory[i]->getName()==pickup->getName()){
					 if(inventory[i]->getStackCount()<inventory[i]->getMaxStack()){
						 inventory[i]->incCount();
						 adNew=false;
						 break;
					 }
				 }
			 }
			 if(adNew){
				 GameItem  * temp = new GameItem(pickup->getSprite());
				 temp->setName(pickup->getName());
				 	 inventory.push_back(temp);
				 }

      }
    }

//left click
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
	GUI* getGUI(){
		return &gui;
	}



	void exitGame(std::string method){

	}


//Process network data
void handleNetworkData(Dictionary * dict){
if(dict == nullptr){
	return;
}
if(loginMenu){
	if(dict->getItem("Login")->value=="success"){
		loginMenu=false;
		gui.setTyping(false);
	}else{
		//std::cout<<dict->getItem("Login")->value<<std::endl;
		gui.setMsgBox(new GUIMessagebox(dict->getItem("Login")->value));
	}

}

if (dict->getItem("Chat") != nullptr){
	std::cout << "chat msg revieved\n";
	gui.addChatLogText(dict->getItem("Chat")->value);
}
delete(dict);
}
};


#endif
