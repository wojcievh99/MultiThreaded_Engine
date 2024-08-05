export module Player;

import Globals;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Collidable;
import Updateable;
import Animateable;

export class Player : public Base, public Drawable, public Animateable, public Moveable, public Eventable, public Updateable, public Collidable {
	sf::Vector2f prevMoveDir;
	sf::Vector2f scale;

	bool jumping;
	bool showBounds;
public:
	Player(sf::Vector2f _pos, sf::Vector2f _scale) :
		Base(typeid(this).raw_name(), _pos), Animateable("textures/Player"),
		Moveable(), prevMoveDir(this->getCurrentMoveDir()), scale({ abs(_scale.x), abs(_scale.y) }),
		jumping(false), showBounds(false)
	{
		body.setPosition(this->object_position);
		body.setScale(scale);

		this->globalBounds = body.getGlobalBounds();

		this->setFormalTexFile("Idle", { 7, 1 });

		this->setMoveDirection({ 0.f, 0.1f });

		this->addKeyAssociation(sf::Keyboard::Q, Functor(
			[this]() {
				this->setMoveDirection({ 0.f, 0.f });
				this->setOneTimeTexFile("Dead", { 5, 1 });
				this->stopAnimationAfterOneTimeIsDone();
				this->lockEvents();
			}
		));
		this->addKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				sf::Vector2f cmd = this->getCurrentMoveDir();
				this->setMoveDirection({ cmd.x + 1, cmd.y });
			}
		));
		this->addReleaseKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				sf::Vector2f cmd = this->getCurrentMoveDir();
				if (cmd.x > 0.f) {
					if (std::abs(cmd.x) == 3.f) this->setMoveDirection({ cmd.x - 3, cmd.y });
					else this->setMoveDirection({ cmd.x - 1, cmd.y });
				}
				else this->setMoveDirection({ 0.f, cmd.y });
			}
		));
		this->addKeyAssociation(sf::Keyboard::A, Functor(
			[this]() {
				sf::Vector2f cmd = this->getCurrentMoveDir();
				this->setMoveDirection({ cmd.x - 1.f, cmd.y });
			}
		));
		this->addReleaseKeyAssociation(sf::Keyboard::A, Functor(
			[this]() {
				sf::Vector2f cmd = this->getCurrentMoveDir();
				if (cmd.x < 0.f) {
					if (std::abs(cmd.x) == 3.f) this->setMoveDirection({ cmd.x + 3, cmd.y });
					else this->setMoveDirection({ cmd.x + 1, cmd.y });
				} 
				else this->setMoveDirection({ 0.f, cmd.y });
			}
		));
		this->addKeyAssociation(sf::Keyboard::LShift, Functor(
			[this]() {
				sf::Vector2f cmd = this->getCurrentMoveDir();
				if (std::abs(cmd.x) == 1.f) this->setMoveDirection({ cmd.x * 3.f, cmd.y });
			}
		));
		this->addReleaseKeyAssociation(sf::Keyboard::LShift, Functor(
			[this]() {
				sf::Vector2f cmd = this->getCurrentMoveDir();
				if (std::abs(cmd.x) == 3.f) {
					this->setMoveDirection({ cmd.x / 3.f, cmd.y });
				}
			}
		));
		this->addKeyAssociation(sf::Keyboard::Space, Functor(
			[this]() {
				if (!jumping) {
					sf::Vector2f cmd = this->getCurrentMoveDir();
					this->setMoveDirection({ cmd.x, -8.f });
				}
			}
		));

		this->addKeyAssociation(sf::Keyboard::LControl, Functor(
			[this]() {
				this->showBounds = !this->showBounds;
			}
		));

	}

	void drawObject() {
		window->draw(body);
		
		if (showBounds) {
			sf::RectangleShape gb;
			gb.setPosition(this->getGlobalBounds().getPosition());
			gb.setSize(this->getGlobalBounds().getSize());
			gb.setFillColor(sf::Color(250, 0, 0, 150));
			window->draw(gb);
		}
	}

	void moveObject() {
		body.move(this->getCurrentMoveDir());
	}

	void updateAnimation() {
		if (prevMoveDir != this->getCurrentMoveDir()) {
			prevMoveDir = this->getCurrentMoveDir();
			///std::cout << prevMoveDir.x << std::endl;
			if (!jumping) {
				if (std::abs(prevMoveDir.y) > 0.f) {
					this->setFormalTexFile("Jump2", { 5, 1 });
					jumping = true;
				}
				else if (prevMoveDir.x == 0.f) {
					this->setFormalTexFile("Idle", { 7, 1 });
				}
				else if (prevMoveDir.x == 1.f) {
					this->setFormalTexFile("Walk", { 7, 1 });
					this->body.setScale(scale);
				}
				else if (prevMoveDir.x == -1.f) {
					this->setFormalTexFile("Walk", { 7, 1 });
					this->body.setScale({ -scale.x, scale.y });
				}
				else if (prevMoveDir.x == 3.f) {
					this->setFormalTexFile("Run", { 8, 1 });
					this->body.setScale(scale);
				}
				else if (prevMoveDir.x == -3.f) {
					this->setFormalTexFile("Run", { 8, 1 });
					this->body.setScale({ -scale.x, scale.y });
				}
			}
		}

	}

	void updateObject() {
		this->object_position = body.getPosition();

		this->globalBounds =
		{
			{body.getGlobalBounds().left + 60.f, body.getGlobalBounds().top + 50.f},
			{body.getGlobalBounds().width - 120.f, body.getGlobalBounds().height - 50.f}
		};

		if (std::abs(this->getCurrentMoveDir().y) > 0.f or this->_objectColliding == nullptr) 
		{
			this->setMoveDirection({ this->getCurrentMoveDir().x, this->getCurrentMoveDir().y + .1f });
		}
	}

	void afterCollision() {
		switch (this->getVerticalDirectionOfCollidingObject())
		{
		case DOWN:
			this->setMoveDirection({ prevMoveDir.x, 0.f });
			this->setFormalTexFile("Idle", { 7, 1 });
			this->jumping = false;
			break;
		case UP:
			this->setMoveDirection({ prevMoveDir.x, -prevMoveDir.y / 2.f });
			break;
		default:
			break;
		}
		
	
	}

};