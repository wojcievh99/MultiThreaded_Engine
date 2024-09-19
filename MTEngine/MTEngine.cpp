// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;


int main()
{
	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1500, 1200 }, "TEST", false, 60);
	
	if (init) engine.run();

	return 0;
}


