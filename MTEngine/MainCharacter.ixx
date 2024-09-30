export module MainCharacter;

import Globals;

import Base;
import Drawable;
import Moveable;
import Collidable;
import Updateable;
import Eventable;

export class MainCharacter : public Base, public Drawable, public Moveable, public Collidable, public Updateable, public Eventable {
	sf::RectangleShape _body;

public:
	MainCharacter(sf::Vector2f position) : Base(typeid(this).raw_name()) 
	{
		_body.setPosition(position);
		_body.setSize(sf::Vector2f(50.f, 80.f));
		_body.setFillColor(sf::Color::White);

		/// KA
		this->addKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f(this->getMoveDir().x + 2.f, this->getMoveDir().y));
			}
		));
		this->addKeyAssociation(sf::Keyboard::A, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f(this->getMoveDir().x - 2.f, this->getMoveDir().y));
			}
		));
		this->addKeyAssociation(sf::Keyboard::W, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f(this->getMoveDir().x, this->getMoveDir().y - 2.f));
			}
		));
		this->addKeyAssociation(sf::Keyboard::S, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f(this->getMoveDir().x, this->getMoveDir().y + 2.f));
			}
		));

		/// RKA
		this->addReleaseKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f(this->getMoveDir().x - 2.f, this->getMoveDir().y));
			}
		));
		this->addReleaseKeyAssociation(sf::Keyboard::A, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f(this->getMoveDir().x + 2.f, this->getMoveDir().y));
			}
		));
		this->addReleaseKeyAssociation(sf::Keyboard::W, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f(this->getMoveDir().x, this->getMoveDir().y + 2.f));
			}
		));
		this->addReleaseKeyAssociation(sf::Keyboard::S, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f(this->getMoveDir().x, this->getMoveDir().y - 2.f));
			}
		));

	}

	void drawObject() {
		window->draw(_body);
	}

	void moveObject() {
		_body.move(this->getMoveDir());
	}

	void updateObject() {

	}

	void afterCollision() {
		
	}

	sf::Vector2f getPosition() {
		return _body.getPosition();
	}

	sf::FloatRect getObjectBounds() {
		return _body.getGlobalBounds();
	}

};