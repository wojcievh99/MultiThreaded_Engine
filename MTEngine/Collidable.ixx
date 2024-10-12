export module Collidable;

import Globals;

export enum collisionCorner {
	LEFT_TOP, RIGHT_TOP, LEFT_BOTTOM, RIGHT_BOTTOM
};
export enum collisionSide {
	LEFT, RIGHT, UP, DOWN
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

	std::set<collisionCorner> checkCollisionCorner() {

		std::set<collisionCorner> result;

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
	// great accuracy	|
	//					V
	std::set<collisionSide> checkCollisionSide(unsigned int divisor) {
		std::set<collisionSide> v;

		for (const auto& object : this->_objectColliding) {
			for (auto side : { LEFT, RIGHT, UP, DOWN }) {
				if (side == LEFT) {
					float space = this->getObjectBounds().height / divisor;
					unsigned int result = 0;
					for (unsigned int d = 0; d <= divisor; d++) {
						if (object->getObjectBounds().contains(
							sf::Vector2f(
								this->getObjectBounds().left,
								this->getObjectBounds().top + (space * d)
							)
						))
							result++;
						if (result > 2) {
							v.insert(side); // LEFT
							break;
						}
					}
				}
				else if (side == RIGHT) {
					float space = this->getObjectBounds().height / divisor;
					unsigned int result = 0;
					for (unsigned int d = 0; d <= divisor; d++) {
						if (object->getObjectBounds().contains(
							sf::Vector2f(
								this->getObjectBounds().left + this->getObjectBounds().width,
								this->getObjectBounds().top + (space * d)
							)
						))
							result++;
						if (result > 2) {
							v.insert(side); // RIGHT
							break;
						}
					}
				}
				else if (side == UP) {
					float space = this->getObjectBounds().width / divisor;
					unsigned int result = 0;
					for (unsigned int d = 0; d <= divisor; d++) {
						if (object->getObjectBounds().contains(
							sf::Vector2f(
								this->getObjectBounds().left + (space * d),
								this->getObjectBounds().top
							)
						))
							result++;
						if (result > 2) {
							v.insert(side); // UP
							break;
						}
					}
				}
				else if (side == DOWN) {
					float space = this->getObjectBounds().width / divisor;
					unsigned int result = 0;
					for (unsigned int d = 0; d <= divisor; d++) {
						if (object->getObjectBounds().contains(
							sf::Vector2f(
								this->getObjectBounds().left + (space * d),
								this->getObjectBounds().top + this->getObjectBounds().height
							)
						))
							result++;
						if (result > 2) {
							v.insert(side); // DOWN
							break;
						}
					}
				}
			}
		}
		return v;
	} 
	// 10-15 is mostly optimal for the divisor but it depends on the actual size

};