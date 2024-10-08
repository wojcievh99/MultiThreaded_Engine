export module Moveable;

import Globals;

export class Moveable {
	sf::Vector2f __moveDirection;
	sf::Vector2f __acceleration;
public:
	void setMoveDirection(sf::Vector2f _newMoveDir) { __moveDirection = _newMoveDir; }
	void setAccDirection(sf::Vector2f _newAccDir) { __acceleration = _newAccDir; }

	virtual void moveObject() = 0;
	void accelerateObject() {
		__moveDirection += __acceleration;
	}

	sf::Vector2f getMoveDir() { return __moveDirection; }
	sf::Vector2f getAccDir() { return __acceleration; }

};