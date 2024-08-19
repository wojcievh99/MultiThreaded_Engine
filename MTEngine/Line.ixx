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
	size_t amountOfParticles;
public:
	Line(std::pair<sf::Vector2f, sf::Vector2f> points, size_t _amountOfParticles)
		: Base(typeid(this).raw_name(), points.first), particles({}), amountOfParticles(_amountOfParticles)
	{

		lines = sf::VertexArray(sf::LinesStrip, amountOfParticles);

		for (size_t i = 0; i < amountOfParticles; i++) {
			particles.push_back(std::make_shared<Particle>(
				i > 0 ? particles[i - 1] : nullptr,
				sf::Vector2f{
					points.first.x + ((points.second.x - points.first.x) / (amountOfParticles - 1)) * i,
					points.first.y + ((points.second.y - points.first.y) / (amountOfParticles - 1)) * i
				},
				(sqrt(
					pow((points.second.x - points.first.x), 2) +
					pow((points.second.y - points.first.y), 2)
				) / (amountOfParticles - 1))
			));
			engine.addObject<Particle>(particles[i]);
			lines[i].position = particles[i]->getCurrentPosition();
		}

	}

	void drawObject() {
		window->draw(lines);
	}

	void updateObject() {
		for (size_t i = 0; i < amountOfParticles; i++) {
			lines[i].position = particles[i]->getCurrentPosition();
		}
	}

};