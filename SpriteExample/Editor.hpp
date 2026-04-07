#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <GL/glut.h>
#include <GL/freeglut.h>

#include <vector>
#include <memory>
#include <iostream>

#include "GameObject2D.hpp"
#include "WindowConstants.hpp"
#include "SoundManager.hpp"
#include "Scene.hpp"
#include "InputManager.hpp"

#include "Hierarchy.hpp"
#include "Inspector.hpp"
#include "AssetPanel.hpp"
#include "TopPanel.hpp"

// Sits on top of game to give editor logic
class Editor {
	public:
		Editor(Scene* scene);

		void editorDraw() const;
		void editorUpdate();

		bool inEditor() const { return inEditor_; }
		void exitEditor();
		void enterEditor();

		bool topPanelMarkedForQuiting() const { return topPanel_.markedForQuiting(); }

		~Editor();
	private:
		bool inEditor_ = false;

		Scene* scene_;

		float editorX_ = 0.0f;
		float editorY_ = 0.0f;
		float editorZoomFactor_ = 1.0f;
		float moveSpeed_ = 1.0f;

		Hierarchy hierarchy_;
		Inspector inspector_;
		AssetPanel assetPanel_;
		TopPanel topPanel_;

		ViewportContext middlePanelContext_;

		// GameObject currently selected (Pulled from Hierarchy, then pushed to Inspector)
		GameObject2D* focusedGameObject_;
};

#endif