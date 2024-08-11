// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Circle;
import Player;
import Rectangle;

int main()
{
	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 2000, 1300 }, "TEST", false, 100000);

	std::random_device rd;

	std::uniform_real_distribution<float> posX(100.f, 1900.f);
	std::uniform_real_distribution<float> posY(100.f, 1200.f);

	std::uniform_real_distribution<float> move(-.001f, .001f);

	std::uniform_real_distribution<float> radius(5.f, 15.f);

	std::uniform_int_distribution<int> rgb(100, 255);


	
	for (int i = 350; i--;) {
		auto r = engine.addObject<Circle>(
			std::make_shared<Circle>(sf::Vector2f{ posX(rd), posY(rd) },
				sf::Vector2f{ move(rd), move(rd) }, radius(rd), sf::Color(rgb(rd), rgb(rd), rgb(rd))
			));
	}
	
		
	
	if (init) engine.run();

	return 0;
}


