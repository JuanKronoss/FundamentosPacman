/**
 * Includes
 */

#include "Ghost.h"
#include "SpriteRendererComponent.h"

Ghost::Ghost(const GhostType _type)
  : m_type(_type)
{
  uint32 imagePosX = static_cast<uint32>(m_type) * m_ghostWidth;
  sf::Vector2i imagePos(imagePosX, 0);
  sf::Vector2i imageSize(m_ghostWidth, m_ghostHeight);
  m_normalSpriteRect = sf::IntRect(imagePos, imageSize);
  m_vulnerableSpriteRect = sf::IntRect(sf::Vector2i(0, m_ghostHeight), imageSize); // The vulnerable sprite is located in the second row of the sprite sheet
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
Ghost::toggleVulnerability(const bool isVulnerable)
{
  m_isVulnerable = isVulnerable;
  m_isVulnerable ? m_state = GhostState::Fleeing : m_state = GhostState::Idle; // Set the ghost's state based on its vulnerability
  setProperSprite(); // Update the ghost's sprite to reflect its new state
}
