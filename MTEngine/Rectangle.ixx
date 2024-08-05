export module Rectangle;

import Globals;
import Base;
import Drawable;

export class Rectangle : public Base, public Drawable {
	sf::RectangleShape body;
public:
	Rectangle(sf::Vector2f _pos, sf::Color color, sf::Vector2f _size) : Base(typeid(this).raw_name(), _pos) {
		body.setPosition(this->object_position);
		body.setSize(_size);
		body.setFillColor(color);
	}

	void drawObject() {
		window->draw(body);
	}

};