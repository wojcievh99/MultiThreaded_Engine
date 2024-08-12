export module Circle;

import Globals;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Collidable;
import Updateable;

export class Circle : public Base, public Drawable, public Updateable, public Moveable, public Collidable, public Eventable {
	sf::CircleShape _body;
	float _radius;
public:
	Circle(sf::Vector2f _pos, sf::Vector2f __moveDir,
		   float __radius, sf::Color _c = sf::Color(255, 255, 255)) 
		:  Base(typeid(this).raw_name(), _pos), Moveable(__moveDir),
		   Collidable(), _radius(__radius)
	{
		_body.setRadius(_radius);
		_body.setFillColor(_c);
		_body.setPosition(_pos);
	}

	float getRadius() {
		return _radius;
	}

	void drawObject() {
		window->draw(_body);
	}

	void updateObject() {
		this->object_position = _body.getPosition();
		this->_radius = _body.getRadius();

		moveObject();
	}

	void moveObject() {
		//std::cout << this->getID() << ": " << this->getCurrentMoveDir().y << std::endl;
		_body.move(this->getCurrentMoveDir());
	}

	bool isInCollisionWith(Collidable* ob) {
		sf::Vector2f obPosition = dynamic_cast<Base*>(ob)->getCurrentPosition();
		float obRadius = dynamic_cast<Circle*>(ob)->getRadius();

		float diagonal =
			sqrt(
				pow(abs((obPosition.x + obRadius) - (this->object_position.x + this->_radius)), 2) +
				pow(abs((obPosition.y + obRadius) - (this->object_position.y + this->_radius)), 2)
			);
		
		//std::cout << diagonal << " <= " << (obRadius + this->_radius) << std::endl;
		if (diagonal <= (obRadius + this->_radius)) {
			return true;
		}
		return false;
	};

	void afterCollision() {
		if (this->getCurrentMoveDir() != sf::Vector2f{ 0.f, 0.f }) {
			if (Circle* other = dynamic_cast<Circle*>(_objectColliding)) {
				// old logic (works but is less accurate):
				sf::Vector2f bOb_pos = other->getCurrentPosition();
				sf::Vector2f newMoveDirection = sf::Vector2f{
					(((this->getCurrentPosition().x + this->_radius) - (bOb_pos.x + other->_radius)) / (this->_radius / other->_radius))
					/ 1000.f + this->getCurrentMoveDir().x / 2.f,
					(((this->getCurrentPosition().y + this->_radius) - (bOb_pos.y + other->_radius)) / (this->_radius / other->_radius))
					/ 1000.f + this->getCurrentMoveDir().y / 2.f
				};

				//std::cout << this->getID() << ": "
					//<< this->getCurrentMoveDir().x << " | " << this->getCurrentMoveDir().y << " <to> "
					//<< newMoveDirection.x << " | " << newMoveDirection.y << std::endl;

				setMoveDirection(newMoveDirection);

			}
			else {
				sf::Vector2f current = getCurrentMoveDir();
				setMoveDirection({ -current.x, -current.y });
			}
			moveObject();
		}
	};

};