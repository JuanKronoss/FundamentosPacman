#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

/**
 * Forward declarations
 */

class Actor;

class DYNAMIC_LIBRARY_API Scene
{
 public:

  Scene() = default;
  ~Scene() = default;

  /**
   * @brief Adds an actor to the scene.
   * 
   * @param actor A weak pointer to the actor to add to the scene.
   */
  void
  addActor(const WPtr<Actor>& actor);

  /**
   * @brief Removes an actor from the scene.
   * 
   * @param actor A weak pointer to the actor to remove from the scene.
   */
  void
  removeActor(const WPtr<Actor>& actor);

  /**
   * @brief Gets the actors in the scene sorted by their draw order.
   * 
   * @return A reference to a vector of shared pointers to the actors in the scene, sorted by their draw order.
   */
  Vector<SPtr<Actor>>&
  getActorsInDrawingOrder() const;

  /**
   * @brief Gets the actors in the scene.
   */
  inline const Vector<SPtr<Actor>>&
  getActors() const
  {
    return m_pActors;
  }

 private:

  Vector<SPtr<Actor>> m_pActors;
};
