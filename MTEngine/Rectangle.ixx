export module Rectangle;

import Globals;
import Base;
import Drawable;
import Collidable;
import Updateable;

export class Rectangle : public Base, public Drawable, public Collidable, public Updateable {
	sf::RectangleShape body;
public:
	Rectangle(sf::Vector2f _pos, sf::Color color, sf::Vector2f _size) : Base(typeid(this).raw_name(), _pos) {
		body.setPosition(this->object_position);
		body.setSize(_size);
		body.setFillColor(color);

		this->globalBounds = body.getGlobalBounds();

	}

	void drawObject() {
		window->draw(body);
	}

	void updateObject() {
		this->globalBounds = body.getGlobalBounds();
	}


};