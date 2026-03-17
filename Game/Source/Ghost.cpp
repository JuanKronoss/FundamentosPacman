/**
 * Includes
 */

#include "Ghost.h"
#include "SpriteRendererComponent.h"
#include "BoxColliderComponent.h"

Ghost::Ghost(const GhostType _type)
  : m_type(_type)
{
  uint32 imagePosX = static_cast<uint32>(m_type) * m_ghostWidth;
  sf::Vector2i imagePos(imagePosX, 0);
  sf::Vector2i imageSize(m_ghostWidth, m_ghostHeight);
  m_normalSpriteRect = sf::IntRect(imagePos, imageSize);
  m_vulnerableSpriteRect = sf::IntRect(sf::Vector2i(0, m_ghostHeight), imageSize); // The vulnerable sprite is located in the second row of the sprite sheet

  switch (m_type)
  {
  case GhostType::Red:
    m_name = "RedGhost";
    break;
  case GhostType::Pink:
    m_name = "PinkGhost";
    break;
  case GhostType::Blue:
    m_name = "BlueGhost";
    break;
  case GhostType::Orange:
    m_name = "OrangeGhost";
    break;
  default:
    break;
  }
}

void
Ghost::resetState()
{
  Actor::resetState(); // Call the base class resetState to reset components
  m_state = GhostState::Idle;
  m_speed = 150.0f;
  m_isVulnerable = false;
  uint64 m_scoreValue = 100;
  m_isDead = false;
  float m_deadDuration = 5.0f;
  m_deadTimer = 0.0f;
  setProperSprite(); // Update the ghost's sprite to reflect its reset state
}

void
Ghost::setProperSprite()
{
  WPtr wpSpriteRenderer = getComponent<SpriteRendererComponent>();
  if (wpSpriteRenderer.expired()) {
    return; // If the ghost doesn't have a SpriteRendererComponent, we can't set the sprite, so we just return
  }
  SPtr<SpriteRendererComponent> spSpriteRenderer = wpSpriteRenderer.lock();
  switch (m_state) {
    case GhostState::Idle:
    case GhostState::Chasing:
      spSpriteRenderer->setTextureRect(m_normalSpriteRect);
      break;
    case GhostState::Fleeing:
      spSpriteRenderer->setTextureRect(m_vulnerableSpriteRect);
      break;
  }
  m_isDirty = true; // Mark the ghost as dirty to ensure it gets updated in the next frame
}

void
Ghost::update(const float deltaTime)
{
  if (m_isDead) {
    m_deadTimer += deltaTime;
    if (m_deadTimer >= m_deadDuration) {
      m_isDead = false; // Revive the ghost after the dead duration has passed
      if (!m_isForeverVulnerable) {
        toggleVulnerability(false); // Make the ghost invulnerable again when it revives
      }
      setVisible(true); // Make the ghost visible again when it revives
      toggleActiveCollisions(true); // Enable the ghost's collisions again when it revives
      m_deadTimer = 0.0f; // Reset the dead timer
    }
    return; // If the ghost is dead, we skip the rest of the update logic
  }

  Actor::update(deltaTime); // Call the base class update to update components
}

void
Ghost::toggleVulnerability(const bool isVulnerable)
{
  m_isVulnerable = isVulnerable;
  m_isVulnerable ? m_state = GhostState::Fleeing : m_state = GhostState::Idle; // Set the ghost's state based on its vulnerability
  setProperSprite(); // Update the ghost's sprite to reflect its new state
}

void
Ghost::onCollisionEnter(const WPtr<Actor> other, const sf::FloatRect& intersection)
{
  if (other.expired()) {
    return; // Do not handle collision with expired actors
  }

  SPtr<Actor> pOther = other.lock();
  if (pOther->hasTag("Player")) {
    if (m_isVulnerable) {
      m_isDead = true; // Mark the ghost as dead when it's eaten by the player
      setVisible(false); // Hide the ghost when it's eaten by the player
      toggleActiveCollisions(false); // Disable the ghost's collisions when it's eaten by the player
    }
  }
}

void
Ghost::setIsForeverVulnerable(const bool isForeverVulnerable)
{
  m_isForeverVulnerable = isForeverVulnerable;
  if (m_isForeverVulnerable) {
    toggleVulnerability(true); // If the ghost is set to be permanently vulnerable, we make it vulnerable immediately
  }
}
