export module Collidable;

import Globals;
import Base;

export class Collidable {
protected:
	sf::FloatRect globalBounds;

	Collidable* _objectColliding;
	Collidable* _lastObjectColliding;
public:
	Collidable() : globalBounds({ {0.f, 0.f}, {0.f, 0.f} }), _objectColliding(nullptr), _lastObjectColliding(nullptr) {}
	~Collidable() { delete _objectColliding; delete _lastObjectColliding; }

	virtual bool isInCollisionWith(Collidable* ob) = 0;
	virtual void afterCollision() = 0;

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
};