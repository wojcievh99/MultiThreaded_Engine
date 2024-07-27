export module OC;

import Globals;
export import Base;

import Moveable;
import Drawable;
import Updateable;
import Eventable;
import Collidable;

export class OC {
	std::map<std::string, std::unordered_map<uint64_t, std::shared_ptr<Base>>> _database;

	std::list<std::pair<uint64_t, Functor>> _objectMoves;
	std::list<std::pair<uint64_t, Functor>> _objectDraws;
	std::list<std::pair<uint64_t, Functor>> _objectUpdates;
	std::list<std::pair<uint64_t, Collidable*>> _objectWithCollisions;
	std::list<std::pair<uint64_t, Eventable*>> _objectsWithEventsAssociatedWithFunctions;

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

		if (Moveable* x = dynamic_cast<Moveable*>(r.get())) {
			_objectMoves.push_back({ r->getID(), Functor([x]() { x->moveObject(); }) });
		}
		if (Drawable* x = dynamic_cast<Drawable*>(r.get())) {
			_objectDraws.push_back({ r->getID(), Functor([x]() { x->drawObject(); }) });
		}
		if (Updateable* x = dynamic_cast<Updateable*>(r.get())) {
			_objectUpdates.push_back({ r->getID(), Functor([x]() { x->updateObject(); }) });
		}
		if (Eventable* x = dynamic_cast<Eventable*>(r.get())) {
			_objectsWithEventsAssociatedWithFunctions.push_back({ r->getID(), x });
		}
		if (Collidable* x = dynamic_cast<Collidable*>(r.get())) {
			_objectWithCollisions.push_back({r->getID(), x});
		}
		
	}

	// memory leak? 
	void deleteObject(uint64_t _id) {
		std::string cn;
		for (const auto& [_classname, _set] : _membership) {
			if (_set.contains(_id)) {
				cn = _classname;
				break;
			}
		}

		auto it = std::find_if(
			std::begin(_objectsWithEventsAssociatedWithFunctions),
			std::end(_objectsWithEventsAssociatedWithFunctions),
			[&](const std::pair<uint64_t, Eventable*> f) 
			{if (f.first == _id) {
			delete f.second; return f.first;
			}});

		_objectsWithEventsAssociatedWithFunctions.erase(it);

		auto it2 = std::find_if(
			std::begin(_objectWithCollisions),
			std::end(_objectWithCollisions),
			[&](const std::pair<uint64_t, Collidable*> f)
			{if (f.first == _id) {
			delete f.second; return f.first;
		}});

		_objectWithCollisions.erase(it2);

		auto it3 = std::find_if(
			std::begin(_objectMoves),
			std::end(_objectMoves),
			[&](const std::pair<uint64_t, Functor> f) {return f.first == _id; });

		_objectMoves.erase(it3);

		auto it4 = std::find_if(
			std::begin(_objectDraws),
			std::end(_objectDraws),
			[&](const std::pair<uint64_t, Functor> f) {return f.first == _id; });

		_objectDraws.erase(it4);

		auto it5 = std::find_if(
			std::begin(_objectUpdates),
			std::end(_objectUpdates),
			[&](const std::pair<uint64_t, Functor> f) {return f.first == _id; });

		_objectUpdates.erase(it5);

		// sidenote: those iterators don't look good

		_membership[cn].erase(_id);
		_database[cn].erase(_id);
	}
		

	friend class Engine;
} inline oc;