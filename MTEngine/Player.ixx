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
public:
	Player(sf::Vector2f _pos, sf::Vector2f _scale) :
		Base(typeid(this).raw_name(), _pos), Animateable("textures/Player"),
		Moveable(), prevMoveDir(this->getCurrentMoveDir()), scale({ abs(_scale.x), abs(_scale.y) }),
		jumping(false)
	{
		body.setPosition(this->object_position);
		body.setScale(scale);

		this->globalBounds = body.getGlobalBounds();

		this->setFormalTexFile("Idle", { 7, 1 });

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
				if (std::abs(cmd.x) == 3.f) this->setMoveDirection({ cmd.x - 3, cmd.y });
				else this->setMoveDirection({ cmd.x - 1, cmd.y });
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
				if (std::abs(cmd.x) == 3.f) this->setMoveDirection({ cmd.x + 3, cmd.y });
				else this->setMoveDirection({ cmd.x + 1, cmd.y });
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
				sf::Vector2f cmd = this->getCurrentMoveDir();
				this->setMoveDirection({ cmd.x, -8.f });
			}
		));

	}

	void drawObject() {
		window->draw(body);
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
		this->globalBounds = body.getGlobalBounds();
		if ((this->getGlobalBounds().getPosition().y + this->getGlobalBounds().getSize().y) < 1000.f) 
			this->setMoveDirection({ this->getCurrentMoveDir().x, this->getCurrentMoveDir().y + .1f });
	}

	void afterCollision() {
		this->setMoveDirection({ prevMoveDir.x, 0.f });
		this->jumping = false;
	}

};