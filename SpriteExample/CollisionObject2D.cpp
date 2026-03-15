#include "CollisionObject2D.hpp"
#include "CollisionManager.hpp"

CollisionObject2D::~CollisionObject2D() {
    unregisterFromCollisionManager();
}

AABB CollisionObject2D::getAABB() const {
    Transform2D worldTrans = getWorldTransform();
    return AABB{
        {worldTrans.position.x - worldTrans.scale.x, worldTrans.position.y - worldTrans.scale.y},
        {worldTrans.position.x + worldTrans.scale.x, worldTrans.position.y + worldTrans.scale.y}
    };
}

bool CollisionObject2D::checkCollision(const CollisionObject2D& other) const {
    return checkAABBCollision(getAABB(), other.getAABB());
}

void CollisionObject2D::rootOnStart() {
    GameObject2D::rootOnStart();
    registerToCollisionManager();
}

void CollisionObject2D::rootOnDestruction() {
    unregisterFromCollisionManager();
    GameObject2D::rootOnDestruction();
}

void CollisionObject2D::registerToCollisionManager() {
    CollisionManager::getInstance().registerObject(this);
}

void CollisionObject2D::unregisterFromCollisionManager() {
    CollisionManager::getInstance().unregisterObject(this);
}