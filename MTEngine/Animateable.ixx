export module Animateable;

import Globals;

export class Animateable {
protected:
	sf::Vector2u _fileImageOffset;
	sf::Vector2u _fileGridLayout;

	std::string folderPath;
	sf::Texture object_tex;

	unsigned int lastFrame;
	bool deathAnimation;
public:
	Animateable(std::string _folderPath) : folderPath(_folderPath), deathAnimation(false),
		_fileGridLayout({ 0, 0 }), _fileImageOffset({ 0, 0 }), lastFrame(0) {}

	virtual void animateObject() = 0;

	bool setTexFile(std::string _file, sf::Vector2u __fileGridLayout) {
		try {
			object_tex.loadFromFile(folderPath + "/" + _file + ".png");
		}
		catch (int error) { return false; }
		
		if (_file == "Dead") deathAnimation = true;

		lastFrame = 0;
		_fileGridLayout = __fileGridLayout;

		_fileImageOffset = object_tex.getSize();
		_fileImageOffset.x /= _fileGridLayout.x;
		_fileImageOffset.y /= _fileGridLayout.y;

		return true;
	}

	sf::IntRect getTexOffset(sf::Vector2u start) {
		return sf::IntRect(start.x, start.y, _fileImageOffset.x, _fileImageOffset.y);
	}

};