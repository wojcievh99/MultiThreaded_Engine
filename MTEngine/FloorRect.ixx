export module FloorRect;

import Globals;

import Base;
import Drawable;
import Collidable;

export class FloorRect : public Base, public Drawable, public Collidable {
	sf::RectangleShape _body;

public:
	FloorRect(sf::Vector2f position, sf::Color color) : Base(typeid(this).raw_name()) 
	{
		_body.setPosition(position);
		_body.setFillColor(color);
		_body.setSize(sf::Vector2f(150.f, 150.f));
	}

	void drawObject() {
		window->draw(_body);
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