#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

/**
 * Forward declarations
 */

class Actor;

class DYNAMIC_LIBRARY_API PhysicsManager
{
 public:
  
  PhysicsManager() = default;
  ~PhysicsManager() = default;

  /**
   * @brief Handles collisions between actors in the scene that have colliders.
   */
  void
  handleCollisions(const Vector<SPtr<Actor>>& actors);

};
