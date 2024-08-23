// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Circle;
import Knight;
import Rectangle;
import Base;

import Globals;

int main()
{

	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1500, 1200 }, "Killer Queen", false, 800);

	auto r = engine.addObject<Rectangle>(
		std::make_shared<Rectangle>(sf::Vector2f{ 200.f, 1000.f }, sf::Color(250, 250, 250), sf::Vector2f{500.f, 100.f})
	);

	auto p = engine.addObject<Knight>(std::make_shared<Knight>(
		sf::Vector2f{300.f, 300.f}, sf::Vector2f{3.f, 3.f}
	));

	
	
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


