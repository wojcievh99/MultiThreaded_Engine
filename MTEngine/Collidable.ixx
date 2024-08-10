export module Collidable;

import Globals;
import Base;

export class Collidable {
protected:
	Collidable* _objectColliding;
	Collidable* _lastObjectColliding;
public:
	Collidable() : _objectColliding(nullptr), _lastObjectColliding(nullptr) {}
	~Collidable() { delete _objectColliding; delete _lastObjectColliding; }

	virtual bool isInCollisionWith(Collidable* ob) = 0;
	virtual void afterCollision() = 0;

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