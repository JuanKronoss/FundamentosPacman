/**
 * Includes
 */

#include "PacDot.h"

PacDot::PacDot(const uint64 scoreValue)
  : m_scoreValue(scoreValue)
{}

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
