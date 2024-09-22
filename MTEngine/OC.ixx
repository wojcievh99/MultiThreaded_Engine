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

	std::list<std::pair<uint64_t, Functor>> _objectMoves;
	std::list<std::pair<uint64_t, Functor>> _objectDraws;
	std::list<std::pair<uint64_t, Functor>> _objectUpdates;
	std::list<std::pair<uint64_t, std::pair<Functor, Functor>>> _objectAnimations;
	std::list<std::pair<uint64_t, std::weak_ptr<Collidable>>> _objectWithCollisions;
	std::list<std::pair<uint64_t, std::weak_ptr<Eventable>>> _objectsWithEventsAssociatedWithFunctions;

	std::map<std::string, std::set<uint64_t>> _membership;

public:

	OC() { std::cout << "<- ObjectContainer Running ->\n"; }

	~OC() {
		_database.clear();
		_objectMoves.clear();
		_objectDraws.clear();
		_objectUpdates.clear();
		_objectsWithEventsAssociatedWithFunctions.clear();
	}

	void insertObject(std::shared_ptr<Base>& r) {

		_database[r->getClassName()][r->getID()] = r;
		_membership[r->getClassName()].insert(r->getID());

		if (std::shared_ptr<Moveable> x = std::dynamic_pointer_cast<Moveable>(r)) {
			_objectMoves.push_back({ r->getID(), Functor([x]() { x->moveObject(); }) });
		}
		if (std::shared_ptr<Drawable> x = std::dynamic_pointer_cast<Drawable>(r)) {
			_objectDraws.push_back({ r->getID(), Functor([x]() { x->drawObject(); }) });
		}
		if (std::shared_ptr<Updateable> x = std::dynamic_pointer_cast<Updateable>(r)) {
			_objectUpdates.push_back({ r->getID(), Functor([x]() { x->updateObject(); }) });
		}
		if (std::shared_ptr<Animateable> x = std::dynamic_pointer_cast<Animateable>(r)) {
			_objectAnimations.push_back({ r->getID(), {Functor([x]() { x->animateObject(); }),  Functor([x]() { x->updateAnimation(); })} });
		}
		if (std::shared_ptr<Eventable> x = std::dynamic_pointer_cast<Eventable>(r)) {
			_objectsWithEventsAssociatedWithFunctions.push_back({ r->getID(), x });
		}
		if (std::shared_ptr<Collidable> x = std::dynamic_pointer_cast<Collidable>(r)) {
			_objectWithCollisions.push_back({r->getID(), x});
		}
		
	}

	// memory leak? 
	void deleteObject(uint64_t _id) {
		
		std::string __className;
		for (auto e : _membership) {
			if (e.second.contains(_id)) {
				__className = e.first;
				_membership[__className].erase(_id);
				break;
			}
		}

		_database[__className].erase(_id);

		// Helper lambda to remove entries with the given id from a list of pairs
		auto removeFromList = [_id](auto& list) {
			list.remove_if([_id](const auto& pair) {
				return pair.first == _id;
				});
		};

		// Remove from _objectMoves, _objectDraws, _objectUpdates, _objectAnimations
		removeFromList(_objectMoves);
		removeFromList(_objectDraws);
		removeFromList(_objectUpdates);
		removeFromList(_objectAnimations);
		removeFromList(_objectWithCollisions);
		removeFromList(_objectsWithEventsAssociatedWithFunctions);
		
	}
		

	friend class Engine;
} inline oc;