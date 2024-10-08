export module Animateable;

import Globals;

export class Animateable {

	std::string __folderPath;
	std::map<std::string, std::pair<std::string, unsigned int>>::iterator __currentAnimation;
	sf::Vector2u __frameDimensions; unsigned int offset;

	sf::Texture __objectTexture;

	unsigned int __framerate; unsigned int __animationIndex;
	sf::Int32 __prevTime = globalClock.getElapsedTime().asMilliseconds();

	void loadNewAnimation() {
		__objectTexture.loadFromFile(__folderPath + "/" + __currentAnimation->second.first);
		_body.setTexture(__objectTexture); _body.setOrigin(sf::Vector2f(__frameDimensions.x / 2.f, __frameDimensions.y / 2.f));
		_body.setTextureRect(sf::IntRect(this->__frameDimensions.x, 0, __frameDimensions.x, __frameDimensions.y));
	}

protected:
	std::map<std::string, std::pair<std::string, unsigned int>> _animationsNames; // <internalName, <linkedName, frames>>
	sf::Sprite _body;

public:
	Animateable(std::string newFolderPath, unsigned int framerate = 10)
		: __folderPath(newFolderPath), __framerate(framerate), __animationIndex(0)
	{

		std::ifstream file;
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			file.open(__folderPath + "/" + "animation-info.txt"); 
			if (!file.is_open()) 
				throw std::ifstream::failure(red + " - File Not Specified [Class Animatable] - " + reset);
		}
		catch (std::exception& err) {
			std::cout << red << " - Animatable Class Failed - \n" << reset;
		}

		std::string internalName, linkedName; unsigned int frameCount;

		try {
			file >> __frameDimensions.x >> __frameDimensions.y; // dimensions: __frameDimensions [x, y]
			file >> offset;

			while (!file.eof()) {
				file >> internalName; file >> linkedName; file >> linkedName; file >> frameCount;
				_animationsNames.insert(std::make_pair(internalName, std::make_pair(linkedName, frameCount)));
			}

			__currentAnimation = _animationsNames.end();
		}
		catch (std::exception &err) {
			std::cout << red << " - Animatable Class Failed - \n" << reset;
		}

		file.close();
	}

	void animateObject() {
		if (__currentAnimation == _animationsNames.end()) {
			__currentAnimation = _animationsNames.begin();
			loadNewAnimation();
		}

		sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
		if (elapsedTime - __prevTime > (1000 / __framerate)) {

			__prevTime = elapsedTime;

			_body.setTextureRect(
				sf::IntRect(
					this->__frameDimensions.x * this->__animationIndex + this->offset * this->__animationIndex++ , 0,
					__frameDimensions.x, __frameDimensions.y
				)
			);

			if (__animationIndex >= this->__currentAnimation->second.second)
				__animationIndex = 0;

		}
	}

	virtual void updateAnimation() {}

	std::map<std::string, std::pair<std::string, unsigned int>>::iterator getAnimationItByInternalName(std::string internalName) {
		try {

			_animationsNames.at(internalName);

			std::map<std::string, std::pair<std::string, unsigned int>>::iterator result = _animationsNames.begin();
			for (auto e : _animationsNames) {
				if (e.first == internalName) return result;
				result++;
			}

		}
		catch (const std::out_of_range) {
			return _animationsNames.end();
		}
	}

	bool setAnimationWithIt(std::map<std::string, std::pair<std::string, unsigned int>>::iterator newAnimation) {
		if (__currentAnimation == newAnimation) return false;
		__currentAnimation = newAnimation; loadNewAnimation(); return true;
	}

};