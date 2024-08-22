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
		: Base(typeid(this).raw_name(), _pos), Animateable("textures/KillerQueen/Characters/KnightSilver"),
		Collidable(), scale(_scale), showBounds(false)
	{
		this->body.setPosition(this->object_position);
		this->body.setScale(scale);

		this->setFormalTexFile("_Idle", { 10, 1 });

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
		this->body.move(this->getCurrentMoveDir());
	}

	void updateObject() {
		this->globalBounds = this->body.getGlobalBounds();

	}

	void updateAnimation() {

	}

	void afterCollision() {

	}

};