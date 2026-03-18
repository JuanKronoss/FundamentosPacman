/**
 * Includes
 */

#include "Ghost.h"
#include "SpriteRendererComponent.h"
#include "BoxColliderComponent.h"

Ghost::Ghost(const GhostType _type, const uint32 _windowWidth, const uint32 _windowHeight, const sf::Vector2f& _iniPos)
  : m_type(_type), m_windowWidth(_windowWidth), m_windowHeight(_windowHeight), m_iniPos(_iniPos)
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
  setNewDirection(); // Set an initial random movement direction for the ghost
  m_movementDirection = m_nextMoveDir; // Initialize the movement direction to the first random direction
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
  translate(deltaTime); // Move the ghost based on its current speed and direction
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
Ghost::translate(const float deltaTime)
{
  if (m_isDead) {
    return; // Do not move the ghost if it's currently dead
  }
  if (m_willChangeDirection) {
    m_movementDirection = m_nextMoveDir; // Update the movement direction to the next desired direction
    m_willChangeDirection = false; // Reset the flag after changing direction
  }

  float moveMagnitude = m_speed * deltaTime;
  move(m_movementDirection.x * moveMagnitude, m_movementDirection.y * moveMagnitude);
  // Wrap the player around the screen edges
  sf::Vector2f position = m_transform.getPosition();
  if (position.x < 0.0f) {
    setPosition(static_cast<float>(m_windowWidth), position.y);
  }
  else if (position.x > static_cast<float>(m_windowWidth)) {
    setPosition(0.0f, position.y);
  }
  if (position.y < 0.0f) {
    setPosition(position.x, static_cast<float>(m_windowHeight));
  }
  else if (position.y > static_cast<float>(m_windowHeight)) {
    setPosition(position.x, 0.0f);
  }

}

void
Ghost::setNewDirection()
{
  int randomDir = rand() % 4; // Randomly choose a direction: 0 = up, 1 = down, 2 = left, 3 = right
  switch (randomDir) {
  case 0:
    m_nextMoveDir = { 0.0f, -1.0f }; // Move up
    break;
  case 1:
    m_nextMoveDir = { 0.0f, 1.0f }; // Move down
    break;
  case 2:
    m_nextMoveDir = { -1.0f, 0.0f }; // Move left
    break;
  case 3:
    m_nextMoveDir = { 1.0f, 0.0f }; // Move right
    break;
  }
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
      toggleActiveCollisions(false); // Disable the ghost's collisions when it's eaten by the player
      setVisible(false); // Hide the ghost when it's eaten by the player
      setPosition(m_iniPos.x, m_iniPos.y); // Move the ghost back to its initial position when it's eaten by the player
      // Force immidiate update of the ghost's components to avoid visual glitches and collision issues when the ghost respawns
      auto wpSpriteRenderer = getComponent<SpriteRendererComponent>();
      if (!wpSpriteRenderer.expired()) {
        wpSpriteRenderer.lock()->update(0.0f);
      }
      auto wpBoxCollider = getComponent<BoxColliderComponent>();
      if (!wpBoxCollider.expired()) {
        wpBoxCollider.lock()->update(0.0f);
      }
    }
  }

  if (pOther->hasTag("Intersection")) {
    sf::Vector2f otherPos(pOther->getTransform().getPosition());
    // Compute a random next movement direction
    setNewDirection();

    // Move towards the center of the intersection to allow for smoother direction changes at intersections
    move((otherPos.x - m_transform.getPosition().x) * 0.5f, (otherPos.y - m_transform.getPosition().y) * 0.5f);
    m_willChangeDirection = true;
  }

  if (pOther->hasTag("Wall")) {
    // Prevent the ghost from moving further into the wall based on the intersection rectangle
    if (intersection.size.x < intersection.size.y) {
      // Collision is more horizontal, adjust the player's position on the x-axis
      if (m_transform.getPosition().x < pOther->getTransform().getPosition().x) {
        setPosition(m_transform.getPosition().x - intersection.size.x, m_transform.getPosition().y);
      }
      else {
        setPosition(m_transform.getPosition().x + intersection.size.x, m_transform.getPosition().y);
      }
    }
    else {
      // Collision is more vertical, adjust the player's position on the y-axis
      if (m_transform.getPosition().y < pOther->getTransform().getPosition().y) {
        setPosition(m_transform.getPosition().x, m_transform.getPosition().y - intersection.size.y);
      }
      else {
        setPosition(m_transform.getPosition().x, m_transform.getPosition().y + intersection.size.y);
      }
    }

    // If the ghost collides with a wall, we need to change its direction immediately to prevent it from getting stuck
    setNewDirection();
    m_willChangeDirection = true; // Set the flag to change direction in the next update
  }
}

void
Ghost::onCollisionStay(const WPtr<Actor> other, const sf::FloatRect& intersection)
{
  SPtr<Actor> pOther = other.lock();

  if (pOther->hasTag("Wall")) {
    // Prevent the ghost from moving further into the wall based on the intersection rectangle
    if (intersection.size.x < intersection.size.y) {
      // Collision is more horizontal, adjust the player's position on the x-axis
      if (m_transform.getPosition().x < pOther->getTransform().getPosition().x) {
        setPosition(m_transform.getPosition().x - intersection.size.x, m_transform.getPosition().y);
      }
      else {
        setPosition(m_transform.getPosition().x + intersection.size.x, m_transform.getPosition().y);
      }
    }
    else {
      // Collision is more vertical, adjust the player's position on the y-axis
      if (m_transform.getPosition().y < pOther->getTransform().getPosition().y) {
        setPosition(m_transform.getPosition().x, m_transform.getPosition().y - intersection.size.y);
      }
      else {
        setPosition(m_transform.getPosition().x, m_transform.getPosition().y + intersection.size.y);
      }
    }
    // If the ghost collides with a wall, we need to change its direction immediately to prevent it from getting stuck
    setNewDirection();
    m_willChangeDirection = true; // Set the flag to change direction in the next update

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
