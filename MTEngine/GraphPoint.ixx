export module GraphPoint;

import Globals;

export class GraphPoint {
	sf::Vector2f point;
public:
	GraphPoint(sf::Vector2f _point = sf::Vector2f{0.f, 0.f}) : point(_point) {}

	void setPosition(sf::Vector2f newPoint) {
		this->point = newPoint;
	}
	sf::Vector2f getPosition() {
		return point;
	}

};