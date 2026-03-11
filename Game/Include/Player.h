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
  
  float m_speed = 5.0f;
};
