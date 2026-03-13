/**
 * Includes
 */

#include "ScoreBall.h"

ScoreBall::ScoreBall(const uint32 scoreValue)
  : m_scoreValue(scoreValue)
{}

void
ScoreBall::onCollisionEnter(const WPtr<Actor> other, const sf::FloatRect& intersection)
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
