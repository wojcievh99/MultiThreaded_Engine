// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Particle;

int main()
{
	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1800, 1200 }, "Engine Test", false, 60);
	


	if (init) engine.run();

	return 0;
}


