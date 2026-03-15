#ifndef COLLISION_OBJECT2D_HPP
#define COLLISION_OBJECT2D_HPP

#include "GameObject2D.hpp"
#include "utilities.hpp"

// CollisionObject2D is a GameObject that will automatically register itsself to the CollisionManager.
// Everytime its AABB based on its Transform2D comes into contact with another its OnCollision method
// Will be called. Programmer defined logic can then be handled seperately.
class CollisionObject2D : public GameObject2D {
	public:
		CollisionObject2D() : GameObject2D() {}
		virtual ~CollisionObject2D();

		AABB getAABB() const;

		bool checkCollision(const CollisionObject2D& other) const;

		void rootOnStart() override final;
		void rootOnDestruction() override final;

	protected:
		virtual void onCollision(CollisionObject2D& other) = 0;

	private:
		void registerToCollisionManager();
		void unregisterFromCollisionManager();

		// CollisionManager will need to access protected fields
		friend class CollisionManager;
};

#endif