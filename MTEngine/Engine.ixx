export module Engine;

import Globals;
import OC;

export class Engine {

	static void checkAndExecuteCollisionsInAllObjects() {
		for (std::pair<uint64_t, std::weak_ptr<Collidable>> e : oc._objectWithCollisions) {
			for (std::pair<uint64_t, std::weak_ptr<Collidable>> otherObject : oc._objectWithCollisions) {
				if (e.first != otherObject.first) {
					if (e.second.lock()->isInCollisionWith(otherObject.second)) {
						if (e.second.lock()->putObjectColliding(otherObject.second.lock())) {

							e.second.lock()->afterCollision();

						}
					}
					else if (e.second.lock()->checkCollisionList(otherObject.second.lock()))
						e.second.lock()->eraseObjectColliding(otherObject.second.lock());
				}
			}
		}
	}

	static void watchCollisionThread() {
		if (window) {

			sf::Int32 prevTime = globalClock.getElapsedTime().asMilliseconds();

			while (isWindowOpen) {
				sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
				if (elapsedTime - prevTime > (1000 / (__framerate * 2))) {

					prevTime = elapsedTime;

					deleteMutex.lock();
					checkAndExecuteCollisionsInAllObjects();
					deleteMutex.unlock();


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
			for (std::pair<uint64_t, std::weak_ptr<Eventable>> e : oc._objectsWithEventsAssociatedWithFunctions) {
				if (!e.second.lock()->isLocked()) {

					for (auto const& [key, func] : e.second.lock()->_keyAssociation)
						if (!e.second.lock()->_lockedIndKeys.contains(key) 
							and event->type == sf::Event::KeyPressed and event->key.code == key)
						{
							Functor f = func; f();
						}
					for (auto const& [key, func] : e.second.lock()->_rKeyAssociation)
						if (!e.second.lock()->_lockedIndKeys.contains(key) 
							and event->type == sf::Event::KeyReleased and event->key.code == key)
						{
							if (!e.second.lock()->_lockedIndKeyRelease.contains(key)) {
								Functor f = func; f();
							}
							else e.second.lock()->_lockedIndKeyRelease.erase(key);
						}
					for (auto const& [button, func] : e.second.lock()->_buttonAssociation)
						if (!e.second.lock()->_lockedIndButtons.contains(button) 
							and event->type == sf::Event::MouseButtonPressed and event->mouseButton.button == button)
						{
							Functor f = func; f();
						}
					for (auto const& [button, func] : e.second.lock()->_rButtonAssociation)
						if (!e.second.lock()->_lockedIndButtons.contains(button)
							and event->type == sf::Event::MouseButtonReleased and event->mouseButton.button == button)
						{
							if (!e.second.lock()->_lockedIndButtonRelease.contains(button)) {
								Functor f = func; f();
							}
							else e.second.lock()->_lockedIndButtonRelease.erase(button);
						}

				}
			}
		}
	}

	void drawAllObjects() {
		for (auto const& e : oc._objectDraws) {
			Functor f = e.second; f();
		}
	}

	void moveAllObjects() {
		for (auto const& e : oc._objectMoves) {

			Functor f = e.second.first; f();
			f = e.second.second; f();

			if (oc._objectWithCollisions[e.first].lock() != nullptr) {
				sf::FloatRect b = oc._objectWithCollisions[e.first].lock()->getObjectBounds();

				for (std::pair<uint64_t, std::weak_ptr<Collidable>> other : oc._objectWithCollisions)
					if (other.second.lock()->getObjectBounds() != b and 
						other.second.lock()->getObjectBounds().intersects(b)) 
					{
						std::string className; for (const auto& cn : oc._membership) if (cn.second.contains(e.first)) className = cn.first;
						std::set<collisionSide> sides = other.second.lock()->
							checkCollisionSide(100, oc._objectWithCollisions[e.first].lock());
						std::weak_ptr<Base> object = oc._database[className][e.first];
						sf::FloatRect otherB = other.second.lock()->getObjectBounds();
						if (sides.contains(UP)) {
							object.lock()->forcePositionChange(
								sf::Vector2f(object.lock()->getPosition().x, 
									otherB.top - b.height / 2.f));
						}
						else if (sides.contains(DOWN)) {
							object.lock()->forcePositionChange(
								sf::Vector2f(object.lock()->getPosition().x,
									otherB.top + otherB.height + b.height / 2.f));
						}
						else if (sides.contains(RIGHT)) {
							object.lock()->forcePositionChange(
								sf::Vector2f(otherB.left + otherB.width + b.width / 2.f, 
									object.lock()->getPosition().y));
						}
						else if (sides.contains(LEFT)) {
							object.lock()->forcePositionChange(
								sf::Vector2f(otherB.left - b.width / 2.f,
									object.lock()->getPosition().y));
						}
						break;
					}

			}

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
				try {
					if (object == nullptr) throw std::exception("Object Terminated.");
					if (!object->isObjectAlive()) {

						deleteMutex.lock();
						oc.deleteObject(object->getID());
						deleteMutex.unlock();

						break;
					}
				}
				catch (const std::exception& err) {
					break;
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

	bool init(std::pair<int, int> _windowSize, std::string _windowName, bool _resizable, unsigned int _framerate) {

		window = std::make_unique<sf::RenderWindow>
			(
				sf::VideoMode(_windowSize.first, _windowSize.second),
				_windowName, _resizable ? (sf::Style::Default) : (sf::Style::Close)
			);
		window->setFramerateLimit(_framerate); __framerate = _framerate;
		window->setVerticalSyncEnabled(true);
		window->setKeyRepeatEnabled(false);
		window->setPosition({ 0,0 });

		event = std::make_unique<sf::Event>();

		isWindowOpen = true;

		std::cout << "<- Engine Loaded ->\n";
		return isWindowOpen;
	}

	bool lockViewOnObject(std::pair<std::string, uint64_t> _objectData) {
		if (oc._database[_objectData.first][_objectData.second] != nullptr) {
			viewObjectData = _objectData;
			return viewLock = true;
		}
		return false;
	}

	void run() {

		isWindowOpen = true;

		sf::Thread collisionThread(&watchCollisionThread);
		collisionThread.launch();

		sf::Int32 prevTime = globalClock.getElapsedTime().asMilliseconds();

		if (window) {
			window->setActive(false);

			while (isWindowOpen) {
				sf::Int32 elapsedTime = globalClock.getElapsedTime().asMilliseconds();
				if (elapsedTime - prevTime > 1000 / (__framerate)) {
					prevTime = elapsedTime;

					try {
						if (viewLock) {
							std::weak_ptr<Base> _viewObject = oc._database[viewObjectData.first][viewObjectData.second];
							if (_viewObject.lock() == nullptr) throw std::exception("ViewObject terminated.");
							view.reset(sf::FloatRect(
								int(_viewObject.lock()->getPosition().x),
								int(_viewObject.lock()->getPosition().y),
								int(window->getSize().x), int(window->getSize().y)
							));
							view.setCenter(
								_viewObject.lock()->getPosition().x,
								_viewObject.lock()->getPosition().y
							);
							window->setView(view);
							
						}
					}
					catch (const std::exception& err) {
						viewLock = false;
					}

					checkAndExecuteEventsInAllObjects();
					moveAllObjects();
					updateAllObjects();
					animateAllObjects();
					deleteAllObjects();
					
					window->clear();
					drawAllObjects();
					window->display();
				}
			} 
			window->close();

		}
		else {

			std::cout << "!- Init the window -!\n";

		}

		collisionThread.wait();
	
	}

} inline engine;