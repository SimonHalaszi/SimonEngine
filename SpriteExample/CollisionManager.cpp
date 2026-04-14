#include "CollisionManager.hpp"
#include "CollisionObject2D.hpp"

void CollisionManager::registerObject(CollisionObject2D* obj) {
	if (!obj) {
		return;
	}
	objects_.push_back(obj);
}

void CollisionManager::unregisterObject(CollisionObject2D* obj) {
	if (!obj) {
		return;
	}
	objects_.erase(
		std::remove(
			objects_.begin(), objects_.end(), obj), 
			objects_.end()
	);
}

void CollisionManager::checkAllCollisions() {
	for (size_t i = 0; i < objects_.size(); ++i) {
		if (!objects_[i]->isCollisionEnabled()) {
			continue;
		}
		for (size_t j = i + 1; j < objects_.size(); ++j) {
			if (!objects_[j]->isCollisionEnabled()) {
				continue;
			}
			if (objects_[i]->checkCollision(*objects_[j])) {
				objects_[i]->onCollision(*objects_[j]);
				objects_[j]->onCollision(*objects_[i]);
			}
		}
	}
}

void CollisionManager::clear() {
	std::cout << "CollisionManager::clear : All collisionObject2Ds unregistered" << std::endl;
	objects_.clear();
}