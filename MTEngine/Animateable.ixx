export module Animateable;

import Globals;

export class Animateable {

	std::string __folderPath;
	std::map<std::string, std::string>::iterator __currentAnimation;

protected:
	std::map<std::string, std::string> _animationsNames;
	sf::Sprite _body;

public:
	Animateable(std::string newFolderPath) : __folderPath(newFolderPath)
	{
		std::ifstream file(__folderPath + "/" + "animation-info.txt");

		std::string linkedName, internalName;
		while (!file.eof()) {
			file >> internalName; file >> linkedName; file >> linkedName;
			_animationsNames.insert(std::make_pair(internalName, linkedName));
		}

		file.close();
	}

	virtual void animateObject() {

	}

	virtual void updateAnimation() {

	}

	std::map<std::string, std::string>::iterator getAnimationItByInternalName(std::string internalName) {
		try {

			_animationsNames.at(internalName);

			std::map<std::string, std::string>::iterator result = _animationsNames.begin();
			for (auto e : _animationsNames) {
				if (e.first == internalName) return result;
				result++;
			}

		}
		catch (const std::out_of_range) {
			//return std::map<std::string, std::string>::iterator();
			return _animationsNames.end();
		}
	}

	bool setAnimationWithIt(std::map<std::string, std::string>::iterator newAnimation) {
		__currentAnimation = newAnimation;
		return !(__currentAnimation == newAnimation);
	}

};