// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;
import Player;

int main()
{
	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1500, 1200 }, "TEST", false, 60);
	
	engine.addObject<Player>(std::make_shared<Player>(sf::Vector2f{100.f, 100.f}));

	if (init) engine.run();

	return 0;
}


