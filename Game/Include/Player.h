#pragma once

/**
 * Includes
 */

#include "Actor.h"

/**
 * @brief Represents the player character in the game, which is a type of actor.
 */
class Player: public Actor
{
 public:
  
  Player() = default;
  ~Player() = default;

  void
  update(const float deltaTime) override;

 private:
  
  /**
   * @brief Handles player input to move the character based on keyboard input.
   */
  void
  handleInput(const float deltaTime);

  /**
   * 
   */
  void
  translate(const float deltaTime);

  float m_speed = 2.5f;
  bool m_isMoving = false;
  sf::Vector2f m_movementDirection = { 0.0f, 0.0f };
};
