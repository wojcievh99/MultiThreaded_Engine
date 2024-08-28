// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Ball;
import Square;
import Base;

import Globals;

int main()
{

	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1500, 1200 }, "Baller", false, 1000);

	auto p = engine.addObject<Ball>(std::make_shared<Ball>(
		sf::Vector2f{ 400.f, 400.f }, 50.f, 1.f
	));

	
	for (int i = 1; i < 100; i++) 
		auto r = engine.addObject<Square>(
			std::make_shared<Square>(sf::Vector2f{ i*10.f, 1000.f }, sf::Color(230, 230, 230), 10.f)
		);

	for (int i = 1; i < 20; i++)
		auto r = engine.addObject<Square>(
			std::make_shared<Square>(sf::Vector2f{ 1200.f, 10.f * i + 850.f }, sf::Color(230, 230, 230), 10.f)
		);

	for (int i = 1; i < 100; i++)
		auto r = engine.addObject<Square>(
			std::make_shared<Square>(sf::Vector2f{ i * 10.f + 1400.f, 1000.f }, sf::Color(230, 230, 230), 10.f)
		);

	for (int i = 1; i < 50; i++)
		auto r = engine.addObject<Square>(
			std::make_shared<Square>(sf::Vector2f{ 2500.f, 10.f * i + 700.f }, sf::Color(230, 230, 230), 10.f)
		);
	
	engine.lockViewOnObject(std::make_pair(".PEAVBall@@", 1));
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


