export module Moveable;

import Globals;
import Accelerateable;

export class Moveable : public Accelerateable {
	sf::Vector2f _moveDirection;
public:
	Moveable (sf::Vector2f _newMoveDir = sf::Vector2f{0.f, 0.f}) 
		: Accelerateable(), _moveDirection(_newMoveDir) {}

	void setMoveDirection(sf::Vector2f _newMoveDir) { _moveDirection = _newMoveDir; }

	void accelerateObject() {
		_moveDirection.x += this->getAcceleration().x;
		_moveDirection.y += this->getAcceleration().y;
	}

	virtual void moveObject() = 0;

	sf::Vector2f getCurrentMoveDir() { return _moveDirection; }
};