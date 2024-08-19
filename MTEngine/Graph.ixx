export module Graph;

import Globals;

import Base;
import Eventable;

import GraphPoint;
import Line;

import Algorithms;

import Engine;

export class Graph : public Base, public Eventable {
	std::string formula;

	std::vector<std::shared_ptr<GraphPoint>> points;
	std::vector<std::weak_ptr<Line>> lines;

	std::pair<sf::Vector2f, sf::Vector2f> bounds;
	float interval; sf::Color color; sf::Vector2f unitSize;

public:
	Graph(std::pair<sf::Vector2f, sf::Vector2f> _bounds, float _interval, sf::Vector2f _unitSize, sf::Color _color)
		: Base(typeid(this).raw_name(), { 0.f, 0.f }), bounds(_bounds), interval(_interval),
		color(_color), formula(""), unitSize(_unitSize)
	{
		for (float i = bounds.first.x; i <= bounds.first.y; i += interval) {
			points.push_back(std::make_shared<GraphPoint>(
				sf::Vector2f{ i, bounds.second.y / 2.f }
			));
		}

		this->addKeyAssociation(sf::Keyboard::Space, Functor(
			[this]() {
				std::cout << "\n<== Enter function formula: ==>\n";
				std::getline(std::cin, formula);
				std::cout << "<== Calculating ==>\n";

				for (size_t i = 0; i < lines.size(); i++) {
					lines[i].lock()->garbage();
					lines.erase(lines.begin());
					i--;
				}

				for (int p = 0; p < points.size(); p++) {
					sf::Vector2f newPos = points[p]->getPosition();
					/*newPos.y = 24.f * pow((newPos.x - bounds.first.y / 2.f), 2) + 250.f * (newPos.x - bounds.first.y / 2.f) - 20.f;*/
					newPos.y = bounds.second.y / 2.f - compute(formula, (newPos.x - bounds.first.y / 2.f) / unitSize.x) * unitSize.y;
					points[p]->setPosition(newPos);
				}

				for (int i = 0; i < points.size() - 1; i++) {
					lines.push_back(
						engine.addObject<Line>(std::make_shared<Line>(
							std::make_pair(points[i]->getPosition(), points[i + 1]->getPosition()),
							color
						))
					);
				}

			}
		));

	}

};