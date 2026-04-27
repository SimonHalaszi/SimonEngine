#include "EditorSaveLoad.hpp"

#include <algorithm>
#include <cerrno>
#include <direct.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "AssetFactory.hpp"
#include "CollisionObject2D.hpp"

// Returns the save file path, they use the .editoractions format
std::string saveFilePath(const std::string& fileName) {
	return std::string("../EditorSaves") + "/" + fileName + ".editoractions";
}

// Makes sure a save directory exist, or creates it
bool ensureSaveDirectory() {
	errno = 0;
	const char* editorSavesDirectory = "../EditorSaves";
	const int result = _mkdir(editorSavesDirectory);
	return result == 0 || errno == EEXIST;
}

// EditorSavedFieldType -> String for saving
std::string fieldTypeToString(EditorSavedFieldType type) {
	switch (type) {
		case EditorSavedFieldType::Int:
			return "INT";
		case EditorSavedFieldType::Char:
			return "CHAR";
		case EditorSavedFieldType::Float:
			return "FLOAT";
		case EditorSavedFieldType::Bool:
			return "BOOL";
		case EditorSavedFieldType::String:
		default:
			return "STRING";
	}
}

// String -> EditorSavedFieldType for loading
EditorSavedFieldType fieldTypeFromString(const std::string& type) {
	if (type == "INT") {
		return EditorSavedFieldType::Int;
	}
	if (type == "CHAR") {
		return EditorSavedFieldType::Char;
	}
	if (type == "FLOAT") {
		return EditorSavedFieldType::Float;
	}
	if (type == "BOOL") {
		return EditorSavedFieldType::Bool;
	}
	return EditorSavedFieldType::String;
}

// Gets the index of a child in a children vector
int findChildIndex(const std::vector<std::unique_ptr<GameObject2D>>* objects, const GameObject2D* object) {
	if (!objects || !object) {
		return -1;
	}

	for (int i = 0; i < objects->size(); ++i) {
		if ((*objects)[i].get() == object) {
			return i;
		}
	}

	return -1;
}

// For a given scene and index path will get the corresponding gameObject
GameObject2D* resolveObjectPath(Scene* scene, const std::vector<int>& path) {
	if (!scene || path.empty()) {
		return nullptr;
	}

	std::vector<std::unique_ptr<GameObject2D>>* objectVector = scene->getRootObjects();
	GameObject2D* currentObject = nullptr;
	for (int index : path) {
		if (!objectVector || index < 0 || index >= static_cast<int>(objectVector->size())) {
			return nullptr;
		}

		currentObject = (*objectVector)[index].get();
		objectVector = currentObject->getChildren();
	}

	return currentObject;
}

// For a given scene and index parent path will get the corresponding parent object, if it is a parent
std::vector<std::unique_ptr<GameObject2D>>* resolveParentPath(Scene* scene, const std::vector<int>& parentPath) {
	if (!scene) {
		return nullptr;
	}

	if (parentPath.empty()) {
		return scene->getRootObjects();
	}

	GameObject2D* parentObject = resolveObjectPath(scene, parentPath);
	return parentObject ? parentObject->getChildren() : nullptr;
}

// Collects all the field values in a given field and adds them to the given values vector
// For saving
void collectFieldValues(const IField* field, const std::string& fieldPath, std::vector<EditorSavedFieldValue>& values) {
	if (!field) {
		return;
	}

	if (const IntField* intField = dynamic_cast<const IntField*>(field)) {
		values.push_back({ EditorSavedFieldType::Int, fieldPath, std::to_string(intField->getValue()) });
		return;
	}
	if (const CharField* charField = dynamic_cast<const CharField*>(field)) {
		values.push_back({ EditorSavedFieldType::Char, fieldPath, std::string(1, charField->getValue()) });
		return;
	}
	if (const FloatField* floatField = dynamic_cast<const FloatField*>(field)) {
		std::ostringstream stream;
		stream << std::setprecision(9) << floatField->getValue();
		values.push_back({ EditorSavedFieldType::Float, fieldPath, stream.str() });
		return;
	}
	if (const BoolField* boolField = dynamic_cast<const BoolField*>(field)) {
		values.push_back({ EditorSavedFieldType::Bool, fieldPath, boolField->getValue() ? "1" : "0" });
		return;
	}
	if (const StringField* stringField = dynamic_cast<const StringField*>(field)) {
		values.push_back({ EditorSavedFieldType::String, fieldPath, stringField->getValue() });
		return;
	}
	if (const Vector2DField* vectorField = dynamic_cast<const Vector2DField*>(field)) {
		collectFieldValues(&vectorField->getXField(), fieldPath + ".x", values);
		collectFieldValues(&vectorField->getYField(), fieldPath + ".y", values);
		return;
	}
	if (const Transform2DField* transformField = dynamic_cast<const Transform2DField*>(field)) {
		collectFieldValues(&transformField->getPosField(), fieldPath + ".pos", values);
		collectFieldValues(&transformField->getScaleField(), fieldPath + ".scale", values);
		collectFieldValues(&transformField->getRotationField(), fieldPath + ".rotation", values);
		collectFieldValues(&transformField->getMirrorField(), fieldPath + ".mirror", values);
		collectFieldValues(&transformField->getFlipField(), fieldPath + ".flip", values);
		return;
	}
}

