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
	virtual void whileCollision() { };
	virtual void afterCollision() {	};

	virtual void while_No_Collision() { };

	virtual bool isCollisionPossible(Collidable* ob) {
		if (this->globalBounds.intersects(ob->globalBounds)) return true;
		return false;
	}
	// ^Saves some calculations - if two objects are far away from each other, then the 
	// isInCollisionWith function (which by design uses more computing power) won't 
	// be executed. Simple optimization.

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