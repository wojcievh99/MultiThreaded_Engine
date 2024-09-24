export module Character;

import Globals;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Collidable;
import Updateable;
import Animateable;

export class Character : public Base, public Drawable, public Animateable, public Updateable {

public:
	Character(sf::Vector2f position)
		: Base(typeid(this).raw_name(), position), Animateable("textures/character1") 
	{
		this->setAnimationWithIt(this->getAnimationItByInternalName("IDLE"));
		_body.setScale(sf::Vector2f(5.f, 5.f));
	}

	void drawObject() {
		window->draw(this->_body);
	}

	void updateObject() {
		this->_body.setPosition(this->getPosition());
	}

};