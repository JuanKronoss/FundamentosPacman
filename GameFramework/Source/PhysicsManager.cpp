/**
 * Includes
 */

#include "PhysicsManager.h"
#include "Actor.h"
#include "Component.h"
#include "BoxColliderComponent.h"



void
PhysicsManager::handleCollisions(const Vector<SPtr<Actor>>& actors)
{
  for (const auto& actor : actors) {
    WPtr<BoxColliderComponent> colliderA = actor->getComponent<BoxColliderComponent>();
    if (colliderA.expired()) {
      continue; // Skip actors without a BoxColliderComponent
    }
    for (const auto& otherActor : actors) {
      if (actor == otherActor) {
        continue; // Skip self-collision
      }
      WPtr<BoxColliderComponent> colliderB = otherActor->getComponent<BoxColliderComponent>();
      if (colliderB.expired()) {
        continue; // Skip actors without a BoxColliderComponent
      }
      // Check for collision
      Optional intersection = colliderA.lock()->getBounds().findIntersection(colliderB.lock()->getBounds());
      if (intersection.has_value()) {
        // Collision detected, call onCollision for both actors
        actor->onCollision(otherActor, intersection.value());
        otherActor->onCollision(actor, intersection.value());
      }
    }
  }
}
