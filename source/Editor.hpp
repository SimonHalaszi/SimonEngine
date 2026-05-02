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
#include "ScenePanel.hpp"
#include "EditorSaveLoad.hpp"

// Sits on top of game to give editor logic
class Editor {
	public:
		Editor(Scene* scene);

		void editorDraw() const;
		void editorUpdate();

		bool inEditor() const { return inEditor_; }
		void exitEditor();
		void enterEditor();
		void loadEditorState();

		bool topPanelMarkedForQuiting() const { return topPanel_.markedForQuiting(); }

		~Editor();
	private:
		// Functions used for the saving and loading processes
		// Resets panels to the default view
		void resetPanelsToDefaultView();
		// Recorders for every action type 
		// Get passed into their corresponding panels update functions and get called inside of them

		// Create Action - Asset Panel
		void recordCreateAction(int assetButtonIndex, GameObject2D* parentObject);
		// Delete Action - Hierarchy Panel
		void recordDeleteAction(GameObject2D* object);
		// Reorder Action - Hierarchy Panel
		void recordReorderAction(GameObject2D* parentObject, int fromIndex, int toIndex);
		// Snapshot Action - Inspector Panel
		void recordSnapshotAction(GameObject2D* object);
		// Save and Load Actions - Top Panel, passed in at initialization
		void saveEditorState();

		bool inEditor_ = true;
		bool canSave_ = true;

		Scene* scene_;

		float editorX_ = 0.0f;
		float editorY_ = 0.0f;
		float editorZoomFactor_ = 1.0f;
		float moveSpeed_ = 1.0f;

		Hierarchy hierarchy_;
		Inspector inspector_;
		AssetPanel assetPanel_;
		TopPanel topPanel_;
		ScenePanel scenePanel_;

		ViewportContext middlePanelContext_;

		// GameObject currently selected (Pulled from Hierarchy, then pushed to Inspector)
		GameObject2D* focusedGameObject_;

		std::string saveName_;
		std::vector<EditorSavedAction> saveActions_;
};

#endif