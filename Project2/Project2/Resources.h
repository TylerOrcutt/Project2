#ifndef __KAL_RESOURCES_H
#define __KAL_RESOURCES_H
#include <vector>
#include "SpriteSheet.h"
#include <stdlib.h>


	SpriteSheet *spritesheets[10];
	//Game Resources
	 void loadResouces(){
		
		spritesheets[0] = new SpriteSheet("itemPickup");
	}
	SpriteSheet* getResouce(int index){
		return spritesheets[index];
	}


	//GUIResources




#endif