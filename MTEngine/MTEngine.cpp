// MTEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

import std;
import Engine;

import Circle;
import Player;
import Rectangle;
import Line;
import Graph;

int main()
{
	std::pair<int, int> windowSize = std::make_pair( 1800, 1400 );
	std::pair<int, int> unitSize = std::make_pair(50, 50);

	//						(size, windowName, resizable, framerate);
	bool init = engine.init(windowSize, "FunctionRecall", false, 60);

	for (int i = 0; i <= windowSize.first; i += unitSize.first) {
		if (i != unitSize.first * (windowSize.first / (2 * unitSize.first)))
			engine.addObject<Line>(std::make_shared<Line>(
				std::make_pair(sf::Vector2f{ i + 0.f, 0.f }, sf::Vector2f{ i + 0.f, windowSize.second + 0.f }),
				sf::Color(80, 80, 80)
			));
		else 
			engine.addObject<Line>(std::make_shared<Line>(
				std::make_pair(sf::Vector2f{ i + 0.f, 0.f }, sf::Vector2f{ i + 0.f, windowSize.second + 0.f })
			));
	}

	for (int i = 0; i <= windowSize.second; i += unitSize.second) {
		if (i != unitSize.second * (windowSize.second / (2 * unitSize.second)))
			engine.addObject<Line>(std::make_shared<Line>(
				std::make_pair(sf::Vector2f{ 0.f, i + 0.f }, sf::Vector2f{ windowSize.first + 0.f, i + 0.f }),
				sf::Color(80, 80, 80)
			));
		else
			engine.addObject<Line>(std::make_shared<Line>(
				std::make_pair(sf::Vector2f{ 0.f, i + 0.f }, sf::Vector2f{ windowSize.first + 0.f, i + 0.f })
			));
	}

	engine.addObject<Graph>(std::make_shared<Graph>(
		std::make_pair(sf::Vector2f{ 0.f, windowSize.first + 0.f }, sf::Vector2f{0.f, windowSize.second + 0.f}),
		unitSize.first / 5.f, sf::Vector2f{unitSize.first + 0.f, unitSize.second + 0.f}, sf::Color::Yellow
	));
	
	if (init) engine.run();

	return 0;
}


