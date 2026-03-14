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
  
  Player(const String& _name, const uint32 _windowWidth, const uint32 _windowHeight);
  Player(const uint32 _windowWidth, const uint32 _windowHeight);
  ~Player() = default;

  /**
   * @brief Resets the player's state to its initial configuration, including position, movement direction, speed, invincibility status, and any other relevant properties.
   * This can be used to restart the player or return it to a known state after certain events, such as losing a life or restarting the game.
   */
  void
  resetState() override;

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

  float m_speed = 200.0f;
  float m_invincibilityDuration = 5.0f; // Duration of invincibility in seconds
  float m_invincibilityTimer = 0.0f; // Timer to track the remaining invincibility time
  bool m_isMoving = false;
  bool m_isInvincible = false;
  sf::Vector2f m_movementDirection = { 0.0f, 0.0f };
  uint32 m_windowWidth = 800; // Default window width, can be set through the constructor
  uint32 m_windowHeight = 900; // Default window height, can be set through the constructor
};
