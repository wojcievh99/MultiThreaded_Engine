export module Moveable;

import Globals;

export class Moveable {
	sf::Vector2f _moveDirection;
public:
	Moveable (sf::Vector2f _newMoveDir = sf::Vector2f{0.f, 0.f}) : _moveDirection(_newMoveDir) {}

	void setMoveDirection(sf::Vector2f _newMoveDir) { _moveDirection = _newMoveDir; }

	virtual void moveObject() = 0;

	sf::Vector2f getCurrentMoveDir() { return _moveDirection; }
};