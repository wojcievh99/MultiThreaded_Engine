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

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			engine.addObject<FloorRect>(
				std::make_shared<FloorRect>(
					sf::Vector2f(200.f + 150.f * j, 200.f + 150.f * i),
					i % 2 == 0 
						? j % 2 == 0 ? sf::Color(74, 74, 74) : sf::Color(47, 47, 47)
						: j % 2 == 0 ? sf::Color(47, 47, 47) : sf::Color(74, 74, 74)
				)
			);
		}
	}

	auto c = engine.addObject<MainCharacter>(
		std::make_shared<MainCharacter>(
			sf::Vector2f(100.f, 100.f)
		)
	);

	engine.lockViewOnObject(
		std::make_pair(c.lock()->getClassName(), c.lock()->getID())
	);

	if (init) engine.run();

	return 0;
}


