// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import MainCharacter;

import FloorRect;

int main()
{
	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1800, 1200 }, "Engine Test", false, 60);

	engine.addObject<FloorRect>(
		std::make_shared<FloorRect>(
			sf::Vector2f(200.f, 200.f),
			sf::Vector2f(500.f, 400.f),
			sf::Color(47, 47, 47)
		)
	);

	engine.addObject<FloorRect>(
		std::make_shared<FloorRect>(
			sf::Vector2f(600.f, 400.f),
			sf::Vector2f(400.f, 100.f),
			sf::Color(47, 47, 47)
		)
	);

	engine.addObject<FloorRect>(
		std::make_shared<FloorRect>(
			sf::Vector2f(900.f, 300.f),
			sf::Vector2f(500.f, 400.f),
			sf::Color(47, 47, 47)
		)
	);

	auto c = engine.addObject<MainCharacter>(
		std::make_shared<MainCharacter>(
			sf::Vector2f(350.f, 350.f)
		)
	);

	engine.lockViewOnObject(
		std::make_pair(c.lock()->getClassName(), c.lock()->getID())
	);

	if (init) engine.run();

	return 0;
}


