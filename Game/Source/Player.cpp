#include "Player.h"
#include "SpriteRendererComponent.h"

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
}

void
Player::handleInput(const float deltaTime)
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
  {
    m_isMoving = true;
    m_movementDirection = { 0.0f, -1.0f }; // Move up
    // Rotate the sprite to face up
    m_transform.setRotation(m_transform.getScale().x < 0.0f ? 90.0f : 270.0f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
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
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
  {
    m_isMoving = true;
    m_movementDirection = { 0.0f, 1.0f }; // Move down
    m_transform.setRotation(m_transform.getScale().x < 0.0f ? 270.0f : 90.0f);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
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

  if (pOther->hasTag("Enemy")) {
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
