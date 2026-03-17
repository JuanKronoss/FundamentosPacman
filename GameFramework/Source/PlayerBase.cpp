/**
 * Includes
 */

#include "PlayerBase.h"

PlayerBase::PlayerBase(const String& _name, const uint32 _windowWidth, const uint32 _windowHeight)
  : Actor(_name), m_windowWidth(_windowWidth), m_windowHeight(_windowHeight)
{}

PlayerBase::PlayerBase(const uint32 _windowWidth, const uint32 _windowHeight)
  : Actor(), m_windowWidth(_windowWidth), m_windowHeight(_windowHeight)
{}

void
PlayerBase::resetState()
{
  Actor::resetState(); // Call the base class resetState to reset components
  m_speed = 200.0f;
  m_invincibilityDuration = 5.0f; // Duration of invincibility in seconds
  m_invincibilityTimer = 0.0f; // Timer to track the remaining invincibility time
  m_isMoving = false;
  m_isInvincible = false;
  m_movementDirection = { 0.0f, 0.0f };
}

void
PlayerBase::toggleInvincibility(const bool isInvincible)
{
  m_isInvincible = isInvincible;
  m_invincibilityTimer = 0.0f; // Reset the invincibility timer when toggling invincibility
  onInvincibilityChanged.invoke(isInvincible); // Trigger the invincibility changed event with the new invincibility state
}

void
PlayerBase::setSpeed(const float _speed)
{
  m_speed = _speed;
}

void
PlayerBase::setForeverInvincibility(const bool isForeverInvincible)
{
  m_isForeverInvincible = isForeverInvincible;
  if (isForeverInvincible) {
    toggleInvincibility(true); // If the player is set to be permanently invincible, we also need to toggle invincibility on immediately
    onForeverInvincibilitySet.invoke(true); // Trigger the forever invincibility set event with true to indicate that the player is now permanently invincible
  }
}
