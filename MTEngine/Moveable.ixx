export module Moveable;

import Globals;

export class Moveable {
	sf::Vector2f __moveDirection;
public:
	void setMoveDirection(sf::Vector2f _newMoveDir) { __moveDirection = _newMoveDir; }

	virtual void moveObject() = 0;

	sf::Vector2f getMoveDir() { return __moveDirection; }
};