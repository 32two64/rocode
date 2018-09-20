#include <Windows.h>
#include "memory.h"
#include "Includes.h"
#include "mem.h"

int lua_State;


int Address(int Offset) {
	return (Offset - 0x00400000 + (DWORD)GetModuleHandle("RobloxPlayerBeta.exe"));
}


//Singleton (Print) done
typedef int(__cdecl *SINGLETON)(int a1, const char *a2);
SINGLETON SingletonPrint = (SINGLETON)Address(0x647190);

//Getfield done
typedef void(__fastcall *Lua_getfield)(DWORD rL, int idx, const char *k);
Lua_getfield lua_getfield = (Lua_getfield)Address(0x850620);

//Settop done
typedef void(__fastcall *Lua_settop)(DWORD rL, int n);
Lua_settop lua_settop = (Lua_settop)Address(0x852780);

//Pushstring done
typedef void(__cdecl *Lua_pushstring)(DWORD rL, const char *s);
Lua_pushstring lua_pushstring = (Lua_pushstring)Address(0x8519A0);

//Push Value done
typedef void(__stdcall *Lua_pushvalue)(DWORD rL, int idx);
Lua_pushvalue lua_pushvalue = (Lua_pushvalue)Address(0x851A60);

//Pcall done
typedef int(__cdecl *Lua_pcall)(DWORD rL, int naArgs, int nresults, int errfunc);
Lua_pcall lua_pcall2 = (Lua_pcall)Address(0x8513E0);

//Setfield
typedef void(__stdcall *rrsetfield)(DWORD rL, int, const char*);
rrsetfield lua_setfield = (rrsetfield)Address(0x8523A0);



//Getmetatable done
typedef int(__cdecl *Lua_getmetatable)(int lua_State, int idx);
Lua_getmetatable lua_getmetatable = (Lua_getmetatable)Address(0x84b220);







void fakeChain(DWORD* chain)
{
	chain[1] = 0x1555555;
	if ((((DWORD*)chain[0])[1]) != NULL) {
		((DWORD*)chain[0])[1] = 0x1555555;
	}
}
void restoreChain(DWORD* chain, DWORD unk, DWORD nextUnk)
{
	chain[1] = unk;
	if ((((DWORD*)chain[0])[1]) != NULL) {
		((DWORD*)chain[0])[1] = nextUnk;
	}
}


int lua_pcall(DWORD rL, int nargs, int nresults, int errfunc)
{
	DWORD* exceptionChain = (DWORD*)__readfsdword(0);
	DWORD unk = exceptionChain[1];
	((((DWORD*)exceptionChain[0])[1]) != NULL);
	{
		DWORD nextUnk = ((DWORD*)exceptionChain[0])[1];
		fakeChain(exceptionChain);
		int ret = lua_pcall(rL, nargs, nresults, errfunc);
		restoreChain(exceptionChain, unk, nextUnk);
		return ret;
	}

	fakeChain(exceptionChain);
	int ret = lua_pcall(rL, nargs, nresults, errfunc);
	restoreChain(exceptionChain, unk, 0);
	return ret;
}

void lua_getglobal(int lua_State, const char *k) {
	lua_getfield(lua_State, -10002, k);
}

#define runr(a)





void CreateHeadPart(std::string ye, std::string inst) {

	lua_getglobal(lua_State, "game");
	lua_getfield(lua_State, -1, "Players");
	lua_getfield(lua_State, -1, ye.c_str());
	lua_getfield(lua_State, -1, "Character");
	lua_getfield(lua_State, -1, "Head");
	lua_getglobal(lua_State, "Instance");
	lua_getfield(lua_State, -1, "new");
	lua_pushstring(lua_State, inst.c_str());
	lua_pushvalue(lua_State, -4);
	lua_pcall(lua_State, 2, 0, 0);
}

//Print (No Singleton)
void Print(std::string Input) {

	lua_getglobal(lua_State, "print");
	lua_pushstring(lua_State, Input.c_str());
	lua_pcall(lua_State, 1, 0, 0);

}



