export module Particle;

import Globals;

import Base;
import Moveable;
import Updateable;

export class Particle : public Base, public Moveable, public Updateable {
	std::shared_ptr<Particle> prev;
	float maxDistance;
public:
	Particle(std::shared_ptr<Particle> _prev, sf::Vector2f _pos, float _maxDistance)
		: Base(typeid(this).raw_name(), _pos), prev(_prev), maxDistance(_maxDistance)
	{}

	void updateObject() {
		if (prev != nullptr) {
			float drvX = this->object_position.x - prev->getCurrentPosition().x;
			float drvY = this->object_position.y - prev->getCurrentPosition().y;
			float distance = sqrt(
				pow(drvX, 2) + pow(drvY, 2)
			);
			float alpha = atanf(drvY / drvX);
			alpha *= 180; alpha /= 3.14159f; // conversion to degrees

			sf::Vector2f cmd = this->getCurrentMoveDir();
			if (distance >= maxDistance) {
				if (round(alpha) >= 90) this->setMoveDirection({ cmd.x, cmd.y + 0.1f });
				else {
					if (round(alpha) < 0) this->setMoveDirection({ cmd.x + 0.01f, cmd.y });
					else this->setMoveDirection({ cmd.x - 0.01f, cmd.y });
				}
			}
			else {
				if (round(alpha) >= 90) this->setMoveDirection({ cmd.x, 0.f });
			}
			
			
		}
	}

	void moveObject() {
		if (prev != nullptr) {

			this->object_position.x += this->getCurrentMoveDir().x;
			this->object_position.y += this->getCurrentMoveDir().y;
		}
	}

};