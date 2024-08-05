export module Eventable;

import Globals;

export class Eventable {
	bool stopCheckingEvents;
public:
	Eventable() : stopCheckingEvents(false) {}
	~Eventable() {
		clearAllAssociations();
	}

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

	void clearAllAssociations() {
		_keyAssociation.clear();
		_buttonAssociation.clear();
		_rKeyAssociation.clear();
		_rButtonAssociation.clear();
	}

	void lockEvents() { stopCheckingEvents = true; }
	void unlockEvents() { stopCheckingEvents = false; }
	
	bool isLocked() { return stopCheckingEvents; }

};