export module Animateable;

import Globals;

export class Animateable {

	sf::Vector2u _formalFileImageOffset;
	sf::Vector2u _formalFileGridLayout;

	sf::Vector2u _onetimeFileImageOffset;
	sf::Vector2u _onetimeFileGridLayout;

	std::string folderPath;

	std::string currentFormalFile;
	std::string currentOneTimeFile;

	sf::Texture formal_object_tex;
	sf::Texture onetime_object_tex;

	unsigned int lastFrame;
	bool oneTimeDone;
	bool stopAnimating;
	bool stopAnimatingAfterOT;

	sf::Int32 prevTime;
	sf::Int32 framerate;

protected:
	sf::Sprite body;

public:
	Animateable(std::string _folderPath, sf::Int32 _framerate = 10) : folderPath(_folderPath), framerate(_framerate),
		_formalFileGridLayout({ 0, 0 }), _formalFileImageOffset({ 0, 0 }),
		_onetimeFileGridLayout({ 0, 0 }), _onetimeFileImageOffset({ 0, 0 }),
		lastFrame(0), currentFormalFile(""), currentOneTimeFile(""),
		oneTimeDone(true), stopAnimating(false), stopAnimatingAfterOT(false) 
	{}

	virtual void updateAnimation() = 0; // override to update so you don't have to inherit from updateable (smart move - saves time)

	bool setFormalTexFile(std::string _file, sf::Vector2u __fileGridLayout) {
		if (!stopAnimating) {
			try {
				formal_object_tex.loadFromFile(folderPath + "/" + _file + ".png");
			}
			catch (int error) { return false; }

			lastFrame = 0;
			_formalFileGridLayout = __fileGridLayout;

			_formalFileImageOffset = formal_object_tex.getSize();
			_formalFileImageOffset.x /= _formalFileGridLayout.x;
			_formalFileImageOffset.y /= _formalFileGridLayout.y;

			currentFormalFile = _file;
			body.setTexture(this->formal_object_tex);

			body.setOrigin({ this->_formalFileImageOffset.x / 2.f, this->_formalFileImageOffset.y / 2.f });

			return true;
		}
		else return false;
	}

	bool setOneTimeTexFile(std::string _file, sf::Vector2u __fileGridLayout) {
		if (!stopAnimating) {
			try {
				onetime_object_tex.loadFromFile(folderPath + "/" + _file + ".png");
			}
			catch (int error) { return false; }

			oneTimeDone = false;
			lastFrame = 0;
			_onetimeFileGridLayout = __fileGridLayout;

			_onetimeFileImageOffset = onetime_object_tex.getSize();
			_onetimeFileImageOffset.x /= _onetimeFileGridLayout.x;
			_onetimeFileImageOffset.y /= _onetimeFileGridLayout.y;

			currentOneTimeFile = _file;
			body.setTexture(this->onetime_object_tex);

			body.setOrigin({ this->_onetimeFileImageOffset.x / 2.f, this->_onetimeFileImageOffset.y / 2.f });

			return true;
		}
		else return false;
	}
	
	void animateObject() {
		if (!stopAnimating) {
			sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
			if (elapsedTime - prevTime > 1000 / framerate) {
				prevTime = elapsedTime;

				if (!oneTimeDone) {
					body.setTextureRect(sf::IntRect(this->_onetimeFileImageOffset.x * this->lastFrame++, 0, _onetimeFileImageOffset.x, _onetimeFileImageOffset.y));
					if (this->lastFrame > this->_onetimeFileGridLayout.x - 1) {
						if (stopAnimatingAfterOT) stopAnimation();
						else {
							this->lastFrame = 0;
							oneTimeDone = true;
							body.setTexture(this->formal_object_tex);
						}
					}
				}
				else {
					body.setTextureRect(sf::IntRect(this->_formalFileImageOffset.x * this->lastFrame++, 0, _formalFileImageOffset.x, _formalFileImageOffset.y));
					if (this->lastFrame > this->_formalFileGridLayout.x - 1) this->lastFrame = 0;
				}
			}
		}
	}

	void stopAnimation() {
		stopAnimating = true;
	}
	void stopAnimationAfterOneTimeIsDone() {
		stopAnimatingAfterOT = true;
	}

};