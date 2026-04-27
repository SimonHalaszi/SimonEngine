#ifndef UI_ELEMENT_HPP
#define UI_ELEMENT_HPP

#include "GameObject2D.hpp"

// UIElement Hierarchy
class UIElement : public GameObject2D {
	public:
		UIElement() {}

		void onStart() override {}
		void draw() override {}
		void update() override {}
		void onDestruction() override {}
		void establishFields() override {}

	protected:
		bool drawElement_ = true;
};

#endif