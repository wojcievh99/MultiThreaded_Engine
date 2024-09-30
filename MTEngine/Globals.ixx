export module Globals;

export import std;
export import "SFML/Graphics.hpp";

export import Functor;
export import Concepts;

export sf::Clock globalClock;
export std::mutex deleteMutex;

export unsigned int __framerate;
export bool isWindowOpen = false;

export std::unique_ptr<sf::RenderWindow> window;
export std::unique_ptr<sf::Event> event;

export sf::View view;
export std::pair<std::string, uint64_t> viewObjectData;
export bool viewLock = false;

export uint64_t globalID = 0;

export const std::string red("\033[31m");
export const std::string reset("\033[0m");