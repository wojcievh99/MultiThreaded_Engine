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
	MainCharacter(sf::Vector2f position) : Base(typeid(this).raw_name()) {

	}

	sf::Vector2f getPosition() {
		return _body.getPosition();
	}

};