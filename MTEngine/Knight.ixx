export module Knight;

import Globals;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Updateable;
import Animateable;
import Collidable;

export class Knight : public Base, public Drawable, public Moveable, 
public Eventable, public Updateable, public Animateable, public Collidable 
{
	sf::Vector2f scale;
	bool showBounds;
public:
	Knight(sf::Vector2f _pos, sf::Vector2f _scale)
		: Base(typeid(this).raw_name(), _pos), Animateable("textures/KillerQueen/Characters/KnightSilver_processed", 5),
		Collidable(), scale(_scale), showBounds(false)
	{
		this->body.setPosition(this->object_position);
		this->body.setScale(scale);

		this->setFormalTexFile("Idle", "Idle_info");

		this->globalBounds = this->body.getGlobalBounds();
		this->setAccelerationDirection({ 0.f, 0.1f });

		this->addKeyAssociation(sf::Keyboard::LControl, Functor(
			[this]() {
				this->showBounds = !this->showBounds;
			}
		));
		this->addKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				this->setFormalTexFile("Walk", "Walk_info");
				this->body.setScale(sf::Vector2f{ scale.x, scale.y });
				this->setMoveDirection({ this->getCurrentMoveDir().x + .5f, this->getCurrentMoveDir().y });
			}
		));
		this->addReleaseKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				this->setFormalTexFile("Idle", "Idle_info");
				this->setMoveDirection({ this->getCurrentMoveDir().x - .5f, this->getCurrentMoveDir().y });

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

	}

	void updateAnimation() {

	}

	void afterCollision() {
		this->setAccelerationDirection({ this->getCurrentAccDir().x, 0.f });
		this->setMoveDirection({ this->getCurrentMoveDir().x, 0.f});
	}

};