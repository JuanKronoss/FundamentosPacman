#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

/**
 * Forward declarations
 */

class Actor;

class Component
{
 public:
    
  Component() = default;
  virtual ~Component() = default;

  /**
   * @brief Updates the component.
   * 
   * @param deltaTime The time elapsed since the last update, in seconds.
   */
  virtual void
  update(const float deltaTime) = 0;

  /**
   * @brief Sets the owner of the component.
   * 
   * @param owner A weak pointer to the actor that owns this component.
   */
  inline void
  setOwner(Actor* owner)
  {
    m_pOwner = owner;
  }

  /**
   * @brief Return whether the component is active and should be updated.
   */
  inline bool
  isActive() const
  {
    return m_isActive;
  }

  /**
   * @brief Sets whether the component is active and should be updated.
   * @param isActive true to make the component active, false to make it inactive.
   */
  inline void
  setActive(const bool isActive)
  {
    m_isActive = isActive;
  }

 protected:

  Actor* m_pOwner;
  bool m_isActive = true; // Whether the component is active and should be updated

};
