export module Moveable;

import Globals;

export class Moveable {
	sf::Vector2f __moveDirection;
	sf::Vector2f __acceleration;
public:
	void setMoveDirection(sf::Vector2f _newMoveDir) { __moveDirection = _newMoveDir; }
	void setAccDirection(sf::Vector2f _newAccDir) { __acceleration = _newAccDir; }

	void setMoveDirectionX(float X) { __moveDirection.x = X; }
	void setMoveDirectionY(float Y) { __moveDirection.x = Y; }
	void setAccDirectionX(float X) { __acceleration.x = X; }
	void setAccDirectionY(float Y) { __acceleration.x = Y; }

	virtual void moveObject() = 0;
	void accelerateObject() {
		__moveDirection += __acceleration;
	}

	sf::Vector2f getMoveDir() { return __moveDirection; }
	sf::Vector2f getAccDir() { return __acceleration; }

};