export module Knight;

import Globals;

import Base;
import Drawable;
import Moveable;
import Physicsable;
import Eventable;
import Updateable;
import Animateable;
import Collidable;

export class Knight : public Base, public Drawable, public Moveable, public Physicsable,
public Eventable, public Updateable, public Animateable, public Collidable 
{
	sf::Vector2f scale;
	bool showBounds;
public:
	Knight(sf::Vector2f _pos, sf::Vector2f _scale, float _mass = 1.f)
		: Base(typeid(this).raw_name(), _pos), Animateable("textures/KillerQueen/Characters/KnightSilver_processed", 5),
		Collidable(), Physicsable(_mass), scale(_scale), showBounds(false)
	{
		this->body.setPosition(this->object_position);
		this->body.setScale(scale);

		//this->setFormalTexFile("Idle", "Idle_info");
		this->setFormalTexFile("Jump", "Jump_info");

		this->globalBounds = this->body.getGlobalBounds();

		this->addKeyAssociation(sf::Keyboard::LControl, Functor(
			[this]() {
				this->showBounds = !this->showBounds;
			}
		));
		
	}

	void drawObject() {
		window->draw(this->body);

		if (showBounds) {
			sf::RectangleShape _bounds;
			_bounds.setPosition(this->getGlobalBounds().getPosition());
			_bounds.setSize(this->getGlobalBounds().getSize());
			_bounds.setFillColor(sf::Color(250, 0, 0, 150));
			window->draw(_bounds);
		}
	}

	void moveObject() {
		this->setMoveDirection(this->getCurrentMoveDir() + this->getCurrentAccDir());
		this->body.move(this->getCurrentMoveDir());
	}

	void updateObject() {
		this->globalBounds = this->body.getGlobalBounds();
		this->setAccelerationDirection(this->sigmaF() / this->getObjectMass());
	}

	void updateAnimation() {

	}

	void afterCollision() {
		this->removeForce(sf::Vector2f{ 0.f, 0.1f });

		/*this->setOneTimeTexFile("Land", "Land_info");
		this->setFormalTexFile("Idle", "Idle_info");*/
	}

	void whileCollision() {
		if (this->sigmaF().y == 0.f) this->setMoveDirection({ this->getCurrentMoveDir().x, 0.f });
	}

	void while_No_Collision() {
		this->addForce(sf::Vector2f{ 0.f, 0.1f });
	}

};