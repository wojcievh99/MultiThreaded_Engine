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
	~Collidable() { delete _objectColliding, _lastObjectColliding; }

	virtual bool isInCollisionWith(Collidable* ob) {
		if (ob->getGlobalBounds().intersects(this->getGlobalBounds())) {
			return true;
		}
		return false;
	};
	virtual void afterCollision() {	}

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

	sf::FloatRect getGlobalBounds() {
		return globalBounds;
	}
};