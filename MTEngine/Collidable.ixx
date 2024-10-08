export module Collidable;

import Globals;

export class Collidable {
protected:
	std::set<std::shared_ptr<Collidable>> _objectColliding;
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
		if (_objectColliding.contains(ob)) return false;
		_objectColliding.insert(ob); return true;
	}
	bool eraseObjectColliding(std::shared_ptr<Collidable> ob) {
		if (_objectColliding.contains(ob))
		{
			_objectColliding.erase(ob); return true;
		}
		return false;
	}

	bool checkCollisionList(std::shared_ptr<Collidable> ob) {
		if (_objectColliding.contains(ob)) return true;
		return false;
	}

};