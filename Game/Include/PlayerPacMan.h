#pragma once

/**
 * Includes
 */

#include "PlayerBase.h"

/**
 * @brief Represents the player character in the game, which is a type of actor.
 */
class FRAMEWORK_EXPORT PlayerPacMan : public PlayerBase
{
 public:

  PlayerPacMan(const String& _name, const uint32 _windowWidth, const uint32 _windowHeight);
  PlayerPacMan(const uint32 _windowWidth, const uint32 _windowHeight);
  ~PlayerPacMan() = default;

  void
  update(const float deltaTime) override;

 private:
  
  /**
   * @brief Handles player input to move the character based on keyboard input.
   */
  void
  handleInput(const float deltaTime);

  /**
   * @brief Translates the player based on the current movement direction and speed,
   * taking into account the elapsed time since the last update.
   */
  void
  translate(const float deltaTime);

  /**
   * @brief Called when the actor collides with another actor.
   *
   * @param other The other actor involved in the collision.
   * @param intersection The intersection rectangle of the collision.
   */
  void
  onCollisionEnter(const WPtr<Actor> other, const sf::FloatRect& intersection) override;

  /**
   * @brief Called when the actor continues to collide with another actor in subsequent frames.
   * 
   * @param other The other actor involved in the collision.
   * @param intersection The intersection rectangle of the collision.
   */
  void
  onCollisionStay(const WPtr<Actor> other, const sf::FloatRect& intersection) override;

  /**
   * @brief Called when the actor stops colliding with another actor.
   * 
   * @param other The other actor involved in the collision.
   */
  void
  onCollisionExit(const WPtr<Actor> other) override;

  //float m_newTestFloat = 0.0f;


};
