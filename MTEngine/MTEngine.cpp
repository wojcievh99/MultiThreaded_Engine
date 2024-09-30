// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Character;
import Particle;


int main()
{
	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1800, 1200 }, "Engine Test", false, 60);

	std::random_device rd; std::mt19937 gen(rd());

	std::uniform_int_distribution<int> posX(100, 1700);
	std::uniform_int_distribution<int> posY(100, 1100);

	std::uniform_int_distribution<int> move(0, 1);

	std::uniform_int_distribution<int> radius(100, 100);

	std::uniform_int_distribution<int> rgb(100, 255);

	for (int i = 10; i--;) { 
		auto r = engine.addObject<Particle>(
			std::make_shared<Particle>(
				sf::Vector2f(posX(gen) + 0.f, posY(gen) + 0.f),
				sf::Vector2f(move(gen) - .9f, move(gen) - .9f),
				radius(gen) + 0.f, sf::Color(rgb(gen), rgb(gen), rgb(gen))
			)
		);

	}
	
	/*auto r = engine.addObject<Character>(std::make_shared<Character>(sf::Vector2f(100.f, 100.f)));
	engine.addObject<Particle>(
		std::make_shared<Particle>(
			sf::Vector2f(100.f, 200.f),
			sf::Vector2f(0.f, 0.f),
			50.f,
			sf::Color::Red
		));

	engine.lockViewOnObject(std::make_pair(r.lock()->getClassName(), r.lock()->getID()));*/

	if (init) engine.run();

	return 0;
}


