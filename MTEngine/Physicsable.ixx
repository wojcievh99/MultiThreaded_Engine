export module Physicsable;

import Globals;

export class Physicsable {
	std::vector<sf::Vector2f> forces;
	std::vector<sf::Vector2f> reaction_forces;
	float _object_mass;
public:
	Physicsable(float _mass = 1.f, std::vector<sf::Vector2f> _forces = { sf::Vector2f{0.f, 0.f} })
		: _object_mass(_mass), forces(_forces), reaction_forces({ sf::Vector2f{ 0.f, 0.f } })
	{
		//forces.push_back(sf::Vector2f{ 0.f, 0.98f * _object_mass });
	}

	void addForce(sf::Vector2f newForce, bool RF = false) {
		if (RF) reaction_forces.push_back(newForce);
		else forces.push_back(newForce);
	}
	bool addNotRepeatedForce(sf::Vector2f newForce, bool RF = false) {
		for (auto e : RF ? reaction_forces : forces) 
			if (e == newForce) return false;

		if (RF) reaction_forces.push_back(newForce);
		else forces.push_back(newForce);

		return true;
	}
	bool removeForce(sf::Vector2f force, bool RF = false) {
		bool result = false;
		if (RF) 
			for (size_t i = 0; i < reaction_forces.size(); i++) {
				if (reaction_forces[i] == force) {
					reaction_forces.erase(reaction_forces.begin() + i);
					result = true;
				}
			}
		else 
			for (size_t i = 0; i < forces.size(); i++) {
				if (forces[i] == force) {
					forces.erase(forces.begin() + i);
					result = true;
				}
			}
		return result;
	}
	void removeLastForce() {
		if (forces.size() > 0) 
			forces.pop_back();
	}
	void removeLastReactionForce() {
		if (reaction_forces.size() > 0) 
			reaction_forces.pop_back();
	}
	void clearForces() {
		forces.clear();
	}
	void clearReactionForces() {
		reaction_forces.clear();
	}
	sf::Vector2f sigmaF(bool RF = false) {
		sf::Vector2f result = sf::Vector2f{ 0.f, 0.f };
		for (auto e : forces) {
			result.x += e.x;
			result.y += e.y;
		}
		if (RF) {
			for (auto e : reaction_forces) {
				result.x += e.x;
				result.y += e.y;
			}
		}
		return result;
	}
	size_t getForcesSize() {
		return forces.size();
	}
	size_t getReactionForcesSize() {
		return reaction_forces.size();
	}

	float setObjectMass(float newMass) {
		_object_mass = newMass;
		return _object_mass;
	}
	float getObjectMass() {
		return _object_mass;
	}

};