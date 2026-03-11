#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

/**
 * Forward declarations
 */

class Actor;

class DYNAMIC_LIBRARY_API Component
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

 protected:

  Actor* m_pOwner;

};
