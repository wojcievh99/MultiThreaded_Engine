// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Particle;

int main()
{
	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1500, 1200 }, "Particle Simulator", false, 60);

	std::random_device rd;

	std::uniform_real_distribution<float> posX(100.f, 1400.f);
	std::uniform_real_distribution<float> posY(100.f, 1100.f);

	std::uniform_real_distribution<float> move(-.1f, .1f);

	std::uniform_real_distribution<float> radius(8.f, 15.f);

	std::uniform_int_distribution<int> rgb(100, 255);

	for (int i = 200; i--;) {
		engine.addObject<Particle>(
			std::make_shared<Particle>(
				sf::Vector2f( posX(rd), posY(rd) ), 
				sf::Vector2f( move(rd), move(rd) ),
				radius(rd), 
				sf::Color(rgb(rd), rgb(rd), rgb(rd))
			)
		);
	}
	
	if (init) engine.run();

	return 0;
}


