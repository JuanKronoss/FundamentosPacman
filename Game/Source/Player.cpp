#include "Player.h"
#include "SpriteRendererComponent.h"
#include "ScoreBall.h"

#include <SFML/Graphics.hpp>

Player::Player(WPtr<sf::RenderWindow> pWindow)
{
  if (pWindow.expired()) {
    throw std::invalid_argument("Player constructor received an expired window pointer");
  }
  m_window = pWindow.lock();
}

void Player::update(const float deltaTime)
{
  handleInput(deltaTime); // Handle player input to move the character

  Actor::update(deltaTime); // Call the base class update to update components

  // Handle invincibility timer
  if (m_isInvincible) {
    m_invincibilityTimer += deltaTime;
    if (m_invincibilityTimer >= m_invincibilityDuration) {
      m_isInvincible = false; // End invincibility when the timer runs out
      m_invincibilityTimer = 0.0f; // Reset the timer
      onInvincibilityDeactivate.invoke(); // Trigger the invincibility deactivate event
    }
  }
}

void
Player::handleInput(const float deltaTime)
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
Player::translate(const float deltaTime)
{
  if (m_isMoving) {
    float moveMagnitude = m_speed * deltaTime;
    move(m_movementDirection.x * moveMagnitude, m_movementDirection.y * moveMagnitude);
    // Wrap the player around the screen edges
    sf::Vector2f position = getTransform().getPosition();
    sf::Vector2u windowSize = m_window->getSize();
    if (position.x < 0.0f) {
      setPosition(static_cast<float>(windowSize.x), position.y);
    }
    else if (position.x > windowSize.x) {
      setPosition(0.0f, position.y);
    }
    if (position.y < 0.0f) {
      setPosition(position.x, static_cast<float>(windowSize.y));
    }
    else if (position.y > windowSize.y) {
      setPosition(position.x, 0.0f);
    }
  }
}

void
Player::onCollisionEnter(const WPtr<Actor> other, const sf::FloatRect& intersection)
{
  if (other.expired()) {
    return; // Do not handle collision with expired actors
  }
  SPtr<Actor> pOther = other.lock();
  // Handle collision logic here

  if (pOther->hasTag("Wall")) {
    m_isMoving = false; // Stop the player from moving when colliding with a wall
  }

  if (pOther->hasTag("Score")) {
    auto scoreBall = std::dynamic_pointer_cast<ScoreBall>(pOther);
    if (scoreBall) {
      onScoreChange.invoke(scoreBall->getScoreValue()); // Trigger the score change event with the score value from the ScoreBall
    }
  }

  if (pOther->hasTag("PowerUp")) {
    m_isInvincible = true; // Make the player invincible when colliding with a power-up
    m_invincibilityTimer = 0.0f; // Reset the invincibility timer
    onInvincibilityActivate.invoke(); // Trigger the invincibility activate event
  }

  if (pOther->hasTag("Enemy")) {

    if (m_isInvincible) {
      return;
    }
    // If the player collides with an enemy, trigger the onDeath event
    onDeath.invoke();
  }
}

void
Player::onCollisionStay(const WPtr<Actor> other, const sf::FloatRect& intersection)
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
      if (getTransform().getPosition().x < pOther->getTransform().getPosition().x) {
        setPosition(getTransform().getPosition().x - intersection.size.x, getTransform().getPosition().y);
      }
      else {
        setPosition(getTransform().getPosition().x + intersection.size.x, getTransform().getPosition().y);
      }
    }
    else {
      // Collision is more vertical, adjust the player's position on the y-axis
      if (getTransform().getPosition().y < pOther->getTransform().getPosition().y) {
        setPosition(getTransform().getPosition().x, getTransform().getPosition().y - intersection.size.y);
      }
      else {
        setPosition(getTransform().getPosition().x, getTransform().getPosition().y + intersection.size.y);
      }
    }

  }
}

void
Player::onCollisionExit(const WPtr<Actor> other)
{
  if (other.expired()) {
    return; // Do not handle collision with expired actors
  }
  SPtr<Actor> pOther = other.lock();
  // Handle logic for when the collision ends if needed
}
