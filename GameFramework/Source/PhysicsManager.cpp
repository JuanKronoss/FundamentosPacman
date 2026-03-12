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
  Set<CollisionPair> currentCollisions{};
  size_t numActors = actors.size();
  for (size_t i = 0; i < numActors; ++i) {
    auto colliderA = actors[i]->getComponent<BoxColliderComponent>();
    if (colliderA.expired()) {
      continue; // Skip actors without a BoxColliderComponent
    }
    for (size_t j = i + 1; j < numActors; ++j) {
      auto colliderB = actors[j]->getComponent<BoxColliderComponent>();
      if (colliderB.expired()) {
        continue; // Skip actors without a BoxColliderComponent
      }
      // Check for collision
      Optional intersection = colliderA.lock()->getBounds().findIntersection(colliderB.lock()->getBounds());
      if (!intersection.has_value()) {
        continue; // No collision detected, skip to the next pair
      }
      CollisionPair pair{ actors[i], actors[j] };
      currentCollisions.insert(pair);
      bool existedLastFrame = m_prevCollisions.contains(pair);
      if (!existedLastFrame) {
        // Collision started this frame
        actors[i]->onCollisionEnter(actors[j], intersection.value());
        actors[j]->onCollisionEnter(actors[i], intersection.value());
      }
      else {
        // Collision continued from last frame
        actors[i]->onCollisionStay(actors[j], intersection.value());
        actors[j]->onCollisionStay(actors[i], intersection.value());
      }
    }
  }
  // Check for collisions that ended this frame
  for (const auto& pair : m_prevCollisions) {
    if (!currentCollisions.contains(pair)) {
      // Collision ended this frame
      pair.a->onCollisionExit(pair.b);
      pair.b->onCollisionExit(pair.a);
    }
  }
  m_prevCollisions = std::move(currentCollisions);
}
