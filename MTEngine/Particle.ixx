export module Particle;

import Globals;

import Base;
import Drawable;
import Moveable;
import Updateable;
import Physicsable;

export class Particle : public Base, public Drawable, public Moveable, public Updateable, public Physicsable {
	sf::CircleShape body;

	std::shared_ptr<Particle> prev;
	float maxDistance;

	float calcDistance() {
		return sqrt(
			pow(prev->getCurrentPosition().y - this->getCurrentPosition().y, 2) +
			pow(prev->getCurrentPosition().x - this->getCurrentPosition().x, 2)
			);
	}
public:
	Particle(std::shared_ptr<Particle> _prev, sf::Vector2f _pos, float _maxDistance, float _radius = 50.f)
		: Base(typeid(this).raw_name(), _pos), Physicsable(1.f), prev(_prev), maxDistance(_maxDistance)
	{
		body.setOrigin(sf::Vector2f{ _radius, _radius });
		body.setPosition(this->object_position);
		body.setRadius(_radius);
		body.setFillColor(sf::Color::White);

		this->addForce(sf::Vector2f{ 0.f, .01f });
	}

	void updateObject() {
		if (prev != nullptr) {
			float distance = calcDistance();

			float alpha = atanf(
				(prev->getCurrentPosition().y - this->getCurrentPosition().y) /
				(prev->getCurrentPosition().x - this->getCurrentPosition().x)
			);
			
			
			this->removeForceBySubscript(2);

			//std::cout << "==" << std::endl;
			//std::cout << "#F -> " << F << std::endl;
			//std::cout << this->getForcesSize() << std::endl;
			if (round(distance) == round(maxDistance)) {
				sf::Vector2f mg = this->sigmaF();
				float Ft = sqrt(mg.x * mg.x + mg.y * mg.y);

				sf::Vector2f newForce;
				newForce.y = sinf(alpha) * -Ft * alpha / abs(alpha);
				newForce.x = cosf(alpha) * -Ft * alpha / abs(alpha);
				//std::cout << alpha << std::endl;

				//std::cout << "NF -> " << newForce.x << " " << newForce.y << "\n\n";

				this->addForce(newForce);
				std::cout << "\nSF -> " << this->sigmaF().x << " " << this->sigmaF().y << std::endl;

				//std::cout << "SF -> " << this->sigmaF().x << " " << this->sigmaF().y << std::endl;
				//std::cout << "A: " << alpha << std::endl;
				//std::cout << this->getID() << ": " << distance << " == " << maxDistance << std::endl;
			}
			else if (round(distance) > round(maxDistance)) prev = nullptr;

			
			//std::cout << "SF -> " << this->sigmaF().x << " " << this->sigmaF().y << std::endl;

			sf::Vector2f sf = this->sigmaF();
			this->setAcceleration({ sf.x / this->getObjectMass(), sf.y / this->getObjectMass() });
			
			//std::cout << sf.x << " " << sf.y << std::endl;
			//std::cout << "X: " << sf.x << ", Y: " << sf.y << std::endl;
			

		}
	}

	void moveObject() {
		if (prev != nullptr) {
			body.move(this->getCurrentMoveDir());
			object_position = body.getPosition();
		}
	}

	void drawObject() {
		window->draw(body);
	}

};