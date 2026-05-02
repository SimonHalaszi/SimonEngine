#ifndef EDITOR_SAVE_LOAD_HPP
#define EDITOR_SAVE_LOAD_HPP

#include <string>
#include <vector>

#include "Scene.hpp"
#include "GameObject2D.hpp"

// Used for snapshots, these are the atomic field types
enum class EditorSavedFieldType {
	Int,
	Char,
	Float,
	Bool,
	String,
};

//
struct EditorSavedFieldValue {
	EditorSavedFieldType type = EditorSavedFieldType::String;
	std::string path;
	std::string value;
};

// EditorSavedActionTypes create -> asset panel, delete, reorder -> hierarchy, snapshot -> inspector
enum class EditorSavedActionType {
	Create,
	Delete,
	Reorder,
	Snapshot,
};

//
struct EditorSavedAction {
	EditorSavedActionType type = EditorSavedActionType::Snapshot;
	std::vector<int> objectPath;
	std::vector<int> parentPath;
	int assetButtonIndex = -1;
	int fromIndex = -1;
	int toIndex = -1;
	std::vector<EditorSavedFieldValue> fieldValues;
};

// For a given object builds its index path from the root, used by Editor
std::vector<int> buildObjectPath(Scene* scene, GameObject2D* object);
// Saves all of an objects IFields into a std::vector<EditorSavedFieldValue>, used by Editor
std::vector<EditorSavedFieldValue> saveIFields(GameObject2D* object);

// Saves all the given EditorSavedActions to a given filename, used by Editor
void saveEditorActionsToFile(const std::string& filename, const std::vector<EditorSavedAction>& actions);
// Loads all the given EditorSavedActions from a given filename into EditorSavedActions, used by Editor
bool loadEditorActionsFromFile(const std::string& filename, std::vector<EditorSavedAction>& outActions);
// Given EditorSavedActions and a scene will replay and apply all of the actions on the scene objects, used by Editor
bool replayEditorActions(Scene* scene, const std::vector<EditorSavedAction>& actions);

#endif
