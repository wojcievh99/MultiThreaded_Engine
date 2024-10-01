export module Eventable;

import Globals;

export class Eventable {
	bool __stopCheckingEvents;
public:
	Eventable() : __stopCheckingEvents(false) {}
	~Eventable() { clearAllAssociations(); }

	std::unordered_map<sf::Keyboard::Key, Functor> _keyAssociation;
	std::unordered_map<sf::Mouse::Button, Functor> _buttonAssociation;

	std::unordered_map<sf::Keyboard::Key, Functor> _rKeyAssociation;
	std::unordered_map<sf::Mouse::Button, Functor> _rButtonAssociation;

	std::set<sf::Keyboard::Key> _lockedIndKeys;
	std::set<sf::Mouse::Button> _lockedIndButtons;

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

	void lockEvents() { __stopCheckingEvents = true; }
	void unlockEvents() { __stopCheckingEvents = false; }

	void lockIndEvent(sf::Keyboard::Key k) { _lockedIndKeys.insert(k); }
	void lockIndEvent(sf::Mouse::Button b) { _lockedIndButtons.insert(b); }

	void unlockIndEvent(sf::Keyboard::Key k) { _lockedIndKeys.erase(k); }
	void unlockIndEvent(sf::Mouse::Button b) { _lockedIndButtons.erase(b); }
	
	bool isLocked() { return __stopCheckingEvents; }

};