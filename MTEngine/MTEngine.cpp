// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Circle;
import Player;
import Rectangle;
import Line;

import Globals;

int main()
{
	sf::Int32 __timeInterval;

	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1500, 1200 }, "TEST", false, 60);
	
	/*
	auto c = engine.addObject<Circle>(std::make_shared<Circle>(sf::Vector2f{ 700.f, 500.f }, sf::Vector2f(0.f, 0.f), 50.f, sf::Color::White));

	c.lock()->addKeyAssociation(sf::Keyboard::D, Functor(
		[&__timeInterval]() {
			__timeInterval = globalClock.getElapsedTime().asMilliseconds();
		}
	));
	c.lock()->addReleaseKeyAssociation(sf::Keyboard::D, Functor(
		[c, &__timeInterval]() {
			__timeInterval -= globalClock.getElapsedTime().asMilliseconds();
			c.lock()->setMoveDirection(sf::Vector2f{0.005f * abs(__timeInterval), 0.f});
		}
	));
	*/

	auto l = engine.addObject<Line>(std::make_shared<Line>(
		std::make_pair( sf::Vector2f{700.f, 100.f}, sf::Vector2f{1000.f, 200.f}), 2
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


