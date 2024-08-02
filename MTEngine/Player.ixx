export module Player;

import Globals;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Collidable;
import Updateable;
import Animateable;

export class Player : public Base, public Drawable, public Animateable, public Moveable, public Eventable, public Updateable {
	sf::Sprite body;
	sf::Int32 prevTime;
	sf::Vector2f lastMoveDir;
public:
	Player(sf::Vector2f _pos) : 
		Base(typeid(this).raw_name(), _pos), Animateable("textures/Player"), Moveable(),
		prevTime(globalClock.getElapsedTime().asMilliseconds()), lastMoveDir({0.f, 0.f})
	{
		body.setPosition(this->object_position);
		body.setScale({ 5.f, 5.f });

		this->setTexFile("Idle", {7, 1});
		body.setTexture(this->object_tex);
		body.setTextureRect(this->getTexOffset({ 0, 0 }));

		body.setOrigin({ this->_fileImageOffset.x / 2.f, this->_fileImageOffset.y / 2.f });


		this->addKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				sf::Vector2f cmd = this->getCurrentMoveDir();
				this->setMoveDirection({ cmd.x + 1.f, cmd.y });
			}
		));
		this->addReleaseKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				sf::Vector2f cmd = this->getCurrentMoveDir();
				this->setMoveDirection({ cmd.x - 1.f, cmd.y });
			}
		));
		this->addKeyAssociation(sf::Keyboard::A, Functor(
			[this]() {
				sf::Vector2f cmd = this->getCurrentMoveDir();
				this->setMoveDirection({ cmd.x - 1.f , cmd.y });
			}
		));
		this->addReleaseKeyAssociation(sf::Keyboard::A, Functor(
			[this]() {
				sf::Vector2f cmd = this->getCurrentMoveDir();
				this->setMoveDirection({ cmd.x + 1.f, cmd.y });
			}
		));
		this->addKeyAssociation(sf::Keyboard::Q, Functor(
			[this]() {
				this->setTexFile("Dead", { 5, 1 });
				this->setMoveDirection({ 0.f, 0.f });
			}
		));


	}

	void drawObject() {
		window->draw(body);
	}

	void moveObject() {
		body.move(this->getCurrentMoveDir());
	}

	void updateObject() {
		if (lastMoveDir != this->getCurrentMoveDir()) {
			lastMoveDir = this->getCurrentMoveDir();
			if (this->deathAnimation) {
				this->setMoveDirection({ 0.f,0.f }); // safety
			}
			else if (lastMoveDir.x == 0.f) {
				this->setTexFile("Idle", { 7, 1 });
			}
			else if (lastMoveDir.x > 0.f) {
				this->setTexFile("Walk", { 7, 1 });
				body.setScale({ 5.f, 5.f });
			}
			else if (lastMoveDir.x < 0.f) {
				this->setTexFile("Walk", { 7, 1 });
				body.setScale({ -5.f, 5.f });
			}
		}
	}

	void animateObject() {
		sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
		if (elapsedTime - prevTime > 100) {
			prevTime = elapsedTime;

			if (this->deathAnimation and this->lastFrame > this->_fileGridLayout.x - 1) {
				this->garbage();
				return;
			}
			if (this->lastFrame > this->_fileGridLayout.x - 1) this->lastFrame = 0;
			body.setTextureRect(this->getTexOffset({ this->_fileImageOffset.x * this->lastFrame++, 0 }));

		}
	}

};