#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Actor.h"

enum class GhostType
{
  Red,
  Pink,
  Blue,
  Orange
};

class Ghost: public Actor
{
 public:

  Ghost(const GhostType _type, const uint32 _windowWidth, const uint32 _windowHeight, const sf::Vector2f& _iniPos);
  ~Ghost() = default;

  enum class GhostState
  {
    Idle,
    Chasing,
    Fleeing
  };

  /**
   * @brief Resets the ghost's state to its initial configuration, including position, rotation, scale, and any other relevant properties.
   * This can be used to restart the ghost or return it to a known state after certain events.
   */
  void
  resetState() override;

  /**
   * @brief Sets the appropriate sprite for the ghost based on its current state.
   */
  void
  setProperSprite();

  /**
   * 
   */
  void
  update(const float deltaTime) override;

  /**
   * @brief Translates the ghost based on the current movement direction and speed,
   * taking into account the elapsed time since the last update.
   */
  void
  translate(const float deltaTime);

  void
  setNewDirection();

  /**
   * @brief Toggles the ghost's vulnerability state, which determines whether it can be eaten by the player.
   *
   * @param isVulnerable true to make the ghost vulnerable (can be eaten by the player), false to make it invulnerable.
   */
  void
  toggleVulnerability(const bool isVulnerable);

  /**
   * @brief Called when the ghost collides with another actor.
   *
   * @param other The other actor involved in the collision.
   * @param intersection The intersection rectangle of the collision.
   */
  void
  onCollisionEnter(const WPtr<Actor> other, const sf::FloatRect& intersection) override;

  /**
   * @brief Called when the ghost continues to collide with another actor in subsequent frames.
   * 
   * @param other The other actor involved in the collision.
   * @param intersection The intersection rectangle of the collision.
   */
  void
  onCollisionStay(const WPtr<Actor> other, const sf::FloatRect& intersection) override;

  /**
   * @brief Gets the score value awarded to the player when they eat this ghost while it's vulnerable.
   * @return The score value for this ghost.
   */
  inline uint64
  getScoreValue() const
  {
    return m_scoreValue;
  }

  /**
   * @brief Sets the score value awarded to the player when they eat this ghost while it's vulnerable.
   * @param scoreValue The new score value for this ghost.
   */
  inline void
  setScoreValue(const uint64 scoreValue)
  {
    m_scoreValue = scoreValue;
  }

  /**
   * @brief Checks if the ghost is currently vulnerable, meaning it can be eaten by the player.
   * @return true if the ghost is vulnerable, false otherwise.
   */
  inline bool
  isVulnerable() const
  {
    return m_isVulnerable;
  }

  /**
   * @brief Checks if the ghost is permanently vulnerable, meaning it can always be eaten by the player regardless of its current state.
   * This can be used for special conditions or mods that make the ghost always vulnerable.
   * @return true if the ghost is permanently vulnerable, false otherwise.
   */
  inline bool
  isForeverVulnerable() const
  {
    return m_isForeverVulnerable;
  }

  /**
   * @brief Sets whether the ghost is permanently vulnerable, meaning it can always be eaten by the player regardless of its current state.
   * This can be used for special conditions or mods that make the ghost always vulnerable.
   * @param isForeverVulnerable true to make the ghost permanently vulnerable, false to make it vulnerable based on its current state.
   */
  void
  setIsForeverVulnerable(const bool isForeverVulnerable);

 private:

   GhostState m_state{ GhostState::Idle };
   GhostType m_type{ GhostType::Red };

   uint32 m_windowWidth = 874; // The width of the game window, used for wrapping the ghost around the edges
   uint32 m_windowHeight = 980; // The height of the game window, used for wrapping the ghost around the edges
   sf::Vector2f m_iniPos; // The initial position of the ghost, used for resetting its state

   int m_ghostWidth = 38; // Width of the ghost sprite
   int m_ghostHeight = 38; // Height of the ghost sprite
   sf::IntRect m_normalSpriteRect; // Texture rectangle for the normal state
   sf::IntRect m_vulnerableSpriteRect; // Texture rectangle for the vulnerable state

   float m_speed = 150.0f; // Base speed of the ghost
   bool m_isForeverVulnerable = false; // Indicates whether the ghost is permanently vulnerable (e.g., due to a mod or special condition)
   bool m_isVulnerable = false; // Indicates whether the ghost is currently vulnerable (can be eaten by the player)
   uint64 m_scoreValue = 100; // The score value awarded to the player when they eat this ghost while it's vulnerable

   bool m_isDead = false; // Indicates whether the ghost is currently dead (has been eaten by the player)
   float m_deadDuration = 5.0f; // Duration for which the ghost remains dead after being eaten by the player
   float m_deadTimer = 0.0f; // Timer to track how long the ghost has been dead

   sf::Vector2f m_movementDirection = { 0.0f, 0.0f };
   sf::Vector2f m_nextMoveDir = { 0.0f, 1.0f };
   bool m_willChangeDirection = false; // A flag to indicate whether the ghost will change direction at the next frame
};
