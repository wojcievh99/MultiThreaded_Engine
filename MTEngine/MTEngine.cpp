// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import MainCharacter;

import R;

int main()
{
	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1800, 1200 }, "ShadowFighter", false, 60); 

	auto c = engine.addObject<MainCharacter>(
		std::make_shared<MainCharacter>(
			sf::Vector2f(350.f, 350.f)
		)
	);

	engine.addObject<R>(std::make_shared<R>(
		sf::Vector2f(100.f, 100.f),
		sf::Vector2f(200.f, 100.f),
		sf::Color::Green
	));

	engine.lockViewOnObject(
		std::make_pair(c.lock()->getClassName(), c.lock()->getID())
	);

	if (init) engine.run();

	return 0;
}


