export module Line;

import Globals;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Collidable;
import Updateable;

import Particle;
import Engine;

export class Line : public Base, public Drawable, public Eventable, public Updateable {
	sf::VertexArray lines;
	std::vector<std::shared_ptr<Particle>> particles;
public:
	Line(std::pair<sf::Vector2f, sf::Vector2f> points) 
		: Base(typeid(this).raw_name(), points.first), particles({})
	{

		lines = sf::VertexArray(sf::LinesStrip, 20);

		for (size_t i = 0; i < 20; i++) {
			particles.push_back(std::make_shared<Particle>(
				i > 0 ? particles[i - 1] : nullptr,
				sf::Vector2f{
					points.first.x + ((points.second.x - points.first.x) / 19) * i,
					points.first.y + ((points.second.y - points.first.y) / 19) * i
				},
				(sqrt(
					pow((points.second.x - points.first.x), 2) +
					pow((points.second.y - points.first.y), 2)
				) / 20.f) 
			));
			engine.addObject<Particle>(particles[i]);
			lines[i].position = particles[i]->getCurrentPosition();
		}

	}

	void drawObject() {
		window->draw(lines);
	}

	void updateObject() {
		for (size_t i = 0; i < 20; i++) {
			lines[i].position = particles[i]->getCurrentPosition();
		}
	}

};