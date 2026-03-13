#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Actor.h"

class PacDot: public Actor
{
 public:
  
  PacDot() = default;
  PacDot(const uint64 scoreValue);
  ~PacDot() = default;

  /**
   * @brief Called when the actor collides with another actor.
   *
   * @param other The other actor involved in the collision.
   * @param intersection The intersection rectangle of the collision.
   */
  void
  onCollisionEnter(const WPtr<Actor> other, const sf::FloatRect& intersection) override;

  /**
   * @brief Gets the score value that this score ball represents.
   * @return The score value that this score ball represents.
   */
  inline uint64
  getScoreValue() const
  {
    return m_scoreValue;
  }

  /**
   * @brief Sets the score value that this score ball represents.
   * @param scoreValue The new score value that this score ball represents.
   */
  inline void
  setScoreValue(const uint64 scoreValue)
  {
    m_scoreValue = scoreValue;
  }

 private:

  uint64 m_scoreValue = 10; // The score value that this score ball represents,

};