// Splits a field path by the dots
std::vector<std::string> splitFieldPath(const std::string& fieldPath) {
	std::vector<std::string> segments;
	std::stringstream stream(fieldPath);
	std::string segment;
	while (std::getline(stream, segment, '.')) {
		segments.push_back(segment);
	}
	return segments;
}

// Applies all the field values in a given field
// For loading, returns false if there was a format error
bool applyFieldValues(IField* field, const std::vector<std::string>& segments, size_t segmentIndex, const EditorSavedFieldValue& value) {
	if (!field || segmentIndex >= segments.size() || field->getName() != segments[segmentIndex]) {
		return false;
	}

	const bool isLeaf = segmentIndex + 1 == segments.size();

	if (IntField* intField = dynamic_cast<IntField*>(field)) {
		if (!isLeaf) {
			return false;
		}
		intField->setValue(std::stoi(value.value));
		return true;
	}
	if (CharField* charField = dynamic_cast<CharField*>(field)) {
		if (!isLeaf) {
			return false;
		}
		charField->setValue(value.value.empty() ? '\0' : value.value[0]);
		return true;
	}
	if (FloatField* floatField = dynamic_cast<FloatField*>(field)) {
		if (!isLeaf) {
			return false;
		}
		floatField->setValue(std::stof(value.value));
		return true;
	}
	if (BoolField* boolField = dynamic_cast<BoolField*>(field)) {
		if (!isLeaf) {
			return false;
		}
		boolField->setValue(value.value == "1" || value.value == "true" || value.value == "TRUE");
		return true;
	}
	if (StringField* stringField = dynamic_cast<StringField*>(field)) {
		if (!isLeaf) {
			return false;
		}
		stringField->setValue(value.value);
		return true;
	}
	if (Vector2DField* vectorField = dynamic_cast<Vector2DField*>(field)) {
		return applyFieldValues(&vectorField->getXField(), segments, segmentIndex + 1, value)
			|| applyFieldValues(&vectorField->getYField(), segments, segmentIndex + 1, value);
	}
	if (Transform2DField* transformField = dynamic_cast<Transform2DField*>(field)) {
		return applyFieldValues(&transformField->getPosField(), segments, segmentIndex + 1, value)
			|| applyFieldValues(&transformField->getScaleField(), segments, segmentIndex + 1, value)
			|| applyFieldValues(&transformField->getRotationField(), segments, segmentIndex + 1, value)
			|| applyFieldValues(&transformField->getMirrorField(), segments, segmentIndex + 1, value)
			|| applyFieldValues(&transformField->getFlipField(), segments, segmentIndex + 1, value);
	}

	return false;
}

// Applies snapshots, which are the EditorSavedAction for the inspector
bool applySnapshot(GameObject2D* object, const std::vector<EditorSavedFieldValue>& values) {
	if (!object) {
		return false;
	}

	bool appliedAny = false;
	for (const EditorSavedFieldValue& value : values) {
		const std::vector<std::string> segments = splitFieldPath(value.path);
		for (auto& field : *object->getIFields()) {
			appliedAny = applyFieldValues(field.get(), segments, 0, value) || appliedAny;
		}
	}

	if (appliedAny) {
		object->updateWorldTransform();

		CollisionObject2D* collider = dynamic_cast<CollisionObject2D*>(object);
		if (collider) {
			collider->setCollisionEnabled(collider->isCollisionEnabled());
		}
	}

	return appliedAny;
}

// Writes an index path to a give output, for saving
void writePath(std::ofstream& output, const std::vector<int>& path) {
	output << path.size();
	for (int index : path) {
		output << ' ' << index;
	}
}

// Read an index path to a give output, for loading
bool readPath(std::istream& input, std::vector<int>& path) {
	size_t pathSize = 0;
	if (!(input >> pathSize)) {
		return false;
	}

	path.clear();
	for (size_t i = 0; i < pathSize; ++i) {
		int index = -1;
		if (!(input >> index)) {
			return false;
		}
		path.push_back(index);
	}
	return true;
}

