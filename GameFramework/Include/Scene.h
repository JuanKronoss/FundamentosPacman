#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

/**
 * Forward declarations
 */

class Actor;

/**
 * @brief Represents a scene in the game, which contains actors and manages their lifecycle.
 */
class Scene
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
   * @brief Sets the visibility of all actors in the scene.
   * 
   * @param isVisible true to make all actors visible, false to make them invisible.
   */
  void
  setAllActorsVisibility(const bool isVisible);

  /**
   * @brief Gets the actors in the scene that are currently visible.
   * 
   * @return A vector of shared pointers to the actors in the scene that are currently visible.
   */
  Vector<SPtr<Actor>>
  getVisibleActors() const;

  /**
   * @brief Gets the actors in the scene sorted by their draw order.
   * 
   * @param onlyVisible If true, only returns actors that are currently visible. If false, returns all actors regardless of visibility.
   * @return A vector of shared pointers to the actors in the scene, sorted by their draw order.
   */
  Vector<SPtr<Actor>>
  getActorsInDrawingOrder(const bool onlyVisible = true) const;

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
