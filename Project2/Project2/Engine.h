/**************************************
*Engine.h
*Created by Tyler Orcutt
*
*Copyright 2015 Tyler Orcutt
****************************************/
#pragma once
#ifndef __KAL_ENGINE_H_
#define __KAL_ENGINE_H_

//#define OFFLINEMODE

#include "Entity.h"
#include "Player.h"
#include "SpriteSheet.h"
#include "Map.h"
#include "Camera.h"
#include "GUI/GUI.h"
#include "GUI/TextRenderer.h"

//game Objects
#include "Resources.h"
#include "GameObject.h"
#include "PickUp.h"

#include "GameItem.h"

#include "Projectile.h"

#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <GLFW/glfw3.h>
#include <thread>
#include <future>
//#include <unistd.h>
#include <time.h>
#include <climits>
#include "Network/NetworkClient.h"
#include "Network/ConnectionHandler.h"
#include<stdlib.h>
#include "Shaders/Shaders.h"

#ifdef __linux__
#include <sys/time.h>
#endif


class Engine{
private:
	
	NetworkClient * network;
	
	//TODO data struct, hash?
	std::vector<Entity*> entities;

	SpriteSheet * peon,*wedguy, *fireball;
	 Map *map;
	 Entity*player;

	 std::vector<Entity*> players;
	 Camera camera;
	 double curtime=0, lastframe=0,lastUpdate;
	 long frames=0;
	 int WIDTH = 800, HEIGHT = 600;

   std::vector<GameObject *>gameObjects;
	 GUI *gui;
	TextRenderer *fpsText;
	std::string fps_str;
std::vector<GameItem *>inventory;
Projectile *proj=nullptr;
Shaders * shaderprogram;

long lt;

long ms;
long mss;
float pstartx,pstarty;
public:
	/*function definitions*/
	static void static_handleNetworkData(Engine * engine, Dictionary * dict){
		engine->handleNetworkData(dict);
	}

	//void handleNetworkData(Dictionary * dict);


	/**/
	Engine(Shaders* shaders){
		shaderprogram = shaders;
#ifndef OFFLINEMODE
		loginMenu=true;
#endif

	loadResouces();

	//	gui->setEngine(thiis);
		gui = new GUI();
network = new NetworkClient();

//std::thread t(&Engine::networkThread, this);
//t.detach();

	gui->setNetworkClient(network);
	gui->setInventory(&inventory);
			 map = new Map("map001");
peon = new SpriteSheet("peon");
	  wedguy=new SpriteSheet("weddingguy02");
		fireball = new SpriteSheet("fireball");

	  player = new Player(wedguy, 200, 200, 0, 0, 32, 64);

	  fpsText  = new TextRenderer(camera.getWidth()-50,10,"");

	
	/*	Entity *ent = new Entity(peon,200,100,0,0,32,32);
		ent->setName("Peon");
		ent->setHP(50);
		ent->resize(64,64);
		entities.push_back(ent);*/
		//curtime = clock();
		curtime=glfwGetTime();
		lastframe=glfwGetTime();
		//lastframe = clock();
		ConnectionHandler conn;
		if (conn.retrieveRealmList()){
			network->setRealm(conn.getRealms()[0]);
			gui->setSelectedRealm(conn.getRealms()[0].name);
			network->setRealms(conn.getRealms());
		}
		

	}



	void Update(){
#ifndef OFFLINEMODE
		Dictionary* di = network->getData();


		//handleNetworkData(dict.get());
		//Dictionary * di = dict.get();
		if (di!= nullptr){
			//std::async(&Engine::static_handleNetworkData, this, di);
			//std::thread t(&Engine::static_handleNetworkData, this, di);
			//t.detach();
			handleNetworkData(di);
		}
		//
		//handleNetworkData(network->getData());
		if (!network->isConnected() && !loginMenu){
			gui->clearChat();
			freePlayers();
			freeInventoryObjects();
			freeGameObjects();
			freeEntities();
		std::cout << "Disconnected\n";
		loginMenu = true;
			gui->setMsgBox(new GUIMessagebox("Connection to server lost"));
		}
#endif
		frames++;
	//	time(&curtime);
	lastUpdate=curtime;
	curtime = glfwGetTime();

	unsigned long ct = getTime();
	unsigned long dt = CalcTimeDiff(ct, lt);
	lt = ct;
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
	
	//	gettimeofda
	
		//long dtt = difftime(ct, lt);
	//	lt = ct;
		//dtt *= 100;
		player->Update(dt);
   

	for (int i = 0; i < players.size(); i++){
		players[i]->Update(dt);
	}

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


	/*	for (unsigned int i = 0; i < entities.size(); i++){
			entities[i]->setX(entities[i]->getX()+1);
			if(entities[i]->getX()>700){
					entities[i]->setX(300);
			}
			entities[i]->Update(curtime);
		}
		*/

dt *=10000;
		//std::cout << dt << std::endl;
//usleep(10000);

if (player->isMoving()){
	//std::stringstream ss;
	//ss << "{\"Position\":[\"x\":\"" << player->getX() << "\",\"y\":\"" << player->getY() << "\"]}";
//	network->sendData(ss.str());
}


	}

