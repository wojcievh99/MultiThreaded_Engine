export module Collidable;

import Globals;

export class Collidable {
protected:
	std::weak_ptr<Collidable> _objectColliding;
	std::weak_ptr<Collidable> _lastObjectColliding;
public:
	Collidable() {}

	virtual bool isInCollisionWith(std::shared_ptr<Collidable> ob) = 0;
	virtual void afterCollision() = 0;

	bool putObjectColliding(std::shared_ptr<Collidable> ob) {
		if (ob == _objectColliding.lock()) return false;
		//delete _objectColliding;
		_objectColliding = ob; return true;
	}

	bool putLastObjectColliding(std::shared_ptr<Collidable> ob) {
		if (ob == _lastObjectColliding.lock()) return false;
		//delete _objectColliding;
		_lastObjectColliding = ob; return true;
	}

	std::weak_ptr<Collidable> getLastObjectColliding() {
		return _lastObjectColliding;
	}
};