#ifndef __MAP_H_
#define __MAP_H_
#include "Sprite.h"
#include "SpriteSheet.h"
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "Camera.h"

struct  Block
{
	float x = 0, y = 0, imgx = 0, imgy = 0, imgw = 32, imgh = 32;
};
class Map{

private:
	Sprite * mapsheet;
	std::vector<Block> blocks;
	float minX=0, minY=0, maxX=0, maxY=0;

public:
	
	Map(std::string file){
		Load(file);
	//	SpriteSheet mpsh;
		
		mapsheet = new Sprite(new SpriteSheet("sp2"));

	}



	void Draw(Camera cam){
		for (unsigned int i = 0; i < blocks.size(); i++){
			if (blocks[i].x >= cam.getX() - blocks[i].imgw && blocks[i].x <= cam.getX() + cam.getWidth() && blocks[i].y >= cam.getY() - blocks[i].imgh && blocks[i].y <= cam.getY() + cam.getHeight()){
				mapsheet->Draw(blocks[i].x - cam.getX(), blocks[i].y - cam.getY(), blocks[i].imgx, blocks[i].imgy);
			}
		}

	}


	bool Load(std::string mFile){
		std::ifstream file;
		mFile = "./maps/" + mFile + ".txt";
		file.open(mFile.c_str());
		if (file.is_open()){
			std::string line;
			while (std::getline(file,line)){
				Block blk;
				for (unsigned int i = 0; i < line.length(); i++){
					if (line.substr(i, 5) == "posx="){
						blk.x = std::stof(getValue(i + 5, line).c_str());

					}
					if (line.substr(i, 5) == "posy="){
						blk.y = std::stof(getValue(i + 5, line).c_str());

					}
					if (line.substr(i, 5) == "imgx="){
						blk.imgx = std::stof(getValue(i + 5, line).c_str());

					}
					if (line.substr(i, 5) == "imgy="){
						blk.imgy = std::stof(getValue(i + 5, line).c_str());

					}
				}
				//	std::cout << "New block\n";
			

				if (maxX < blk.x){
					maxX = blk.x;
				}
				if (maxY < blk.y){
					maxY = blk.y;
				}

				if (minX> blk.x){
					minX = blk.x;
				}
				if (minY> blk.y){
					minY= blk.y;
				}
				blocks.push_back(blk);
			}


			file.close();



		}
		return true;
	}

	std::string getValue(int pos, std::string line){
		std::string value;
		for (unsigned int i = pos; i < line.length() && line.substr(i, 1) != ";"; i++){
			value = value + line.substr(i, 1);
		}
		return value;
	}



	float getMaxX(){
		return maxX;
	}	
	float getMaxY(){
		return maxY;
	}
	float getMinX(){
		return minX;
	}
	float getMinY(){
		return minY;
	}
};



#endif