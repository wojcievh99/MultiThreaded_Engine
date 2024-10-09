export module MainCharacter;

import Globals;

import Base;
import Drawable;
import Moveable;
import Collidable;
import Updateable;
import Eventable;
import Animateable;

export class MainCharacter : public Base, public Drawable, public Moveable, public Collidable, public Updateable, public Eventable, public Animateable {
	sf::RectangleShape __showbounds; bool sb;

public:
	MainCharacter(sf::Vector2f position) : Base(typeid(this).raw_name()), Animateable("textures/character1")
	{
		this->_body.setPosition(position);
		this->_body.setOrigin(sf::Vector2f(25.f, 40.f));

		this->setAnimationWithIt(this->getAnimationItByInternalName("IDLE"));
		this->_body.setScale(sf::Vector2f(2.f, 2.f));

		__showbounds.setFillColor(sf::Color(150, 10, 10, 100));
		__showbounds.setOutlineColor(sf::Color::White);

		this->addKeyAssociation(sf::Keyboard::LControl, Functor(
			[this]() {
				this->sb = !this->sb;
			}
		));
		sb = false;

		this->setAccDirection(sf::Vector2f(0.f, .5f));

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

		this->addKeyAssociation(sf::Keyboard::Space, Functor(
			[this]() {
				if (this->checkCollisionSide().contains(LEFT_BOTTOM) and this->checkCollisionSide().contains(RIGHT_BOTTOM))
					this->setMoveDirection(sf::Vector2f(this->getMoveDir().x, this->getMoveDir().y - 15.f));
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

	}

	void drawObject() {
		window->draw(this->_body);

		if (sb) {
			__showbounds.setPosition(_body.getGlobalBounds().getPosition());
			__showbounds.setSize(_body.getGlobalBounds().getSize());

			window->draw(__showbounds);
		}
	}

	void moveObject() {
		_body.move(this->getMoveDir());
	}

	void updateObject() {
		std::set<collisionSide> cs = this->checkCollisionSide();

		if (!cs.size()) this->setAccDirection(sf::Vector2f(0.f, .5f));
	
	}

	void afterCollision() {
		std::set<collisionSide> cs = this->checkCollisionSide();

		if (cs.contains(LEFT_BOTTOM) or cs.contains(RIGHT_BOTTOM)) {
			this->setAccDirection(sf::Vector2f(0.f, 0.f));
			this->setMoveDirection(sf::Vector2f(this->getMoveDir().x, 0.f));
		}

	}

	sf::Vector2f getPosition() {
		return _body.getPosition();
	}

	sf::FloatRect getObjectBounds() {
		return _body.getGlobalBounds();
	}

};