export module Particle;

import Globals;
import Base;
import Drawable;
import Moveable;
import Eventable;
import Collidable;
import Updateable;

export class Particle : public Base, public Drawable, public Updateable, public Moveable, public Collidable, public Eventable {
	sf::CircleShape _body;
	float _radius;

	unsigned long long int collisionCount;
public:
	Particle(sf::Vector2f _pos, sf::Vector2f __moveDir,
		float __radius, sf::Color _c = sf::Color(255, 255, 255))
		: Base(typeid(this).raw_name(), _pos), Moveable(__moveDir),
		Collidable(_body.getGlobalBounds()), _radius(__radius), collisionCount(0)
	{
		_body.setRadius(_radius);
		_body.setFillColor(_c);
		_body.setPosition(_pos);
	}

	void drawObject() {
		window->draw(_body);
	}

	void updateObject() {
		this->updateObjectGlobalBounds(_body.getGlobalBounds());
		this->_object_position = _body.getPosition();
		this->_radius = _body.getRadius();

		if (collisionCount > 100) this->_object_alive = false;

		if ((this->_object_position.x + 2 * _radius) >= window->getSize().x or this->_object_position.x <= 0) {
			this->setMoveDirection(sf::Vector2f{ -this->getMoveDir().x, this->getMoveDir().y });
		}
		if ((this->_object_position.y + 2 * _radius) >= window->getSize().y or this->_object_position.y <= 0) {
			this->setMoveDirection(sf::Vector2f{ this->getMoveDir().x, -this->getMoveDir().y });
		}

		//std::cout << this->object_position.x << "; " << this->object_position.y << std::endl;

		moveObject();
	}

	void moveObject() {
		//std::cout << this->getID() << ": " << this->getCurrentMoveDir().y << std::endl;
		_body.move(this->getMoveDir());
	}

	bool isInCollisionWith(std::weak_ptr<Collidable> ob) {
		sf::Vector2f obPosition = std::dynamic_pointer_cast<Base>(ob.lock())->getPosition();
		float obRadius = std::dynamic_pointer_cast<Particle>(ob.lock())->_radius;

		float diagonal =
			sqrt(
				pow(abs((obPosition.x + obRadius) - (this->_object_position.x + this->_radius)), 2) +
				pow(abs((obPosition.y + obRadius) - (this->_object_position.y + this->_radius)), 2)
			);

		//std::cout << diagonal << " <= " << (obRadius + this->_radius) << std::endl;
		if (diagonal <= (obRadius + this->_radius)) {
			collisionCount += 1;
			return true;
		}
		return false;
	};

	void afterCollision() {
		if (std::shared_ptr<Particle> other = std::dynamic_pointer_cast<Particle>(_objectColliding.lock())) {
			sf::Vector2f newMoveDirection;

			sf::Vector2f delta = other->getPosition() - this->getPosition();
			float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
			sf::Vector2f normal = delta / distance;

			sf::Vector2f relativeVelocity = other->getMoveDir() - this->getMoveDir();

			float velocityAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

			if (velocityAlongNormal > 0) return;

			float impulseScalar = (2 * velocityAlongNormal) / (other->_radius + this->_radius);

			sf::Vector2f impulse = normal * impulseScalar;

			newMoveDirection = this->getMoveDir() + impulse * other->_radius;
			this->setMoveDirection(newMoveDirection);

			newMoveDirection = this->getMoveDir() - impulse * other->_radius;
			other->setMoveDirection(newMoveDirection);

		}
		else {
			sf::Vector2f current = getMoveDir();
			setMoveDirection({ -current.x, -current.y });
		}
		//moveObject(); // safety: still the logic&calc thread is working linearly.
	};

};

