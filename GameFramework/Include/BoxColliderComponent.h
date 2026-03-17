#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Component.h"

#include <SFML/Graphics.hpp>

/**
 * @brief A component that represents a box collider for an actor, used for collision detection.
 */
class FRAMEWORK_EXPORT BoxColliderComponent: public Component
{
 public:

  BoxColliderComponent(const sf::FloatRect& bounds);
  BoxColliderComponent(const sf::Vector2f& pos, const sf::Vector2f& size);
  ~BoxColliderComponent() = default;

  /**
   * @brief Updates the box collider component.
   * 
   * @param deltaTime The time elapsed since the last update, in seconds.
   */
  void
  update(const float deltaTime) override;
  
  /**
   * @brief Gets the bounds of the box collider.
   */
  inline sf::FloatRect
  getBounds() const
  {
    return m_bounds;
  }

  /**
   * @brief Sets the bounds of the box collider.
   * @return The new bounds of the box collider.
   */
  inline void
  setBounds(const sf::FloatRect& bounds)
  {
    m_bounds = bounds;
  }

  /**
   * @brief Gets the position of the box collider.
   * @return The position of the box collider.
   */
  inline sf::Vector2f
  getPosition() const
  {
    return m_bounds.position;
  }

  /**
   * @brief Gets the size of the box collider.
   * @return The size of the box collider.
   */
  inline sf::Vector2f
  getSize() const
  {
    return m_bounds.size;
  }
  
 private:

  /**
   * @brief Sets the bounds of the box collider such that its origin is at its center.
   * This is useful for proper collision detection, as it allows the bounds to be positioned
   * based on the actor's transform without needing to manually adjust for the origin.
   */
  void
  setBoundsAtCenter();

  sf::FloatRect m_bounds;
};
