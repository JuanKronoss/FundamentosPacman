#pragma once

/**
 * Includes
 */

#include "Actor.h"
#include "Event.h"

/**
 * @brief Represents the player character in the game, which is a type of actor.
 */
class Player: public Actor
{
 public:
  
  Player(WPtr<sf::RenderWindow> pWindow);
  ~Player() = default;

  void
  update(const float deltaTime) override;

  Event<> onDeath;
  Event<uint64> onScoreChange;
  Event<bool> onInvincibilityChanged;

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
   * @brief Toggles the player's invincibility state.
   *
   * @param isInvincible true to make the player invincible, false to make it vulnerable.
   */
  void
  toggleInvincibility(const bool isInvincible);

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

  SPtr<sf::RenderWindow> m_window; // Reference to the game window for wrapping the player around the screen
  float m_speed = 200.0f;
  float m_invincibilityDuration = 5.0f; // Duration of invincibility in seconds
  float m_invincibilityTimer = 0.0f; // Timer to track the remaining invincibility time
  bool m_isMoving = false;
  bool m_isInvincible = false;
  sf::Vector2f m_movementDirection = { 0.0f, 0.0f };

};
