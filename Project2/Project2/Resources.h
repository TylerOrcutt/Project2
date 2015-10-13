#pragma once
#ifndef __KAL_RESOURCES_H
#define __KAL_RESOURCES_H
#include <vector>
#include "SpriteSheet.h"
#include <stdlib.h>

	 SpriteSheet *spritesheets[10];
	//Game Resources
	 void loadResouces(){

		spritesheets[0] = new SpriteSheet("itemPickup");
		spritesheets[1] = new SpriteSheet("peon");
	}
	 SpriteSheet* getResouce(int index){
		return spritesheets[index];
	}


	//GUIResources


#endif