export module Moveable;

import Globals;

export class Moveable {
	sf::Vector2f _moveDirection;
	sf::Vector2f _accelerationDirection;
public:
	Moveable (sf::Vector2f _newMoveDir = sf::Vector2f{0.f, 0.f}) : _moveDirection(_newMoveDir) {}

	void setMoveDirection(sf::Vector2f _newMoveDir) { _moveDirection = _newMoveDir; }
	void setAccelerationDirection(sf::Vector2f _newAccDir) { _accelerationDirection = _newAccDir; }

	virtual void moveObject() = 0;

	sf::Vector2f getCurrentMoveDir() { return _moveDirection; }
	sf::Vector2f getCurrentAccDir() { return _accelerationDirection; }
};