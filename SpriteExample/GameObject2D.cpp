#include "GameObject2D.hpp"

void GameObject2D::rootOnStart() {
	onStart();

	isWorldTransformOutDated_ = true;

	for (auto& child : children_) {
		child->rootOnStart();
	}
}

// Runs once per update of the Scene
void GameObject2D::rootUpdate() {
	if (isWorldTransformOutDated_ || (parent_ && parent_->isWorldTransformOutDated_)) {
		updateWorldTransform();
	}
	
	update();

	// Iterate with index so we can safely remove children that self-destruct during update.
	for (auto it = children_.begin(); it != children_.end();) {
		GameObject2D* child = it->get();
		
		child->rootUpdate();

		if (child->isAlive()) {
			++it;
		}
		else {
			child->rootOnDestruction();
			it = children_.erase(it);
		}
	}
}

// Runs once per frame update of the Scene
void GameObject2D::rootDraw() {
	draw();

	for (auto& child : children_) {
		child->rootDraw();
	}
}

// Runs at the end of a frame after destroy in Scene update
void GameObject2D::rootOnDestruction() {
	onDestruction();

	for (auto& child : children_) {
		child->rootOnDestruction();
	}
}

void GameObject2D::rootEstablishFields() {
	IFields_.push_back(std::make_unique<StringField>("Name", &name_));
	IFields_.push_back(std::make_unique<StringField>("Tag", &tag_));
	IFields_.push_back(std::make_unique<Transform2DField>("Local Transform", &localTransform_));
	
	establishFields();
	
	for (auto& child : children_) {
		child->rootEstablishFields();
	}
}


void GameObject2D::outDateWorldTransform() {
	isWorldTransformOutDated_ = true;

	for (auto& child : children_) {
		child->outDateWorldTransform();
	}
}

// Recalculate world transforms
void GameObject2D::updateWorldTransform() {
	if (parent_) {
		worldTransform_ = composeTransforms(parent_->getWorldTransform(), localTransform_);
	}
	else {
		worldTransform_ = localTransform_;
	}

	isWorldTransformOutDated_ = false;

	for (auto& child : children_) {
		child->updateWorldTransform();
	}
}

void GameObject2D::attachChild(std::unique_ptr<GameObject2D> child) {
	if (!child) {
		return;
	}

	if (child->parent_) {
		throw std::runtime_error("GameObject2D::attachChild : child already has a parent");
	}

	child->parent_ = this;
	children_.push_back(std::move(child));

	children_.back()->rootOnStart();
	children_.back()->rootEstablishFields();
}