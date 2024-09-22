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
public:
	Particle(sf::Vector2f _pos, sf::Vector2f __moveDir,
		float __radius, sf::Color _c = sf::Color(255, 255, 255))
		: Base(typeid(this).raw_name(), _pos), Moveable(__moveDir),
		Collidable(_body.getGlobalBounds()), _radius(__radius)
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
			return true;
		}
		return false;
	};

	void afterCollision() {
		if (std::shared_ptr<Particle> other = std::dynamic_pointer_cast<Particle>(_objectColliding.lock())) {
			// old logic (works but is less accurate):
			sf::Vector2f bOb_pos = other->getPosition();
			sf::Vector2f newMoveDirection = sf::Vector2f{
				(((this->getPosition().x + this->_radius) - (bOb_pos.x + other->_radius)) / (this->_radius / other->_radius))
				/ 1000.f + this->getMoveDir().x / 2.f,
				(((this->getPosition().y + this->_radius) - (bOb_pos.y + other->_radius)) / (this->_radius / other->_radius))
				/ 1000.f + this->getMoveDir().y / 2.f
			};

			//std::cout << this->getID() << ": "
				//<< this->getCurrentMoveDir().x << " | " << this->getCurrentMoveDir().y << " <to> "
				//<< newMoveDirection.x << " | " << newMoveDirection.y << std::endl;

			setMoveDirection(newMoveDirection);

		}
		else {
			sf::Vector2f current = getMoveDir();
			setMoveDirection({ -current.x, -current.y });
		}
		moveObject(); // safety: still the logic&calc thread is working linearly.
	};

};

