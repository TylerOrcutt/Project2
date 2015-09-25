#ifndef __KAL_ENGINE_NETWORDATAHANDLER_H_
#define __KAL_ENGINE_NETWORDATAHANDLER_H_
/*#include "../Engine.h"
//#include "Dictionary.h"
#include "../Resources.h"
void Engine::handleNetworkData(Dictionary * dict){
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
	if (dict->getItem("GameObjects") != nullptr){
		DictionaryItem * gm = dict->getItem("GameObjects");
		freeGameObjects();
		for (int i = 0; i < gm->items.size(); i++){
			float px = atof(gm->items[i].getItem("x")->value.c_str());
			float py = atof(gm->items[i].getItem("y")->value.c_str());
			std::string pv = gm->items[i].getItem("isVisible")->value;
			int resouceID = atoi(gm->items[i].getItem("resourceID")->value.c_str());
			PickUp *p = new PickUp(ResourceManager::getResouce(resouceID), px, py);
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
			GameItem *pv = new GameItem(ResourceManager::getResouce(resouceID));
			pv->setName(gm->items[i].key);
			pv->setStackCount(count);
			//std::cout << count << std::endl;

			inventory.push_back(pv);

		}
	}

	delete(dict);
}*/

#endif