	void Draw(){
		if(loginMenu){
			shaderprogram->disableShaders();
			gui->DrawLoginMenu();
			fpsText->Draw();
			return;
		}
		
		shaderprogram->enableShaders();
    map->Draw(camera);

	for (int i = 0; i < gameObjects.size(); i++){
		gameObjects[i]->Draw(&camera);
	}
		for (unsigned int i = 0; i < entities.size(); i++){
			entities[i]->Draw(camera);
		}

		for (int i = 0; i < players.size(); i++){
			players[i]->Draw(camera);
		}

		player->Draw(camera);
		if(proj != nullptr){
			proj->Draw(&camera);
		}

		shaderprogram->disableShaders();
		gui->Draw(player);
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

void sendMouseClick(int button, double MouseX, double MouseY){
	std::stringstream ss;
	ss << "{\"MouseClick\":[";
	ss << "\"Button\":\""<<button<<"\",";
	ss << "\"X\":\"" << MouseX << "\",";
	ss << "\"Y\":\"" << MouseY << "\"]}";
	network->sendData(ss.str());

}
	void MouseClick(int button, double MouseX, double MouseY){
	double	gMouseX = MouseX+camera.getX();
	double	gMouseY = MouseY+camera.getY();
		//std::cout << "MouseButton:" << button << "  X:" << MouseX << " Y:" << MouseY << "\n";
    //right click
    if(button==1){
		sendMouseClick(button, gMouseX, gMouseY);
/*      if(pickup->checkMouseClick(gMouseX,gMouseY)){
       pickup->setVisible(false);
			 bool adNew=true;
       gui->addChatLogText("You looted " + pickup->getName()+".");
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

      }*/
    }

//left click
		if (button == 0){
			if(gui->checkMouseClick(MouseX, MouseY)){
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
		return gui;
	}
	NetworkClient * getNetwork(){
		return network;
	}



	void exitGame(std::string method){

	}

	void freePlayers(){
		for (int i = 0; i < players.size(); i++){
			delete(players[i]);
		
		}
		players.clear();
	}
	void freeGameObjects(){
		for (int i = 0; i < gameObjects.size(); i++){
			delete(gameObjects[i]);

		}
		gameObjects.clear();
	}
	void freeEntities(){
		for (int i = 0; i < entities.size(); i++){
			delete(entities[i]);

		}
		entities.clear();
	}
	void freeInventoryObjects(){
		for (int i = 0; i < inventory.size(); i++){
			delete(inventory[i]);

		}
		inventory.clear();
	}
	
	void sendMoving(){
		std::stringstream ss;
		if (player->isMoving()){
			ms = getTime();
			//ss << "{\"Position\":[\"x\":\"" << player->getX() << "\",\"y\":\"" << player->getY() << "\"],
			ss<<"{\"Moving\":[\"isMoving\":\"true\",\"Direction\":\"" << player->getDirection() << "\"]}";
		
			pstartx = player->getX();
			pstarty = player->getY();

		}
		else{
			//ss << "{\"Position\":[\"x\":\"" << player->getX() << "\",\"y\":\"" << player->getY() << "\"],\"Moving\":[\"isMoving\":\"false\",\"Direction\":\"" << player->getDirection() << "\"]}";
			ss << "{\"Moving\":[\"isMoving\":\"false\",\"Direction\":\"" << player->getDirection() << "\"]}";
		/*	unsigned long dms = CalcTimeDiff(getTime(), ms);
			float distance = ((float)player->getSpeed()*dms)/1000 ;
			std::cout << distance << std::endl;
			
			std::cout << "Start Location: X:" << pstartx << " Y:" << pstarty << std::endl;
			switch (player->getDirection())
			{
			case 0 :
				pstarty -= distance;
				break;
			case 1:
				pstartx += distance;
				break;
			case 2:
				pstarty += distance;
				break;
			case 3:
				pstartx -= distance;
				break;
			}
		//	std::cout << "Projected Location: X:" << pstartx << " Y:" << pstarty << std::endl;

			//std::cout << "Actual Location: X:"<<player->getX()<<" Y:"<<player->getY()<<std::endl;
			*/
		}
		network->sendData(ss.str());
	}


	void handleNetworkData(Dictionary * dict){
		if (dict == nullptr){
			return;
		}
		if (dict->getItem("msgBox") != nullptr){
			gui->createMessageBox(dict->getItem("msgBox")->value);
		}
		if (loginMenu){
			if (dict->getItem("Login") != nullptr){
				if (dict->getItem("Login")->value == "success"){
					loginMenu = false;
					gui->setTyping(false);
				}
				else{
					//std::cout<<dict->getItem("Login")->value<<std::endl;
					//gui->setMsgBox(new GUIMessagebox(dict->getItem("Login")->value));
					gui->createMessageBox(dict->getItem("Login")->value);
				}

			}

		}
		if (dict->getItem("Disconnected") != nullptr){
			std::string dc = dict->getItem("Disconnected")->value;
			for (int i = 0; i < players.size(); i++){
				if (players[i]->getName() == dc){
					delete(players[i]);
					players.erase(players.begin() + i);
					break;
				}
			}
			gui->addChatLogText(dc + " disconnected.");
		}
		if (dict->getItem("Chat") != nullptr){
			//std::cout << "chat msg revieved\n";
			std::string cline = dict->getItem("Chat")->value;
			for (int i = 0; i <= cline.length(); i++){
				if (cline.substr(i, 4) == "&qt;"){
					cline.replace(i, 4, "\"");
				}
			}
			gui->addChatLogText(cline);
		}
		if (dict->getItem("Stats") != nullptr){
			DictionaryItem *position = nullptr;
			if ((position = dict->getItem("Stats")->getItem("Position")) != nullptr){
				player->setX(atof(position->getItem("X")->value.c_str()));
				player->setY(atof(position->getItem("Y")->value.c_str()));
				//	std::cout << "Updating position\n";

			}
		}

		if (dict->getItem("Players") != nullptr){
			//dict->printDictionay();
			for (int i = 0; i < dict->getItem("Players")->items.size(); i++){
				bool found = false;
				for (int p = 0; p < players.size(); p++){
					if (players[p]->getName() == dict->getItem("Players")->items[i].key){
						found = true;
						if (dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Position") != nullptr){
							players[p]->setX(atof(dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Position")->getItem("x")->value.c_str()));
							players[p]->setY(atof(dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Position")->getItem("y")->value.c_str()));
							//std::cout << "Updating Player " << dict->getItem("Players")->items[i].key << std::endl;
						}
						if (dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Moving") != nullptr){
							if (dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Moving")->getItem("isMoving")->value == "true"){
								players[p]->setMoving(true);
							}
							else{
								players[p]->setMoving(false);
							}
							players[p]->setDirection(atoi(dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Moving")->getItem("Direction")->value.c_str()));
						}

						break;
					}

				}

				if (!found){
					Player *ply = new Player(wedguy, 200, 200, 0, 0, 32, 64);
					if (dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Position") != nullptr){
						float px = atof(dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Position")->getItem("x")->value.c_str());
						float py = atof(dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Position")->getItem("y")->value.c_str());
						ply->setX(px);
						ply->setY(py);
					}
					if (dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Moving") != nullptr){
						if (dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Moving")->getItem("isMoving")->value == "true"){
							ply->setMoving(true);
						}
						else{
							ply->setMoving(false);
						}
						ply->setDirection(atoi(dict->getItem("Players")->getItem(dict->getItem("Players")->items[i].key)->getItem("Moving")->getItem("Direction")->value.c_str()));
					}

					ply->setName(dict->getItem("Players")->items[i].key);
					players.push_back(ply);

				}
				//std::cout << "Adding Player " << dict->getItem("Players")->items[i].key << std::endl;

			}

		}


		if (dict->getItem("NPCS") != nullptr){
			//dict->printDictionay();
			for (int i = 0; i < dict->getItem("NPCS")->items.size(); i++){
				bool found = false;
				for (int p = 0; p < entities.size(); p++){
					if (entities[p]->getName() == dict->getItem("NPCS")->items[i].key){
						found = true;
						if (dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Position") != nullptr){
							entities[p]->setX(atof(dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Position")->getItem("x")->value.c_str()));
							entities[p]->setY(atof(dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Position")->getItem("y")->value.c_str()));
							//std::cout << "Updating Player " << dict->getItem("Players")->items[i].key << std::endl;
						}
						if (dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Moving") != nullptr){
							if (dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Moving")->getItem("isMoving")->value == "true"){
								entities[p]->setMoving(true);
							}
							else{
								entities[p]->setMoving(false);
							}
							entities[p]->setDirection(atoi(dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Moving")->getItem("Direction")->value.c_str()));
						}

						break;
					}

				}

				if (!found){
					Entity *ply = new Entity(wedguy, 200, 200, 0, 0, 32, 64);
					if (dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Position") != nullptr){
						float px = atof(dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Position")->getItem("x")->value.c_str());
						float py = atof(dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Position")->getItem("y")->value.c_str());
						ply->setX(px);
						ply->setY(py);
					}
					if (dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Moving") != nullptr){
						if (dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Moving")->getItem("isMoving")->value == "true"){
							ply->setMoving(true);
						}
						else{
							ply->setMoving(false);
						}
						ply->setDirection(atoi(dict->getItem("NPCS")->getItem(dict->getItem("NPCS")->items[i].key)->getItem("Moving")->getItem("Direction")->value.c_str()));
					}

					ply->setName(dict->getItem("NPCS")->items[i].key);
					entities.push_back(ply);

				}
				//std::cout << "Adding Player " << dict->getItem("Players")->items[i].key << std::endl;

			}

		}

		if (dict->getItem("GameObjects") != nullptr){
			DictionaryItem * gm = dict->getItem("GameObjects");
			freeGameObjects();
			for (int i = 0; i < gm->items.size(); i++){
				float px = atof(gm->items[i].getItem("x")->value.c_str());
				float py = atof(gm->items[i].getItem("y")->value.c_str());
				std::string pv = gm->items[i].getItem("isVisible")->value;
				int resouceID = atoi(gm->items[i].getItem("resourceID")->value.c_str());
				PickUp *p = new PickUp(getResouce(resouceID), px, py);
				if (pv == "true"){
					p->setVisible(true);
				}
				else{
					p->setVisible(false);
				}
				gameObjects.push_back(p);

			}
		}
		if (dict->getItem("Inventory") != nullptr){
			DictionaryItem * gm = dict->getItem("Inventory");
			freeInventoryObjects();
			for (int i = 0; i < gm->items.size(); i++){
				float count = atoi(gm->items[i].getItem("count")->value.c_str());

				int resouceID = atoi(gm->items[i].getItem("resourceID")->value.c_str());
				GameItem *pv = new GameItem(getResouce(resouceID));
				pv->setName(gm->items[i].key);
				pv->setStackCount(count);
				//std::cout << count << std::endl;

				inventory.push_back(pv);

			}
		}
		if (dict->getItem("GameTime") != nullptr){
			DictionaryItem * gm = dict->getItem("GameTime");
			if (gm->getItem("Hours") != nullptr){
				std::cout << "Game Hours:" << gm->getItem("Hours")->value<<std::endl;
				std::cout << "Game Minutes:" << gm->getItem("Minutes")->value << std::endl;
				std::cout << "Game Days:" << gm->getItem("Days")->value << std::endl;
				int hours = atoi(gm->getItem("Hours")->value.c_str());
				int minutes = atoi(gm->getItem("Minutes")->value.c_str());
			
			
				
				if (hours == 21){
					GLfloat ambient[] = { 3.0f, 3.0f, 3.0f, 1.f };
					glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
				}
				
			
				else
				if (hours == 22){
					GLfloat ambient[] = { 1.0f, 1.0f, 1.0f, 1.f };
					glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
				}
			
				else
				if (hours == 23 ){
					GLfloat ambient[] = { 0.5f, 0.5f, 0.5f, 1.f };
					glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
				}else
		
				if (hours == 0 ){
					GLfloat ambient[] = { 0.25f, 0.25f, 0.25f, 1.f };
					glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
				}else
				
				if (hours == 1){
					GLfloat ambient[] = { 0.5f, 0.5f, 0.5f, 1.f };
					glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
				}else
				if (hours ==2){
					GLfloat ambient[] = { 1.0f, 1.0f, 1.0f, 1.f };
					glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
				}else
				if (hours == 3){
					GLfloat ambient[] = { 2.0f, 2.0f,2.0f, 1.f };
					glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
				}else
				if (hours == 4 ){
					GLfloat ambient[] = { 3.f, 3.f, 3.f, 1.f };
					glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
				}
				else {
					GLfloat ambient[] = { 4.0f,4.0f, 4.0f, 1.f };
					glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
				}
				
			}
		}

		delete(dict);
	}
unsigned long getTime(){
#ifdef __linux__
	timeval tm;
	gettimeofday(&tm,NULL);
	unsigned long cm=(tm.tv_sec*1000)+(tm.tv_usec/1000);
	return cm;
#else
	SYSTEMTIME t;
	GetSystemTime(&t);
	unsigned long ctim = (t.wSecond * 1000)+ t.wMilliseconds;
	return ctim;
#endif
}

unsigned long CalcTimeDiff(unsigned long curtime, unsigned long lasttime){
	unsigned long dtt;
	if (curtime < lasttime){
		dtt =(ULONG_MAX - lasttime) + curtime;
		std::cout << "Time lap\n";
		dtt = 0;

	}
	else{
		dtt = curtime - lasttime;

	}
	return dtt;
}

};


#endif