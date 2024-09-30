export module Base;

import Globals;

export class Base {
	std::string __object_className;
	std::uint64_t __object_id;
protected:
	sf::Vector2f _object_position;
	bool _object_alive;
public:

	Base(std::string _className, sf::Vector2f _position) 
		: __object_className(_className), _object_position(_position), _object_alive(true)
	{
		this->__object_id = ++globalID;
		//std::cout << "[ID: " << __object_id << ", className: " << __object_className << "](+) \n";
	}
	~Base() {
		std::cout << "[ID: " << __object_id << ", className: " << __object_className << "](-) \n";
	}

	std::uint64_t getID() {
		return __object_id;
	}

	std::string getClassName() {
		return __object_className;
	}

	sf::Vector2f getPosition() {
		return _object_position;
	}

	bool isObjectAlive() {
		return _object_alive;
	}

	virtual void garbage() {
		//_object_alive = false;
		std::cout << "[ID: " << __object_id << "](-) \n";
	}

};
