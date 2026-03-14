/**
 * Includes
 */

#include "PacDot.h"

PacDot::PacDot(const String& _name, const uint64 _scoreValue)
  : Actor(_name), m_scoreValue(_scoreValue)
{}

PacDot::PacDot(const uint64 scoreValue)
  : m_scoreValue(scoreValue)
{}

void
PacDot::resetState()
{
  Actor::resetState(); // Call the base class resetState to reset components
  m_scoreValue = 10; // Reset the score value to its default value
}

void
PacDot::onCollisionEnter(const WPtr<Actor> other, const sf::FloatRect& intersection)
{
  if (other.expired()) {
    return; // Do not handle collision with expired actors
  }
  SPtr<Actor> pOther = other.lock();
  // Handle collision logic here
  if (pOther->hasTag("Player")) {
    markForDestruction();
  }
}
