export module Player;

import Globals;

import Base;
import Drawable;
import Moveable;
import Eventable;
import Collidable;
import Updateable;

export class Player : public Base, public Drawable, public Moveable, public Eventable, public Updateable {
	sf::Texture texIdle, texWalk;
	sf::RectangleShape body;

	unsigned int lastWalkImg;
	float imageOffset;

	sf::Int32 prevTime;

public:
	Player(sf::Vector2f _pos) :
		Base(typeid(this).raw_name(), _pos), Moveable(sf::Vector2f{ 0.f, 0.f }),
		imageOffset(96.f), lastWalkImg(0), prevTime(globalClock.getElapsedTime().asMilliseconds())
	{

		body.setPosition(this->object_position);
		body.setSize({96.f, 96.f});
		body.setScale(sf::Vector2f{ 3.f, 3.f });

		texIdle.loadFromFile("textures/Ninja_Monk/Idle.png");
		texWalk.loadFromFile("textures/Ninja_Monk/Walk.png");

		body.setTexture(&texIdle);

		body.setTextureRect(sf::IntRect(imageOffset * 0, imageOffset * 0, imageOffset, imageOffset));

		

		this->addKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f{ 1.f, this->getCurrentMoveDir().y});
			}
		));

		this->addReleaseKeyAssociation(sf::Keyboard::D, Functor(
			[this]() {
				this->setMoveDirection(sf::Vector2f{ 0.f, this->getCurrentMoveDir().y });
			}
		));

	}

	void drawObject() {
		window->draw(body);
	}

	void moveObject() {
		if (getCurrentMoveDir() != sf::Vector2f{ 0.f, 0.f }) {
			body.move(this->getCurrentMoveDir());
			body.setTexture(&texWalk);
			sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
			if (elapsedTime - prevTime > 120) {
				prevTime = elapsedTime;
				if (lastWalkImg > 6) lastWalkImg = 0;
				body.setTextureRect(sf::IntRect(imageOffset * lastWalkImg++, imageOffset * 0, imageOffset, imageOffset));
			}
		}
		else body.setTexture(&texIdle);
	}

	void updateObject() {

	}


};