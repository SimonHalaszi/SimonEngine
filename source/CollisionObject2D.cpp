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

void CollisionObject2D::setCollisionEnabled(bool enabled) {
    collisionEnabled_ = enabled;
    std::vector<std::unique_ptr<GameObject2D>>* children = getChildren();
    for (auto& child : *children) {
        CollisionObject2D* childCollider = dynamic_cast<CollisionObject2D*>(child.get());
        if (childCollider) {
            childCollider->setCollisionEnabled(enabled);
        }
    }
}

void CollisionObject2D::rootOnStart() {
    if (hasStarted_) {
        return;
    }
    GameObject2D::rootOnStart();
    collisionEnabled_ = true;
    registerToCollisionManager();
}

void CollisionObject2D::rootOnDestruction() {
    unregisterFromCollisionManager();
    GameObject2D::rootOnDestruction();
}

void CollisionObject2D::rootEstablishFields() {
    if (hasEstablishedFields_) {
        return;
    }
    hasEstablishedFields_ = true;

    attachIField(std::make_unique<StringField>("Name", &name_));
    attachIField(std::make_unique<StringField>("Tag", &tag_));
    attachIField(std::make_unique<Transform2DField>("Local Transform", &localTransform_));
    attachIField(std::make_unique<BoolField>("Collision", &collisionEnabled_));

    establishFields();

    std::vector<std::unique_ptr<GameObject2D>>* children = getChildren();
    for (auto& child : *children) {
        child->rootEstablishFields();
    }
}

void CollisionObject2D::registerToCollisionManager() {
    CollisionManager::getInstance().registerObject(this);
}

void CollisionObject2D::unregisterFromCollisionManager() {
    CollisionManager::getInstance().unregisterObject(this);
}