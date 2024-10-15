export module Functor;

import std;

export class Functor {
	std::function<void()> __body;
	std::vector<Functor> __body_addition;

public:
	Functor() {}
	Functor(std::function<void()>&& f) : __body(f) {}
	
	void operator()() {
		for (const auto& f : __body_addition) f.__body();
		return __body();
	}
	void operator+=(Functor f) {
		__body_addition.push_back(f);
	}
};