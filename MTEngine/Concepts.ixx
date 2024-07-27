export module Concepts;

import std;

export template <typename T>
concept Base2D =
	requires (T t) {
	t.getID;
	t.getClassName;
};