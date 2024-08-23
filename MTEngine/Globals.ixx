export module Globals;

export import std;
export import "SFML/Graphics.hpp";

export import Functor;
export import Concepts;

export sf::Clock globalClock;
export sf::Mutex deleteMutex;
//export sf::Mutex mutex;

export bool isWindowOpen = false;

export std::unique_ptr<sf::RenderWindow> window;
export std::unique_ptr<sf::Event> event;

export sf::View view; 
export std::pair<std::string, uint64_t> viewObjectData;
export bool viewLock = false;

export uint64_t globalID = 0;