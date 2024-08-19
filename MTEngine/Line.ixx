export module Line;

import Globals;

import Base;
import Drawable;

export class Line : public Base, public Drawable {
	std::pair<sf::Vector2f, sf::Vector2f> points;
	sf::VertexArray line;
public:
	Line(std::pair<sf::Vector2f, sf::Vector2f> _points, sf::Color color = sf::Color::White) 
		: points(_points), Base(typeid(this).raw_name(), points.first) 
	{
		line = sf::VertexArray(sf::LinesStrip, 2);
		line[0].position = points.first; line[0].color = color;
		line[1].position = points.second; line[1].color = color;
	}

	void drawObject() {
		window->draw(line);
	}

	void garbage() {
		object_alive = false;
	}
};