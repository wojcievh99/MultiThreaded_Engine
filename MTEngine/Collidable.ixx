export module Collidable;

import Globals;

export enum collisionSide {
	LEFT_TOP, RIGHT_TOP, LEFT_BOTTOM, RIGHT_BOTTOM
};

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

	// acctually returns angles of global bounds that are colliding
	std::set<collisionSide> checkCollisionSide() { 

		std::set<collisionSide> result;

		for (const auto& e : this->_objectColliding) {
			if (e->getObjectBounds()
				.contains(sf::Vector2f(
					this->getObjectBounds().left,
					this->getObjectBounds().top))
				)
			{
				result.insert(LEFT_TOP);
			}
			if (e->getObjectBounds()
				.contains(sf::Vector2f(
					this->getObjectBounds().left + this->getObjectBounds().width,
					this->getObjectBounds().top))
				)
			{
				result.insert(RIGHT_TOP);
			}
			if (e->getObjectBounds()
				.contains(sf::Vector2f(
					this->getObjectBounds().left,
					this->getObjectBounds().top + this->getObjectBounds().height))
				)
			{
				result.insert(LEFT_BOTTOM);
			}
			if (e->getObjectBounds()
				.contains(sf::Vector2f(
					this->getObjectBounds().left + this->getObjectBounds().width,
					this->getObjectBounds().top + this->getObjectBounds().height))
				)
			{
				result.insert(RIGHT_BOTTOM);
			}
		}

		return result;
	}

};