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
	bool init = engine.init({ 1500, 1200 }, "TEST", false, 60);

	auto p = engine.addObject<Player>(
		std::make_shared<Player>(sf::Vector2f{ 100.f, 900.f }, sf::Vector2f{ 2.f, 2.f })
	);

	auto r = engine.addObject<Rectangle>(
		std::make_shared<Rectangle>(sf::Vector2f{ 0.f, 1000.f }, sf::Color(50, 180, 80), sf::Vector2f{1500.f, 200.f})
	);
	
	if (init) engine.run();

	return 0;

	/*
		std::random_device rd;

		std::uniform_real_distribution<float> posX(100.f, 1000.f);
		std::uniform_real_distribution<float> posY(100.f, 900.f);

		std::uniform_real_distribution<float> move(-1.f, 1.f);

		std::uniform_int_distribution<int> rgb(0, 255);

		for (int i = 2; i--;) {
			auto r = engine.addObject<Circle>(
				std::make_shared<Circle>(sf::Vector2f{ posX(rd), posY(rd) },
				sf::Vector2f{ move(rd), move(rd) }, 100.f, sf::Color(rgb(rd), rgb(rd), rgb(rd))
				));
		}
	*/
}