// For a given object builds its index path from the root
std::vector<int> buildObjectPath(Scene* scene, GameObject2D* object) {
	std::vector<int> reversedPath;
	if (!scene || !object) {
		return reversedPath;
	}

	GameObject2D* current = object;
	while (current) {
		GameObject2D* parent = current->getParent();
		std::vector<std::unique_ptr<GameObject2D>>* siblings = parent ? parent->getChildren() : scene->getRootObjects();
		const int index = findChildIndex(siblings, current);
		if (index < 0) {
			return {};
		}

		reversedPath.push_back(index);
		current = parent;
	}

	std::reverse(reversedPath.begin(), reversedPath.end());
	return reversedPath;
}

// Saves all of an objects IFields into a std::vector<EditorSavedFieldValue>
std::vector<EditorSavedFieldValue> saveIFields(GameObject2D* object) {
	std::vector<EditorSavedFieldValue> values;
	if (!object) {
		return values;
	}

	for (const auto& field : *object->getIFields()) {
		collectFieldValues(field.get(), field->getName(), values);
	}

	return values;
}

// Saves all the given EditorSavedActions to a given filepath
void saveEditorActionsToFile(const std::string& filename, const std::vector<EditorSavedAction>& actions) {
	const std::string filePath = saveFilePath(filename);
	if (!ensureSaveDirectory()) {
		std::cout << "saveEditorActionsToFile() : Failed to create save directory for " << filePath << std::endl;
		return;
	}

	std::ofstream output(filePath, std::ios::trunc);
	if (!output.is_open()) {
		std::cout << "saveEditorActionsToFile() : Failed to open " << filePath << std::endl;
		return;
	}

	// For all actions, output the corresponding formatting
	for (const EditorSavedAction& action : actions) {
		switch (action.type) {
			case EditorSavedActionType::Create:
				output << "CREATE ";
				writePath(output, action.parentPath);
				output << ' ' << action.assetButtonIndex << '\n';
				break;
			case EditorSavedActionType::Delete:
				output << "DELETE ";
				writePath(output, action.objectPath);
				output << '\n';
				break;
			case EditorSavedActionType::Reorder:
				output << "REORDER ";
				writePath(output, action.parentPath);
				output << ' ' << action.fromIndex << ' ' << action.toIndex << '\n';
				break;
			case EditorSavedActionType::Snapshot:
				output << "SNAPSHOT ";
				writePath(output, action.objectPath);
				output << ' ' << action.fieldValues.size() << '\n';
				for (const EditorSavedFieldValue& fieldValue : action.fieldValues) {
					output << "FIELD "
						<< fieldTypeToString(fieldValue.type) << ' '
						<< std::quoted(fieldValue.path) << ' '
						<< std::quoted(fieldValue.value) << '\n';
				}
				break;
		}
	}

	std::cout << "saveEditorActionsToFile() : Saved " << actions.size() << " editor actions to " << filePath << std::endl;
}

// Loads all the given EditorSavedActions from a given filename into EditorSavedActions
bool loadEditorActionsFromFile(const std::string& filename, std::vector<EditorSavedAction>& outActions) {
	const std::string filePath = saveFilePath(filename);
	std::ifstream input(filePath);
	if (!input.is_open()) {
		std::cout << "loadEditorActionsFromFile() : No save file found for " << filePath << std::endl;
		return false;
	}

	std::string recordType;

	outActions.clear();
	// While we have strings load in all the corresponding EditorSavedActions, also push them into the given outActions
	while (input >> recordType) {
		EditorSavedAction action;
		if (recordType == "CREATE") {
			action.type = EditorSavedActionType::Create;
			if (!readPath(input, action.parentPath) || !(input >> action.assetButtonIndex)) {
				std::cout << "loadEditorActionsFromFile() : Corrupt create action in " << filePath << std::endl;
				return false;
			}
		}
		else if (recordType == "DELETE") {
			action.type = EditorSavedActionType::Delete;
			if (!readPath(input, action.objectPath)) {
				std::cout << "loadEditorActionsFromFile() : Corrupt delete action in " << filePath << std::endl;
				return false;
			}
		}
		else if (recordType == "REORDER") {
			action.type = EditorSavedActionType::Reorder;
			if (!readPath(input, action.parentPath) || !(input >> action.fromIndex >> action.toIndex)) {
				std::cout << "loadEditorActionsFromFile() : Corrupt reorder action in " << filePath << std::endl;
				return false;
			}
		}
		else if (recordType == "SNAPSHOT") {
			action.type = EditorSavedActionType::Snapshot;
			size_t fieldCount = 0;
			if (!readPath(input, action.objectPath) || !(input >> fieldCount)) {
				std::cout << "loadEditorActionsFromFile() : Corrupt snapshot action in " << filePath << std::endl;
				return false;
			}

			for (size_t i = 0; i < fieldCount; ++i) {
				std::string fieldRecordType;
				input >> fieldRecordType;
				if (fieldRecordType != "FIELD") {
					std::cout << "loadEditorActionsFromFile() : Corrupt snapshot field in " << filePath << std::endl;
					return false;
				}

				EditorSavedFieldValue fieldValue;
				std::string typeName;
				if (!(input >> typeName >> std::quoted(fieldValue.path) >> std::quoted(fieldValue.value))) {
					std::cout << "loadEditorActionsFromFile() : Corrupt snapshot field payload in " << filePath << std::endl;
					return false;
				}
				fieldValue.type = fieldTypeFromString(typeName);
				action.fieldValues.push_back(fieldValue);
			}
		}
		else {
			std::cout << "loadEditorActionsFromFile() : Unknown record type " << recordType << std::endl;
			return false;
		}

		outActions.push_back(action);
	}

	std::cout << "loadEditorActionsFromFile() : Loaded " << outActions.size() << " editor actions from " << filePath << std::endl;
	return true;
}

