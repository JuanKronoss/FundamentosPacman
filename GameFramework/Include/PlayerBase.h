#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Actor.h"
#include "Event.h"

class PlayerBase: public Actor
{
 public:

  PlayerBase() = default;
  PlayerBase(const String& _name, const uint32 _windowWidth, const uint32 _windowHeight);
  PlayerBase(const uint32 _windowWidth, const uint32 _windowHeight);
  ~PlayerBase() = default;

  Event<> onDeath;
  Event<uint64> onScoreChange;
  Event<bool> onInvincibilityChanged;
  Event<bool> onForeverInvincibilitySet;

  /**
   * @brief Resets the player's state to its initial configuration, including position, movement direction, speed, invincibility status, and any other relevant properties.
   * This can be used to restart the player or return it to a known state after certain events, such as losing a life or restarting the game.
   */
  void
  resetState() override;

  /**
   * Mod Functions
   */

  /**
   * @brief Gets the player's current movement speed.
   */
  inline const float
  getSpeed() const
  {
    return m_speed;
  }

  /**
   * @brief Sets the player's movement speed.
   * @param _speed The new movement speed for the player.
   */
  void
  setSpeed(const float _speed);

  /**
   * @brief Toggles the player's invincibility state.
   *
   * @param isInvincible true to make the player invincible, false to make it vulnerable.
   */
  void
  toggleInvincibility(const bool isInvincible);

  /**
   * @brief Sets whether the player is permanently invincible.
   * If set to true, the player will remain invincible indefinitely until this flag is set to false.
   * This can be used for mods that grant permanent invincibility to the player.
   */
  void
  setForeverInvincibility(const bool isForeverInvincible);

protected:

  float m_speed = 200.0f;
  float m_invincibilityDuration = 5.0f; // Duration of invincibility in seconds
  float m_invincibilityTimer = 0.0f; // Timer to track the remaining invincibility time
  bool m_isMoving = false;
  bool m_isInvincible = false;
  bool m_isForeverInvincible = false; // A flag to indicate whether the player is permanently invincible, which can be set based on the mod information when the Player is created
  sf::Vector2f m_movementDirection = { 0.0f, 0.0f };
  uint32 m_windowWidth = 874; // Default window width, can be set through the constructor
  uint32 m_windowHeight = 980; // Default window height, can be set through the constructor

};
