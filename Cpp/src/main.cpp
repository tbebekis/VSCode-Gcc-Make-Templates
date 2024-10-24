#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

#include "./inc/funcs.hpp"

using namespace std;
using namespace project;

int main() {
	stringstream SS;

	WriteLine("Hi there, this is a template C++ project");

	string S = ReadString("Type a string"); 		
	SS << "You typed: " << S;
	WriteLine(SS.str());
	
	SS.str(""); 							// clear the stream	
	
	int i = ReadInteger("Type an integer");			
	SS << "You typed: " << i;
	WriteLine(SS.str()); 

#ifdef _WIN32 
	WriteLine("Press a key to terminate");
	cin.get();								// stop and wait for a keystroke
	cin.get();
#endif 

	return 0;
}