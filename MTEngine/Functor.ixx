export module Functor;

import std;

export class Functor {
	std::function<void()> _body;
public:
	Functor() {}
	Functor(std::function<void()>&& f) : _body(f) {}
	
	void operator()() {
		return _body();
	}
};