// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Circle;
import Player;
import Rectangle;
import Base;

import Globals;

std::vector<std::weak_ptr<Base>> v;

void updMap() {
	float _lastRender = 1490;
	bool rendered = false;

	auto p = engine.addObject<Player>(
		std::make_shared<Player>(sf::Vector2f{ 100.f, 500.f }, sf::Vector2f{ 2.f, 2.f })
	);

	while (isWindowOpen) {
		if (p.lock()->getPosition().x > _lastRender) {
			if (!rendered) {
				rendered = true;
				for (size_t i = 0; i < v.size(); i++) {
					if (v[i].lock() ->getPosition().x + v[i].lock()->getDimensions().x < _lastRender)
					{
						v[i].lock()->garbage();
						v.erase(v.begin() + i--);
						continue;
					}
					v[i].lock()->resetToRender();
				}
			}
		}
		else rendered = false;
	}
}

int main()
{

	//						(size, windowName, resizable, framerate);
	bool init = engine.init({ 1500, 1200 }, "TEST", false, 60);

	auto r = engine.addObject<Rectangle>(
		std::make_shared<Rectangle>(sf::Vector2f{ 0.f, 1000.f }, sf::Color(50, 180, 80), sf::Vector2f{1500.f, 200.f})
	);

	v.push_back(engine.addObject<Rectangle>(
		std::make_shared<Rectangle>(sf::Vector2f{ 800.f, 700.f }, sf::Color(100, 100, 100), sf::Vector2f{ 500.f, 300.f })
	));
	v.push_back(engine.addObject<Rectangle>(
		std::make_shared<Rectangle>(sf::Vector2f{ 1300.f, 500.f }, sf::Color(100, 100, 100), sf::Vector2f{ 800.f, 50.f })
	));
	v.push_back(engine.addObject<Rectangle>(
		std::make_shared<Rectangle>(sf::Vector2f{ 2300.f, 300.f }, sf::Color(100, 100, 100), sf::Vector2f{ 500.f, 50.f })
	));
	
	sf::Thread updateMapThread(&updMap);
	updateMapThread.launch();
	
	if (init) engine.run();

	updateMapThread.wait();
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


