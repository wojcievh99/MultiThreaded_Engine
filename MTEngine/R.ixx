export module R;

import Globals;

import Base;
import Drawable;
import Collidable;
import Textureable;

export class R : public Base, public Drawable, public Collidable {
	sf::RectangleShape _body;
public:
	R(sf::Vector2f position, sf::Vector2f size, sf::Color color) 
		: Base(typeid(this).raw_name())
	{
		_body.setPosition(position);
		_body.setSize(size);
		_body.setFillColor(color);
	}

	void drawObject() {
		window->draw(this->_body);
	}

	void afterCollision() {}

	sf::Vector2f getPosition() {
		return this->_body.getPosition();
	}

	sf::FloatRect getObjectBounds() {
		return this->_body.getGlobalBounds();
	}

};