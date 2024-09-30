// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;


int main()
{
	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1800, 1200 }, "Engine Test", false, 60);

	
	
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


