export module Animateable;

import Globals;

export class Animateable {

	std::vector<sf::IntRect> _formalLayoutContainer;
	std::vector<sf::IntRect> _onetimeLayoutContainer;

	size_t lastIteration;

	std::string folderPath;

	std::string currentFormalFile;
	std::string currentOneTimeFile;

	sf::Texture formal_object_tex;
	sf::Texture onetime_object_tex;

	bool oneTimeDone;
	bool stopAnimating;
	bool stopAnimatingAfterOT;

	sf::Int32 prevTime;
	sf::Int32 framerate;

protected:
	sf::Sprite body;

public:
	Animateable(std::string _folderPath, sf::Int32 _framerate = 10) 
		: folderPath(_folderPath), framerate(_framerate), lastIteration(0),
		currentFormalFile(""), currentOneTimeFile(""), 
		oneTimeDone(true), stopAnimating(false), stopAnimatingAfterOT(false)
	{}

	virtual void updateAnimation() = 0; // override to update so you don't have to inherit from updateable (smart move - saves time)

	bool setFormalTexFile(std::string _file, std::string info_file) {
		if (!stopAnimating) {
			try {
				formal_object_tex.loadFromFile(folderPath + "/" + _file + ".png");
			}
			catch (int error) { return false; }

			lastIteration = 0;
			_formalLayoutContainer.clear();
			
			std::ifstream __file;
			__file.open(folderPath + "/" + info_file + ".txt");

			std::string temp; std::vector<int> tempContainer;
			while (!__file.eof()) {
				std::getline(__file, temp, ',');

				for (int i = 4; i--;) {
					if (i != 0) std::getline(__file, temp, ',');
					else std::getline(__file, temp);

					tempContainer.push_back(std::stoi(temp));
				}

				_formalLayoutContainer.push_back(sf::IntRect(
					tempContainer[0], tempContainer[1],
					tempContainer[2], tempContainer[3]
				));
				tempContainer.clear();

			}

			__file.close();

			currentFormalFile = _file;
			body.setTexture(this->formal_object_tex);

			return true;
		}
		else return false;
	}

	bool setOneTimeTexFile(std::string _file, std::string info_file) {
		if (!stopAnimating) {
			try {
				onetime_object_tex.loadFromFile(folderPath + "/" + _file + ".png");
			}
			catch (int error) { return false; }

			oneTimeDone = false;
			lastIteration = 0;
			_onetimeLayoutContainer.clear();

			std::ifstream __file;
			__file.open(folderPath + "/" + info_file + ".txt");

			std::string temp; std::vector<int> tempContainer;
			while (!__file.eof()) {
				std::getline(__file, temp, ',');

				for (int i = 4; i--;) {
					if (i != 0) std::getline(__file, temp, ',');
					else std::getline(__file, temp);

					tempContainer.push_back(std::stoi(temp));
				}

				_onetimeLayoutContainer.push_back(sf::IntRect(
					tempContainer[0], tempContainer[1],
					tempContainer[2], tempContainer[3]
				));
				tempContainer.clear();

			}

			__file.close();

			currentOneTimeFile = _file;
			body.setTexture(this->onetime_object_tex);

			return true;
		}
		else return false;
	}
	
	void animateObject() {
		if (!stopAnimating) {
			sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
			if (elapsedTime - prevTime > 1000 / framerate) {
				prevTime = elapsedTime;

				if (oneTimeDone) {

					body.setTextureRect(_formalLayoutContainer[lastIteration]); 
					body.setOrigin({ _formalLayoutContainer[lastIteration].width / 2.f,  _formalLayoutContainer[lastIteration].height / 2.f });
					lastIteration++;
					if (lastIteration == _formalLayoutContainer.size()) lastIteration = 0;
					
				}
				else 
				{
					body.setTextureRect(_onetimeLayoutContainer[lastIteration]); 
					body.setOrigin({ _onetimeLayoutContainer[lastIteration].width / 2.f,  _onetimeLayoutContainer[lastIteration].height / 2.f });
					lastIteration++;
					if (lastIteration == _onetimeLayoutContainer.size()) {
						oneTimeDone = true;
						lastIteration = 0;
					}
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
	void setAnimationFramerate(sf::Int32 newFramerate = 10) {
		framerate = newFramerate;
	}

};