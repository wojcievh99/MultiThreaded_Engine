export module Line;

import Globals;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Collidable;
import Updateable;

export class Line : public Base, public Drawable, public Moveable, public Eventable, public Updateable {
	sf::VertexArray lines;

	size_t lastMovedPoint;
	sf::Int32 prevTime;

public:
	Line(std::pair<sf::Vector2f, sf::Vector2f> points) 
		: Base(typeid(this).raw_name(), points.first), lastMovedPoint(1), 
		prevTime(globalClock.getElapsedTime().asMilliseconds())
	{

		lines = sf::VertexArray(sf::LinesStrip, 100);

		for (size_t i = 0; i < 100; i++) {
			lines[i].position = sf::Vector2f{
				points.first.x + ((points.second.x - points.first.x) / 100) * i,
				points.first.y + ((points.second.y - points.first.y) / 100) * i
			};
		}

	}

	void drawObject() {
		window->draw(lines);
	}

	void updateObject() {
		float drv = (lines[0].position.x - lines[99].position.x);
		if (drv != 0.f) {
			sf::Vector2f cmd = this->getCurrentMoveDir();
			this->setMoveDirection({ cmd.x + drv / 1000.f, cmd.y});
		}
		else {
			this->setMoveDirection({ 0.f, 0.f });
		}
	}

	// this is stupid as fuck. make objects to be the points of the line 
	// and make them update themselfs with their own fucking phisics...
	// possibly the shittiest code i have ever written.
	void moveObject() {
		
		/*sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
		if (elapsedTime - prevTime > 10) {*/

			if (this->getCurrentMoveDir() != sf::Vector2f{ 0.f, 0.f }) {
				//prevTime = elapsedTime;
				lines[lastMovedPoint].position.x += this->getCurrentMoveDir().x;
				lines[lastMovedPoint].position.y += this->getCurrentMoveDir().y;
				if (lastMovedPoint == 99) {
					this->setMoveDirection(sf::Vector2f{ 0.f, 0.f });
					lastMovedPoint = 1;
				}
				else {
					lastMovedPoint++;
				}
			//}

		}
			
	}

};