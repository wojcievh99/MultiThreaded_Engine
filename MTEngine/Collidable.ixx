export module Collidable;

import Globals;

export class Collidable {
protected:
	std::weak_ptr<Collidable> _objectColliding;
	std::weak_ptr<Collidable> _lastObjectColliding;
public:

	virtual sf::FloatRect getObjectBounds() = 0;

	virtual bool isInCollisionWith(std::weak_ptr<Collidable> ob) {
		return isCollisionPossible(ob);
	}
	virtual void afterCollision() = 0;

	virtual bool isCollisionPossible(std::weak_ptr<Collidable> ob) {
		return this->getObjectBounds().intersects(ob.lock()->getObjectBounds());
	}

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