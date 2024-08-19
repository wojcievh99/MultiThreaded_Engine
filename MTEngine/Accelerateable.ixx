export module Accelerateable;

import Globals;

export class Accelerateable {
	sf::Vector2f acc;
public:
	Accelerateable(sf::Vector2f _acc = sf::Vector2f{0.f, 0.f}) : acc(_acc) {}

	virtual void accelerateObject() = 0;

	sf::Vector2f getAcceleration() {
		return acc;
	}
	sf::Vector2f setAcceleration(sf::Vector2f newAcc) {
		acc = newAcc;
		return acc;
	}

};