export module Massable;

export class Massable {
	float _object_mass;
public:
	Massable(float _mass = 0.f) : _object_mass(_mass) {}

	float setObjectMass(float newMass) {
		_object_mass = newMass;
		return _object_mass;
	}
	float getObjectMass() {
		return _object_mass;
	}

};