#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Module.h"

/**
 * Forward declarations
 */

class Actor;

struct CollisionPair
{
  SPtr<Actor> a;
  SPtr<Actor> b;

  bool operator<(const CollisionPair& other) const
  {
    return tie(a, b) < tie(other.a, other.b);
  }
};

/**
 * @brief Manages the physics and collision detection for actors in the scene.
 */
class PhysicsManager : public Module<PhysicsManager>
{
 public:

  PhysicsManager() = default;
  ~PhysicsManager() = default;

  /**
   * @brief Handles collisions between actors in the scene that have colliders.
   */
  void
  handleCollisions(const Vector<SPtr<Actor>>& actors);

 private:

  Set<CollisionPair> m_prevCollisions;

};
