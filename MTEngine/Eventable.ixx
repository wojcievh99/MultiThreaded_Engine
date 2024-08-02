export module Eventable;

import Globals;

export class Eventable {
public:
	std::unordered_map<sf::Keyboard::Key, Functor> _keyAssociation;
	std::unordered_map<sf::Mouse::Button, Functor> _buttonAssociation;

	std::unordered_map<sf::Keyboard::Key, Functor> _rKeyAssociation;
	std::unordered_map<sf::Mouse::Button, Functor> _rButtonAssociation;

	// press
	void addKeyAssociation(sf::Keyboard::Key key, Functor func) {
		_keyAssociation[key] = func;
	}
	void addButtonAssociation(sf::Mouse::Button button, Functor func) {
		_buttonAssociation[button] = func;
	}

	// release
	void addReleaseKeyAssociation(sf::Keyboard::Key key, Functor func) {
		_rKeyAssociation[key] = func;
	}
	void addReleaseButtonAssociation(sf::Mouse::Button button, Functor func) {
		_rButtonAssociation[button] = func;
	}
	
};