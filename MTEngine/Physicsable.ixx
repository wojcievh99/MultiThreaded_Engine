export module Physicsable;

import Globals;

export class Physicsable {
	std::vector<sf::Vector2f> forces;
	float _object_mass;
public:
	Physicsable(float _mass = 1.f, std::vector<sf::Vector2f> _forces = { sf::Vector2f{0.f, 0.f} })
		: _object_mass(_mass), forces(_forces)
	{
		//forces.push_back(sf::Vector2f{ 0.f, 0.98f * _object_mass });
	}

	void addForce(sf::Vector2f newForce) {
		forces.push_back(newForce);
	}
	bool addNotRepeatedForce(sf::Vector2f newForce) {
		for (auto e : forces) 
			if (e == newForce) return false;
		forces.push_back(newForce);
		return true;
	}
	bool removeForce(sf::Vector2f force) {
		bool result = false;
		for (size_t i = 0; i < forces.size(); i++) {
			if (forces[i] == force) {
				forces.erase(forces.begin() + i);
				result = true;
			}
		}
		return result;
	}
	bool removeForceBySubscript(size_t subscript) {
		if (forces.size() - 1 >= subscript)
			forces.erase(forces.begin() + subscript);
		else return false;
		return true;
	}
	bool removeForceBySubscript(std::vector<size_t> subscripts) {
		for (auto subscript : subscripts) {
			if (forces.size() - 1 >= subscript)
			{
				forces.erase(forces.begin() + subscript);
			}
		}
		return true;
	}
	sf::Vector2f sigmaF() {
		sf::Vector2f result = sf::Vector2f{ 0.f, 0.f };
		for (auto e : forces) {
			result.x += e.x;
			result.y += e.y;
		}
		return result;
	}
	size_t getForcesSize() {
		return forces.size();
	}
	sf::Vector2f getForceBySubscript(size_t subscript) {
		if (forces.size() - 1 > subscript)
			return forces[subscript];
		return { 0.f, 0.f };
	}

	float setObjectMass(float newMass) {
		_object_mass = newMass;
		return _object_mass;
	}
	float getObjectMass() {
		return _object_mass;
	}

};