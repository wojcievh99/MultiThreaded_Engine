export module Engine;

import Globals;
import OC;

export class Engine {

	static void drawAllObjects() {
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

				deleteMutex.lock();
				drawAllObjects(); 
				deleteMutex.unlock();

				window->display();
			} 
			window->close();
		}
	}

	static void checkAndExecuteCollisionsInAllObjects() {
		for (std::pair<uint64_t, std::shared_ptr<Collidable>> e : oc._objectWithCollisions) {
			for (std::pair<uint64_t, std::shared_ptr<Collidable>> otherObject : oc._objectWithCollisions) {
				if (e.first != otherObject.first and e.second->isCollisionPossible(otherObject.second)) {
					if (e.second->isInCollisionWith(otherObject.second)) {
						if (e.second->putObjectColliding(otherObject.second)) {

							e.second->putLastObjectColliding(otherObject.second);
							e.second->afterCollision();

						}
					}
					else {
						if (e.second->getLastObjectColliding().lock() == otherObject.second)
							e.second->putObjectColliding(nullptr);
					}
				}
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

	void checkAndExecuteEventsInAllObjects() {
		while (window->pollEvent(*event)) {
			if (event->type == sf::Event::Closed) {

				isWindowOpen = false;
				break;

			}
			for (std::pair<uint64_t, std::shared_ptr<Eventable>> e : oc._objectsWithEventsAssociatedWithFunctions) {
				if (!e.second->isLocked()) {

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
	}

	void moveAllObjects() {
		for (auto const& e : oc._objectMoves) {
			Functor f = e.second; f();
		}
	}

	void updateAllObjects() {
		for (auto const& e : oc._objectUpdates) {
			Functor f = e.second; f();
		}
	}

	void animateAllObjects() {
		for (auto const& e : oc._objectAnimations) {
			Functor f = e.second.first; f();
			f = e.second.second; f();
		}
	}

	void deleteAllObjects() { 
		for (auto const& [className, element] : oc._database) {
			for (auto const& [id, object] : element) {
				if (!object->isObjectAlive()) {

					deleteMutex.lock();
					oc.deleteObject(object->getID());
					deleteMutex.unlock();

				}
			}
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

		window = std::make_unique<sf::RenderWindow>
			(
				sf::VideoMode(_windowSize.first, _windowSize.second),
				_windowName, _resizable ? (sf::Style::Default) : (sf::Style::Close)
			);
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
					animateAllObjects();
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