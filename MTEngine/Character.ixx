export module Character;

import Globals;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Collidable;
import Updateable;
import Animateable;

export class Character : public Base, public Drawable, public Moveable, public Animateable, public Updateable, public Eventable {

public:
	Character(sf::Vector2f position)
		: Base(typeid(this).raw_name(), position), Moveable(), Animateable("textures/character1") 
	{
		this->setAnimationWithIt(this->getAnimationItByInternalName("IDLE"));
		_body.setScale(sf::Vector2f(5.f, 5.f));
		
		this->addKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f(5.f, this->getMoveDir().y));
			}
		));
	}

	void drawObject() {
		window->draw(this->_body);
	}

	void moveObject() {
		this->_body.move(this->getMoveDir());
	}

	void updateObject() {
		this->_body.setPosition(this->getPosition());
	}

};