export module Collidable;

import Globals;
import Base;

export enum direc { UP, DOWN, RIGHT, LEFT, NONE };

export class Collidable {
protected:
	sf::FloatRect globalBounds;

	Collidable* _objectColliding;
	Collidable* _lastObjectColliding;
public:
	Collidable() : globalBounds({ {0.f, 0.f}, {0.f, 0.f} }), _objectColliding(nullptr), _lastObjectColliding(nullptr) {}
	~Collidable() { delete _objectColliding, _lastObjectColliding; }

	virtual bool isInCollisionWith(Collidable* ob) {
		if (ob->getGlobalBounds().intersects(this->getGlobalBounds())) {
			return true;
		}
		return false;
	};
	virtual void afterCollision() {	}

	direc getVerticalDirectionOfCollidingObject() {
		if (_objectColliding) {
			Base* obB = dynamic_cast<Base*>(_objectColliding);
			Base* thisB = dynamic_cast<Base*>(this);

			if (thisB->getPosition().y > obB->getPosition().y) return UP;
			else if (thisB->getPosition().y < obB->getPosition().y) return DOWN;

		}
		return NONE;
	}
	direc getHorizontalDirectionOfCollidingObject() {
		if (_objectColliding) {
			Base* obB = dynamic_cast<Base*>(_objectColliding);
			Base* thisB = dynamic_cast<Base*>(this);

			if (thisB->getPosition().x < obB->getPosition().x) return RIGHT;
			else if (thisB->getPosition().x > obB->getPosition().x) return LEFT;

		}
		return NONE;
	}

	bool isCollisionHorizontal() {
		if (_objectColliding) {

			if (this->getGlobalBounds().top < _objectColliding->getGlobalBounds().top
				and this->getGlobalBounds().top + this->getGlobalBounds().height - 5.f > 
				_objectColliding->getGlobalBounds().top) return true;

		}
		return false;
	}

	bool isCollisionFullLengthHorizontal() {
		if (_objectColliding) {

			if (this->getGlobalBounds().top > _objectColliding->getGlobalBounds().top
				and this->getGlobalBounds().top + this->getGlobalBounds().height - 15.f <
				_objectColliding->getGlobalBounds().top + _objectColliding->getGlobalBounds().height) return true;

		}
		return false;
	}

	bool putObjectColliding(Collidable* ob) {
		if (ob == _objectColliding) return false;
		//delete _objectColliding;
		_objectColliding = ob; return true;
	}

	bool putLastObjectColliding(Collidable* ob) {
		if (ob == _lastObjectColliding) return false;
		//delete _objectColliding;
		_lastObjectColliding = ob; return true;
	}

	Collidable* getLastObjectColliding() {
		return _lastObjectColliding;
	}

	Collidable* getObjectColliding() {
		return _objectColliding;
	}

	sf::FloatRect getGlobalBounds() {
		return globalBounds;
	}
};