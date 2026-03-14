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

  Ghost(const GhostType _type);
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
   * @brief Gets the score value awarded to the player when they eat this ghost while it's vulnerable.
   * @return The score value for this ghost.
   */
  inline uint64
  getScoreValue() const
  {
    return m_scoreValue;
  }

 private:

   GhostState m_state{ GhostState::Idle };
   GhostType m_type{ GhostType::Red };

   int m_ghostWidth = 60; // Width of the ghost sprite
   int m_ghostHeight = 60; // Height of the ghost sprite
   sf::IntRect m_normalSpriteRect; // Texture rectangle for the normal state
   sf::IntRect m_vulnerableSpriteRect; // Texture rectangle for the vulnerable state

   float m_speed = 150.0f; // Base speed of the ghost
   bool m_isVulnerable = false; // Indicates whether the ghost is currently vulnerable (can be eaten by the player)
   uint64 m_scoreValue = 100; // The score value awarded to the player when they eat this ghost while it's vulnerable

   bool m_isDead = false; // Indicates whether the ghost is currently dead (has been eaten by the player)
   float m_deadDuration = 5.0f; // Duration for which the ghost remains dead after being eaten by the player
   float m_deadTimer = 0.0f; // Timer to track how long the ghost has been dead
};
