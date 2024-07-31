export module Engine;

import Globals;
import OC;

export class Engine {

	static void drawAllObjects() {
		window->setActive(false);
		for (auto const& e : oc._objectDraws) {
			Functor f = e.second; f();
		}
	}

	static void renderingThread() {
		if (window) {
			window->setActive(true);
			isWindowOpen = true;

			while (isWindowOpen) {
				window->clear();
				
				drawAllObjects(); 

				window->display();
			} 
			window->close();
		}
	}

	static void checkAndExecuteCollisionsInAllObjects() {
		for (std::pair<uint64_t, Collidable*> e : oc._objectWithCollisions) {
			for (std::pair<uint64_t, Collidable*> otherObject : oc._objectWithCollisions) {
				if (e.first != otherObject.first) {
					if (e.second->isInCollisionWith(otherObject.second)) {
						if (e.second->putObjectColliding(otherObject.second)) {
							//std::cout << "#(" << e.first << " and " << otherObject.first << "): afterCollision processing...\n";
							e.second->putLastObjectColliding(otherObject.second);
							e.second->afterCollision();
						}
					}
					else {
						if (e.second->getLastObjectColliding() == otherObject.second)
							e.second->putObjectColliding(nullptr);
						//std::cout << e.first << " and " << otherObject.first << ": no collision processing...\n";
						//std::cout << std::boolalpha << e.second->putObjectColliding(nullptr) << std::endl;

					}
				}
				//else std::cout << "the same";
			}
		}
	}

	static void watchCollisionThread() {
		if (window) {

			sf::Int32 prevTime = globalClock.getElapsedTime().asMilliseconds();

			while (isWindowOpen) {
				sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
				if (elapsedTime - prevTime > (100 / 12)) {

					prevTime = elapsedTime;
					checkAndExecuteCollisionsInAllObjects();
				}
			}
		}
	}

	void moveAllObjects() {
		for (auto const& e : oc._objectMoves) {
			Functor f = e.second; f();
		}
	}

	void checkAndExecuteEventsInAllObjects() {
		while (window->pollEvent(*event)) {
			if (event->type == sf::Event::Closed) {
				isWindowOpen = false;
				break;
			}
			for (std::pair<uint64_t, Eventable*> e : oc._objectsWithEventsAssociatedWithFunctions) {
				//std::cout << e.second << " " << e.second->_keyAssociation.size() << std::endl;
				for (auto const& [key, func] : e.second->_keyAssociation)
					if (event->type == sf::Event::KeyPressed and event->key.code == key)
					{
						Functor f = func; f();
					}
				for (auto const& [key, func] : e.second->_rKeyAssociation)
					if (event->type == sf::Event::KeyReleased and event->key.code == key)
					{
						Functor f = func; f();
					}
				for (auto const& [button, func] : e.second->_buttonAssociation)
					if (event->type == sf::Event::MouseButtonPressed and event->mouseButton.button == button)
					{
						Functor f = func; f();
					}
				for (auto const& [button, func] : e.second->_rButtonAssociation)
					if (event->type == sf::Event::MouseButtonReleased and event->mouseButton.button == button)
					{
						Functor f = func; f();
					}
			}
		}
	}

	void deleteAllObjects() { // not all obviously
		window->setActive(false);
		for (auto const& [className, element] : oc._database) {
			for (auto const& [id, object] : element) {
				if (!object->isObjectAlive()) {
					object->garbage();
					oc.deleteObject(object->getID());
				}
			}
		}
	}

	void updateAllObjects() {
		for (auto const& e : oc._objectUpdates) {
			Functor f = e.second; f();
		}
	}

public:
	Engine() {
		std::cout << "<- Engine Loading... ->\n";
	}

	template <typename T>
	std::weak_ptr<T> addObject(std::shared_ptr<Base>&& r) {
		oc.insertObject(r);
		return std::weak_ptr<T>(std::dynamic_pointer_cast<T>(std::move(r)));
	}

	bool init(std::pair<int, int> _windowSize, std::string _windowName, bool _resizable, int _framerate) {
		window = std::make_unique<sf::RenderWindow>(
			sf::VideoMode(_windowSize.first, _windowSize.second),
			_windowName, _resizable ? (sf::Style::Default) : (sf::Style::Close));
		window->setFramerateLimit(_framerate);
		window->setVerticalSyncEnabled(true);
		window->setKeyRepeatEnabled(false);
		window->setPosition({ 0,0 });

		event = std::make_unique<sf::Event>();

		isWindowOpen = true;
		std::cout << "<- Engine Loaded ->\n";
		return isWindowOpen;
	}

	void run() {

		sf::Thread renderThread(&renderingThread);
		renderThread.launch();

		sf::Thread collisionThread(&watchCollisionThread);
		collisionThread.launch();

		sf::Int32 prevTime = globalClock.getElapsedTime().asMilliseconds();

		if (window) {
			window->setActive(false);
			isWindowOpen = true;

			while (window->isOpen()) {
				sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
				if (elapsedTime - prevTime > 100 / 12) {
					prevTime = elapsedTime;

					checkAndExecuteEventsInAllObjects();
					moveAllObjects();
					updateAllObjects();
					deleteAllObjects();
					
				}
			} 

		}
		else {
			std::cout << "!- Init the window -!\n";
		}
		renderThread.wait();
		collisionThread.wait();
	}

} inline engine;