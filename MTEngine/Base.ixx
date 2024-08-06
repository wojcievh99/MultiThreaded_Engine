export module Base;

import Globals;

export class Base {
	std::string _object_className;
	std::uint64_t _object_id;
protected:
	sf::Vector2f object_position;
	bool object_alive;
public:

	Base(std::string _className, sf::Vector2f _position)
		: _object_className(_className), object_position(_position), object_alive(true)
	{
		this->_object_id = ++globalID;
		std::cout << "[ID: " << _object_id << ", className: " << _object_className << "](+) \n";
	}
	~Base() {
		std::cout << "[ID: " << _object_id << ", className: " << _object_className << "](-) \n";
	}

	std::uint64_t getID() {
		return _object_id;
	}

	std::string getClassName() {
		return _object_className;
	}

	bool isObjectAlive() {
		return object_alive;
	}

	sf::Vector2f getPosition() {
		return object_position;
	}

	virtual void garbage() {
		object_alive = false;
		std::cout << "[ID: " << _object_id << "](-) \n";
	}

	virtual void resetToRender() {}
	virtual sf::Vector2f getDimensions() { return { 0.f, 0.f }; }

};