// Given EditorSavedActions and a scene will replay and apply all of the actions on the scene objects, used by Editor
bool replayEditorActions(Scene* scene, const std::vector<EditorSavedAction>& actions) {
	const std::vector<std::string>& assetOptions = AssetFactory::getInstance().getFactoryOptions();
	for (const EditorSavedAction& action : actions) {
		if (action.type == EditorSavedActionType::Create) {
			if (action.assetButtonIndex < 0 || action.assetButtonIndex >= static_cast<int>(assetOptions.size())) {
				std::cout << "replayEditorActions() : Invalid asset button index in save file" << std::endl;
				return false;
			}

			std::unique_ptr<GameObject2D> createdObject = AssetFactory::getInstance().createGameObject(assetOptions[action.assetButtonIndex]);
			if (!createdObject) {
				std::cout << "replayEditorActions() : Failed to create asset during replay" << std::endl;
				return false;
			}

			GameObject2D* parentObject = resolveObjectPath(scene, action.parentPath);
			if (action.parentPath.empty()) {
				scene->addRootGameObject2D(std::move(createdObject));
				scene->getRootObjects()->back()->updateWorldTransform();
			}
			else if (parentObject) {
				parentObject->attachChild(std::move(createdObject));
				parentObject->getChildren()->back()->updateWorldTransform();
			}
			else {
				std::cout << "replayEditorActions() : Failed to resolve parent path during create replay" << std::endl;
				return false;
			}
		}
		else if (action.type == EditorSavedActionType::Delete) {
			if (action.objectPath.empty()) {
				continue;
			}

			std::vector<int> parentPath(action.objectPath.begin(), action.objectPath.end() - 1);
			std::vector<std::unique_ptr<GameObject2D>>* parent = resolveParentPath(scene, parentPath);
			const int deleteIndex = action.objectPath.back();
			if (!parent || deleteIndex < 0 || deleteIndex >= static_cast<int>(parent->size())) {
				std::cout << "replayEditorActions() : Failed to resolve delete path during replay" << std::endl;
				return false;
			}

			parent->erase(parent->begin() + deleteIndex);
		}
		else if (action.type == EditorSavedActionType::Reorder) {
			std::vector<std::unique_ptr<GameObject2D>>* parent = resolveParentPath(scene, action.parentPath);
			if (!parent
				|| action.fromIndex < 0
				|| action.fromIndex >= static_cast<int>(parent->size())
				|| action.toIndex < 0
				|| action.toIndex >= static_cast<int>(parent->size())) {
				std::cout << "replayEditorActions() : Failed to resolve reorder path during replay" << std::endl;
				return false;
			}

			std::unique_ptr<GameObject2D> movedObject = std::move((*parent)[action.fromIndex]);
			parent->erase(parent->begin() + action.fromIndex);
			parent->insert(parent->begin() + action.toIndex, std::move(movedObject));
		}
		else if (action.type == EditorSavedActionType::Snapshot) {
			GameObject2D* object = resolveObjectPath(scene, action.objectPath);
			if (!object || !applySnapshot(object, action.fieldValues)) {
				std::cout << "replayEditorActions() : Failed to apply snapshot during replay" << std::endl;
				return false;
			}
		}
	}

	return true;
}
