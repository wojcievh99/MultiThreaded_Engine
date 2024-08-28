export module Square;

import Globals;
import Base;
import Drawable;
import Collidable;
import Updateable;

export class Square : public Base, public Drawable, public Collidable, public Updateable {
	sf::RectangleShape body;
public:
	Square(sf::Vector2f _pos, sf::Color color, float _size) : Base(typeid(this).raw_name(), _pos) {
		body.setPosition(this->object_position);
		body.setSize(sf::Vector2f{ _size, _size });
		body.setFillColor(color);

		this->globalBounds = body.getGlobalBounds();

	}

	void drawObject() {
		window->draw(body);
	}

	void updateObject() {
		this->globalBounds = body.getGlobalBounds();
	}

	sf::Vector2f getSize() {
		return body.getSize();
	}

};