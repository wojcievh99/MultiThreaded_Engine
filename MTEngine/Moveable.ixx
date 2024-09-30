export module Moveable;

import Globals;

export class Moveable {
	sf::Vector2f __moveDirection;
public:
	Moveable (sf::Vector2f _newMoveDir = sf::Vector2f(0.f, 0.f)) : __moveDirection(_newMoveDir) {}

	void setMoveDirection(sf::Vector2f _newMoveDir) { __moveDirection = _newMoveDir; }

	virtual void moveObject() = 0;

	sf::Vector2f getMoveDir() { return __moveDirection; }
};