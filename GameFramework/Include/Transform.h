#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "SFML/Graphics.hpp"

/**
 * @brief Represents the position, rotation, and scale of an Actor in the game world.
 */
class DYNAMIC_LIBRARY_API Transform
{
 public:
  
  Transform() = default;
  ~Transform() = default;
  
  /**
   * @brief Sets the position of the transform.
   * 
   * @param x The x-coordinate of the new position.
   * @param y The y-coordinate of the new position.
   */
  void
  setPosition(const float x, const float y);
  
  /**
   * @brief Moves the transform by the specified amounts.
   * 
   * @param deltaX The amount to move the transform along the x-axis.
   * @param deltaY The amount to move the transform along the y-axis.
   */
  void
  move(const float deltaX, const float deltaY);
  
  /**
   * @brief Sets the scale of the transform.
   * 
   * @param scaleX The scale factor along the x-axis.
   * @param scaleY The scale factor along the y-axis.
   */
  void
  setScale(const float scaleX, const float scaleY);

  /**
   * @brief Sets the rotation of the transform.
   * 
   * @param rotation The new rotation in degrees.
   */
  void
  setRotation(const float rotation);

  /**
   * @brief Rotates the transform by the specified amount.
   * 
   * @param deltaRotation The amount to rotate the transform, in degrees.
   */
  void
  rotate(const float deltaRotation);

  /**
   * @brief Resets the transform to its default state (position at origin, no rotation, and scale of 1).
   */
  inline void
  reset()
  {
    m_position = { 0.0f, 0.0f };
    m_scale = { 1.0f, 1.0f };
    m_rotation = 0.0f;
  }

  /**
   * @brief Gets the position of the transform.
   */
  inline sf::Vector2f
  getPosition() const
  {
    return m_position;
  }

  /**
   * @brief Gets the scale of the transform.
   */
  inline sf::Vector2f
  getScale() const
  {
    return m_scale;
  }

  /**
   * @brief Gets the rotation of the transform.
   */
  inline float
  getRotation() const
  {
    return m_rotation;
  }

 private:
  
  sf::Vector2f m_position{ 0.0f, 0.0f };
  sf::Vector2f m_scale{ 1.0f, 1.0f };
  float m_rotation{ 0.0f };
};
