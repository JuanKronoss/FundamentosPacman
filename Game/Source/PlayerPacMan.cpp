#include "PlayerPacMan.h"
#include "SpriteRendererComponent.h"
#include "PacDot.h"
#include "Ghost.h"

#include <SFML/Graphics.hpp>

PlayerPacMan::PlayerPacMan(const String& _name, const uint32 _windowWidth, const uint32 _windowHeight)
  : PlayerBase(_name, _windowWidth, _windowHeight)
{}

PlayerPacMan::PlayerPacMan(const uint32 _windowWidth, const uint32 _windowHeight)
  : PlayerBase(_windowWidth, _windowHeight)
{}

void PlayerPacMan::update(const float deltaTime)
{
  handleInput(deltaTime); // Handle player input to move the character

  Actor::update(deltaTime); // Call the base class update to update components

  // Handle invincibility timer
  if (m_isInvincible && !m_isForeverInvincible) {
    m_invincibilityTimer += deltaTime;
    if (m_invincibilityTimer >= m_invincibilityDuration) {
      toggleInvincibility(false); // Toggle invincibility off when the timer exceeds the duration
    }
  }
}

void
PlayerPacMan::handleInput(const float deltaTime)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
  {
    m_isMoving = true;
    m_movementDirection = { 0.0f, -1.0f }; // Move up
    // Rotate the sprite to face up
    m_transform.setRotation(m_transform.getScale().x < 0.0f ? 90.0f : 270.0f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
  {
    m_isMoving = true;
    m_movementDirection = { -1.0f, 0.0f }; // Move left
    // Flip the sprite horizontally to face left
    m_transform.setRotation(0.0f);
    sf::Vector2f scale = m_transform.getScale();
    if (scale.x > 0.0f) {
      m_transform.scale(-scale.x, scale.y);
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
  {
    m_isMoving = true;
    m_movementDirection = { 0.0f, 1.0f }; // Move down
    m_transform.setRotation(m_transform.getScale().x < 0.0f ? 270.0f : 90.0f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
  {
    m_isMoving = true;
    m_movementDirection = { 1.0f, 0.0f }; // Move right
    // Flip the sprite horizontally to face right
    m_transform.setRotation(0.0f);
    sf::Vector2f scale = m_transform.getScale();
    if (scale.x < 0.0f) {
      m_transform.scale(scale.x, scale.y);
    }
  }
  translate(deltaTime); // Move the player based on the input
}

void
PlayerPacMan::translate(const float deltaTime)
{

  if (m_isMoving) {
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
}

void
PlayerPacMan::onCollisionEnter(const WPtr<Actor> other, const sf::FloatRect& intersection)
{
  if (other.expired()) {
    return; // Do not handle collision with expired actors
  }
  SPtr<Actor> pOther = other.lock();
  // Handle collision logic here

  if (pOther->hasTag("Wall")) {
    m_isMoving = false; // Stop the player from moving when colliding with a wall
  }

  if (pOther->hasTag("PacDot")) {
    auto pPacDot = dynamic_pointer_cast<PacDot>(pOther);
    if (pPacDot) {
      onScoreChange.invoke(pPacDot->getScoreValue()); // Trigger the score change event with the score value from the PacDot
    }
    if (pOther->hasTag("PowerPellet")) {
      toggleInvincibility(true); // Make the player invincible when colliding with a power-up
    }
  }

  if (pOther->hasTag("Enemy")) {

    if (m_isInvincible) {
      auto pGhost = dynamic_pointer_cast<Ghost>(pOther);
      if (pGhost) {
        onScoreChange.invoke(pGhost->getScoreValue()); // Trigger the score change event with the score value from the Ghost
      }
      return;
    }
    // If the player collides with an enemy, trigger the onDeath event
    onDeath.invoke();
  }
}

void
PlayerPacMan::onCollisionStay(const WPtr<Actor> other, const sf::FloatRect& intersection)
{
  if (other.expired()) {
    return; // Do not handle collision with expired actors
  }
  SPtr<Actor> pOther = other.lock();
  // Handle ongoing collision logic here if needed
  if (pOther->hasTag("Wall")) {
    m_isMoving = false; // Stop the player from moving when colliding with a wall
    // Prevent the player from moving further into the wall based on the intersection rectangle
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

  }
}

void
PlayerPacMan::onCollisionExit(const WPtr<Actor> other)
{
  if (other.expired()) {
    return; // Do not handle collision with expired actors
  }
  SPtr<Actor> pOther = other.lock();
  // Handle logic for when the collision ends if needed
}
