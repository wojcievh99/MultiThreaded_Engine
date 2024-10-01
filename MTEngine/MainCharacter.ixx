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

	std::vector<bool> _points; // 0: left-top, 1. right-top, 2. left-bottom, 3. right-bottom 
public:
	MainCharacter(sf::Vector2f position) : Base(typeid(this).raw_name()), _points({true, true, true, true})
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

		for (const auto& e : this->_objectColliding) {
			if (e->getObjectBounds()
				.contains(sf::Vector2f(
					this->getObjectBounds().left, 
					this->getObjectBounds().top))
				) 
			{
				_points[0] = true;
			}
			if (e->getObjectBounds()
				.contains(sf::Vector2f(
					this->getObjectBounds().left + this->getObjectBounds().width, 
					this->getObjectBounds().top))
				)
			{
				_points[1] = true;
			}
			if (e->getObjectBounds()
				.contains(sf::Vector2f(
					this->getObjectBounds().left, 
					this->getObjectBounds().top + this->getObjectBounds().height))
				)
			{
				_points[2] = true;
			}
			if (e->getObjectBounds()
				.contains(sf::Vector2f(
					this->getObjectBounds().left + this->getObjectBounds().width, 
					this->getObjectBounds().top + this->getObjectBounds().height))
				)
			{
				_points[3] = true;
			}
		}

		if (!_points[0] and !_points[2]) {
			this->lockIndEvent(sf::Keyboard::A);
			this->setMoveDirection(sf::Vector2f(0.f, this->getMoveDir().y));
		}
		else this->unlockIndEvent(sf::Keyboard::A);

		if (!_points[1] and !_points[3]) {
			this->lockIndEvent(sf::Keyboard::D);
			this->setMoveDirection(sf::Vector2f(0.f, this->getMoveDir().y));
		}
		else this->unlockIndEvent(sf::Keyboard::D);

		if (!_points[0] and !_points[1]) {
			this->lockIndEvent(sf::Keyboard::W);
			this->setMoveDirection(sf::Vector2f(this->getMoveDir().x, 0.f));
		}
		else this->unlockIndEvent(sf::Keyboard::W);

		if (!_points[2] and !_points[3]) {
			this->lockIndEvent(sf::Keyboard::S);
			this->setMoveDirection(sf::Vector2f(this->getMoveDir().x, 0.f));
		}
		else this->unlockIndEvent(sf::Keyboard::S);

		_points = { false, false, false, false };
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