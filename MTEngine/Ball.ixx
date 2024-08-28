export module Ball;

import Globals;

import Base;
import Drawable;
import Moveable;
import Collidable;
import Eventable;
import Updateable;
import Physicsable;

export class Ball
	: public Base, public Drawable, public Moveable, public Collidable, public Eventable, public Updateable, public Physicsable
{
	sf::CircleShape body;
	sf::Int32 prevTime;

public:
	Ball(sf::Vector2f _pos, float _radius, float _mass, sf::Color c = sf::Color::White)
		: Base(typeid(this).raw_name(), _pos), Collidable(), Physicsable(_mass),
		prevTime(globalClock.getElapsedTime().asMilliseconds())
	{
		body.setPosition(this->object_position);
		body.setFillColor(c);
		body.setRadius(_radius);
		body.setOrigin(sf::Vector2f{ _radius, _radius });

		this->addNotRepeatedForce(sf::Vector2f{ 0.f, 0.005f * this->getObjectMass() });
		this->lockEvents();

		this->globalBounds = body.getGlobalBounds();

		this->addKeyAssociation(sf::Keyboard::Right, Functor(
			[this]() {
				this->prevTime = globalClock.getElapsedTime().asMilliseconds();
			}
		));

		this->addReleaseKeyAssociation(sf::Keyboard::Right, Functor(
			[this]() {
				sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds() - this->prevTime;
				if (this->getCurrentAccDir().x <= 0.f)
					this->setAccelerationDirection(sf::Vector2f{ 0.01f * elapsedTime, this->getCurrentAccDir().y });
			}
		));
		this->addKeyAssociation(sf::Keyboard::Left, Functor(
			[this]() {
				this->prevTime = globalClock.getElapsedTime().asMilliseconds();
			}
		));

		this->addReleaseKeyAssociation(sf::Keyboard::Left, Functor(
			[this]() {
				sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds() - this->prevTime;
				if (this->getCurrentAccDir().x <= 0.f)
					this->setAccelerationDirection(sf::Vector2f{ -0.01f * elapsedTime, this->getCurrentAccDir().y });
				
			}
		));

		this->addKeyAssociation(sf::Keyboard::Space, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f{ this->getCurrentMoveDir().x, -2.f });
			}
		));

	}

	void drawObject() {
		window->draw(body);
	}

	void moveObject() {
		body.move(this->getCurrentMoveDir());
	}

	void updateObject() {
		this->object_position = body.getPosition();
		this->globalBounds = sf::FloatRect(body.getGlobalBounds());
		this->setAccelerationDirection(this->sigmaF(true) / this->getObjectMass());
	}

	bool isInCollisionWith(Collidable* ob) {
		Base* ob_B = dynamic_cast<Base*>(ob);

		float dx = abs(this->getPosition().x - ob_B->getPosition().x), 
			  dy = abs(this->getPosition().y - ob_B->getPosition().y);

		float diagonal = sqrt(
			pow(dx, 2) + pow(dy, 2)
		);

		float dist = ob_B->getSize().x / 2.f, dx1;

		if (dx >= dy) dx1 = (dist / dx) * diagonal; // scale times diagonal (since [T]abc ~ [T]def)
		else dx1 = (dist / dy) * diagonal;

		this->setCollisionAngle(atanf(dy / dx));

		if (diagonal <= (dx1 + this->getSize().x)) // dx1 + radius
			return true;

		return false;
	};

	void afterCollision() {
		this->unlockEvents(); 

		this->addNotRepeatedForce(
			sf::Vector2f{ 
				round(cos(this->getCollisionAngle())) * -sigmaF().x,
				round(sin(this->getCollisionAngle())) * -sigmaF().y 
			},
			true // bool -> reaction-force?
		);

		if (round(cos(this->getCollisionAngle())) != 0.f)
			this->setMoveDirection(sf::Vector2f{ 0.f, this->getCurrentMoveDir().y });
		else 
			this->setMoveDirection(sf::Vector2f{ this->getCurrentMoveDir().x, 0.f });

		this->setAccelerationDirection(this->sigmaF(true) / this->getObjectMass());
	}

	void afterCollisionIsResolved() {
		this->lockEvents(); 
		this->clearReactionForces();
	}

	sf::Vector2f getSize() {
		return sf::Vector2f{ body.getRadius(), body.getRadius() };
	};

};