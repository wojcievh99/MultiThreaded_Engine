export module Collidable;

import Globals;

export class Collidable {
	sf::FloatRect __objectBounds;
protected:
	std::weak_ptr<Collidable> _objectColliding;
	std::weak_ptr<Collidable> _lastObjectColliding;
public:
	Collidable(sf::FloatRect objectBounds = { {0.f, 0.f}, {0.f, 0.f} }) : __objectBounds(objectBounds) {}

	virtual bool isInCollisionWith(std::weak_ptr<Collidable> ob) = 0;
	virtual void afterCollision() = 0;

	virtual bool isCollisionPossible(std::weak_ptr<Collidable> ob) {
		return this->__objectBounds.intersects(ob.lock()->__objectBounds);
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

	bool updateObjectGlobalBounds(sf::FloatRect newObjectBounds) {
		if (this->__objectBounds == newObjectBounds) return false;
		this->__objectBounds = newObjectBounds; return true;
	}
};