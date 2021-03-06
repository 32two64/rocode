
#include <Windows.h>
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <DirectXColors.h>
#include "ConsoleCMDS.h"
#include "Color.h"
#include "RoCodeLua.h"






using namespace std;



std::string Input() {
	std::string Lithium;
	getline(std::cin, Lithium);
	return Lithium;
}

std::vector<std::string> split(std::string s) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);
	return vstrings;
}



namespace PrintExploit {
	namespace Integers {
		int OutputType = 0; // 0 = Print, 1 = Info, 2 = Warn, 3 = Error
	}
}




// This code is leaked publicly, so I'll just use this. I'm not sure who made it originally though. But credits to whoever you are.

void ConsoleBypass() {
	DWORD CheckerValue;
	VirtualProtect((PVOID)&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &CheckerValue);
	*(BYTE*)(&FreeConsole) = (0xC3);
}

// Now let's create a Console Function. This just makes it easier for me to read my own code for some reason.

void Console(const char* ConsoleTitle) {
	ConsoleBypass();
	AllocConsole();
	SetConsoleTitleA(ConsoleTitle);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	HWND ConsoleHandle = GetConsoleWindow();
	::SetWindowPos(ConsoleHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	::ShowWindow(ConsoleHandle, SW_NORMAL);
}

// Here is the actual start of the program.

void luacommands(std::string Cmd) {
	std::vector<std::string> In = split(Cmd);

	std::string Error = "Could Not Execute Command, Please Rescan and try again.";
	
	if (In.at(0) == "cmds") {
		try {
			cout << blue << commands << white;
			cout << "[RC] >";
		}
		catch (std::exception) {
			cout << red << "Could not display commands. Unknown error occoured." << white;
		}
	}
	//Print Command
	else if (In.at(0) == "print") {
		try {
			string string;
			for (size_t i = 1; i < In.size(); i++) {
				if (i < (In.size() - 1)) {
					string.append(In.at(i) + ' ');
				}
				if (i == (In.size() - 1)) {
					string.append(In.at(i));
				}
			}
			cout << "";
			PrintExploit::Integers::OutputType = 0;
			SingletonPrint(PrintExploit::Integers::OutputType, string.c_str());
			cout << "[RC] >";
			
		}
		catch (std::exception) {
			cout << red << "[RC] Error, Could Not Execute!" << white;
			std::string Z = Input();
			luacommands(Z);
			cout << "[RC] >";
		}
	}
	//Warn Command
	else if (In.at(0) == "warn") {
		try {
			string string;
			for (size_t i = 1; i < In.size(); i++) {
				if (i < (In.size() - 1)) {
					string.append(In.at(i) + ' ');
				}
				if (i == (In.size() - 1)) {
					string.append(In.at(i));
				}
			}
			cout << "";
			PrintExploit::Integers::OutputType = 2;
			SingletonPrint(PrintExploit::Integers::OutputType, string.c_str());
			cout << "[RC] >";

		}
		catch (std::exception) {
			cout << "[RC] Error, Could Not Execute!" << white;
			std::string Z = Input();
			luacommands(Z);
			cout << "[RC] >";
		}
	
	}
	//Error Command
	else if (In.at(0) == "error") {
		try {
			string string;
			for (size_t i = 1; i < In.size(); i++) {
				if (i < (In.size() - 1)) {
					string.append(In.at(i) + ' ');
				}
				if (i == (In.size() - 1)) {
					string.append(In.at(i));
				}
			}
			cout << "";
			PrintExploit::Integers::OutputType = 3;
			SingletonPrint(PrintExploit::Integers::OutputType, string.c_str());
			cout << "[RC] >";

		}
		catch (std::exception) {
			cout << "[RC] Error, Could Not Execute!" << white;
			std::string Z = Input();
			luacommands(Z); // Part 1
			cout << "[RC] >";
		}
	}
	// Info Command
	else if (In.at(0) == "info") {
		try {
			string string;
			for (size_t i = 1; i < In.size(); i++) {
				if (i < (In.size() - 1)) {
					string.append(In.at(i) + ' ');
				}
				if (i == (In.size() - 1)) {
					string.append(In.at(i));
				}
			}
			cout << "";
			PrintExploit::Integers::OutputType = 1;
			SingletonPrint(PrintExploit::Integers::OutputType, string.c_str());
			cout << "[RC] >";

		}
		catch (std::exception) {
			cout << red << "[RC] Error, Could Not Execute!" << white;
			std::string Z = Input();
			luacommands(Z);
			cout << "[RC] >";
		}
		
	}
	//Day
	else if (In.at(0) == "day") {
		try {
			lua_getglobal(lua_State, "game");
			lua_getfield(lua_State, -1, "Lighting");
			lua_pushstring(lua_State, "14");
			lua_setfield(lua_State, -2, "TimeOfDay");
			cout << green << "Changed time to day (Client Only)" << white;
			}
		catch (std::exception) {
			cout << red << "[RC] Error, Could Not Execute!" << white;
			std::string Z = Input();
			luacommands(Z); 
			cout << "[RC] >";
		}
	}
	//Night
	else if (In.at(0) == "night") {
	try {
		lua_getglobal(lua_State, "game");
		lua_getfield(lua_State, -1, "Lighting");
		lua_pushstring(lua_State, "14");
		lua_setfield(lua_State, -2, "TimeOfDay");
		cout << green << "Changed time to night (Client Only)" << white;
	}
	catch (std::exception) {
		cout << red << "[RC] Error, Could Not Execute!" << white;
		std::string Z = Input();
		luacommands(Z);
		cout << "[RC] >";
	}
	}
	else if (In.at(0) == "printnos") {
	try {
		string string;
		for (size_t i = 1; i < In.size(); i++) {
			if (i < (In.size() - 1)) {
				string.append(In.at(i) + ' ');
			}
			if (i == (In.size() - 1)) {
				string.append(In.at(i));
			}
		}
		Print(string.c_str());
	}
	catch (std::exception) {
		std::cout << Error << std::endl;
	}
	}
	// If unknown/invalid command
	else {

		cout << red << "[RC] Unknown Command! \n" << white;
		cout << "[RC] >";
	}
}

void DoCommands(std::string Command) {
	luacommands(Command);
}

void MainFunction() {

	Console("RoCode");
	cout << green << "RoCode loaded.\n" << white;
	cout << "Type cmds to view a list of cmds \n";
	cout << "\n";
	cout << "[RC] >";
		while (true) {
			try {
				std::string Z = Input();
				luacommands(Z);
			}
			catch (std::exception) {
				cout << red << "\n Unable to run RoCode." << white;
			}
		}

}





// Here is the end (dllmain) which creates a thread and executes the code above when injected.

int __stdcall DllMain(HMODULE a, DWORD b, void* c) {
	if (b == 1) {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainFunction, 0, 0, 0);
	}
	return TRUE;
}