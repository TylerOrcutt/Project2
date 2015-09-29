#ifndef __KAL_LUAMANAGER_H_
#define __KAL_LUAMANAGER_H_
#include <stdio.h>
#include <string>
#pragma comment(lib, "lua52")
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "../GUI/GUI.h"

 GUI * LUAgui;
class LUAManager {
private:
	
public:

	static void executeLUAFile(std::string file,GUI *gu){
	//	std::cout << "Execuiting LUA file\n";
		lua_State * L = luaL_newstate();

		luaL_openlibs(L);
		LUAgui= gu;
		
		lua_register(L, "average", LUAManager::average);
		lua_register(L, "print", LUAManager::print);
		lua_register(L, "createMessageBox", LUAManager::createMessageBox);

		luaL_dofile(L, "Addons/average.lua");

		
		lua_close(L);
	

		
		
	}
	static int average(lua_State *L)
	{
	//	std::cout << "adverage called\n";
	

		int n = lua_gettop(L);
		double sum = 0;
		int i;

	//loop thro args
		for (i = 1; i <= n; i++)
		{
			sum += lua_tonumber(L, i);
		}

		
		//push adverage
		lua_pushnumber(L, sum / n);

		//push sum
		lua_pushnumber(L, sum);

		//return number of results
		return 2;
	}
	static int print(lua_State *L)
	{
	//	std::cout << "print called\n";
		/* get number of arguments */
		int n = lua_gettop(L);
		std::string a;
		for (int i = 1; i <= n; i++){
			 a =  a  +(std::string)luaL_checkstring(L, i);
		}
		std::cout << a << std::endl;

		return 0;

	}
	static int createMessageBox(lua_State *L){
		std::cout << "called create messagebox\n";
			int n = lua_gettop(L);
		std::string a;
		for (int i = 1; i <= n; i++){
			 a =  a+(std::string)luaL_checkstring(L, i);
		}
		LUAgui->createMessageBox(a);
			return 0;
	}
};

#endif