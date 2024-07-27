export module Eventable;

import Globals;

export class Eventable {
public:
	std::unordered_map<sf::Keyboard::Key, Functor> _keyAssociation;
	std::unordered_map<sf::Mouse::Button, Functor> _buttonAssociation;

	void addKeyAssociation(sf::Keyboard::Key key, Functor func) {
		_keyAssociation[key] = func;
	}
	void addButtonAssociation(sf::Mouse::Button button, Functor func) {
		_buttonAssociation[button] = func;
	}
	
};