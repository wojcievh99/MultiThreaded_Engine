// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Character;

int main()
{
	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1800, 1200 }, "Engine Test", false, 60);
	
	engine.addObject<Character>(std::make_shared<Character>(sf::Vector2f(100.f, 100.f)));

	if (init) engine.run();

	return 0;
}


