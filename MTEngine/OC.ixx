export module OC;

import Globals;
export import Base;

import Moveable;
import Drawable;
import Updateable;
import Eventable;
import Collidable;
import Animateable;

export class OC {

	std::map<std::string, std::unordered_map<uint64_t, std::shared_ptr<Base>>> _database;

	std::unordered_map<uint64_t, std::pair<Functor, Functor>> _objectMoves; // accelerate, move
	std::unordered_map<uint64_t, Functor> _objectDraws;
	std::unordered_map<uint64_t, Functor> _objectUpdates;
	std::unordered_map<uint64_t, std::pair<Functor, Functor>> _objectAnimations;
	std::unordered_map<uint64_t, std::weak_ptr<Collidable>> _objectWithCollisions;
	std::unordered_map<uint64_t, std::weak_ptr<Eventable>> _objectsWithEventsAssociatedWithFunctions;

	std::map<std::string, std::set<uint64_t>> _membership;

	void insertObject(std::shared_ptr<Base>& r) {

		_database[r->getClassName()][r->getID()] = r;
		_membership[r->getClassName()].insert(r->getID());

		if (std::shared_ptr<Moveable> x = std::dynamic_pointer_cast<Moveable>(r)) {
			_objectMoves[r->getID()] = std::make_pair(Functor([x]() { x->accelerateObject(); }), Functor([x]() { x->moveObject(); }));
		}
		if (std::shared_ptr<Drawable> x = std::dynamic_pointer_cast<Drawable>(r)) {
			_objectDraws[r->getID()] = Functor([x]() { x->drawObject(); });
		}
		if (std::shared_ptr<Updateable> x = std::dynamic_pointer_cast<Updateable>(r)) {
			_objectUpdates[r->getID()] = Functor([x]() { x->updateObject(); });
		}
		if (std::shared_ptr<Animateable> x = std::dynamic_pointer_cast<Animateable>(r)) {
			_objectAnimations[r->getID()] =
				std::make_pair(Functor([x]() { x->updateAnimation(); }), Functor([x]() { x->animateObject(); }));
		}
		if (std::shared_ptr<Collidable> x = std::dynamic_pointer_cast<Collidable>(r)) {
			_objectWithCollisions[r->getID()] = x;
		}
		if (std::shared_ptr<Eventable> x = std::dynamic_pointer_cast<Eventable>(r)) {
			_objectsWithEventsAssociatedWithFunctions[r->getID()] = x;
		}

	}

	void deleteObject(uint64_t _id) {

		_objectMoves.erase(_id);
		_objectDraws.erase(_id);
		_objectUpdates.erase(_id);
		_objectAnimations.erase(_id);
		_objectWithCollisions.erase(_id);
		_objectsWithEventsAssociatedWithFunctions.erase(_id);

		for (auto& e : _membership) {
			if (e.second.contains(_id)) {
				_database[e.first].erase(_id);
				_membership[e.first].erase(_id);
				break;
			}
		}

	}

public:

	OC() { std::cout << "<- ObjectContainer Running ->\n"; }

	~OC() {
		_database.clear();
		_objectMoves.clear();
		_objectDraws.clear();
		_objectUpdates.clear();
		_objectsWithEventsAssociatedWithFunctions.clear();
	}

	friend class Engine;
} inline oc;