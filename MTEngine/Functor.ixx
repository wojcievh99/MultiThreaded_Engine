export module Functor;

import std;

export class Functor {
	std::function<void()> __body;
public:
	Functor() {}
	Functor(std::function<void()>&& f) : __body(f) {}
	
	void operator()() {
		return __body();
	}
};