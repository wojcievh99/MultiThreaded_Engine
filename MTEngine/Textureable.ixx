export module Textureable;

import Globals;

export class Textureable {
	sf::Texture _tex;
	std::string folderPath;
protected:
	sf::Sprite _body;

public:
	Textureable(std::string _folderPath, std::string file, unsigned int scale) : folderPath(_folderPath) {
		_tex.loadFromFile(folderPath + "/" + file);
		_body.setScale(sf::Vector2f(scale, scale));
		_body.setTexture(_tex);
	}

	void changeTexture(std::string file) {
		_tex.loadFromFile(folderPath + "/" + file);
		_body.setTexture(_tex);
	}

};