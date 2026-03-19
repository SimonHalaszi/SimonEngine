#ifndef COLLISION_MANAGER_HPP
#define COLLISION_MANAGER_HPP

#include <vector>
#include <algorithm>
#include <iostream>

class CollisionObject2D;

class CollisionManager {
	public:
		static CollisionManager& getInstance() {
			static CollisionManager instance;
			return instance;
		}

		void registerObject(CollisionObject2D* obj);
		void unregisterObject(CollisionObject2D* obj);

		void checkAllCollisions();

		void clear();

		CollisionManager(const CollisionManager&) = delete;
		CollisionManager& operator=(const CollisionManager&) = delete;
		CollisionManager(const CollisionManager&&) = delete;
		CollisionManager& operator=(const CollisionManager&&) = delete;

	private:
		CollisionManager() {}
		std::vector<CollisionObject2D*> objects_;
};

#endif

