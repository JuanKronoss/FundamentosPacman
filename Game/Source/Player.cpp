#include "Player.h"
#include "SpriteRendererComponent.h"

#include <SFML/Graphics.hpp>

void Player::update(const float deltaTime)
{
  // Handle input and other actor-specific logic here
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
  {
    move(0.0f, -1.0f * m_speed * deltaTime);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
  {
    // Move left
    move(-1.0f * m_speed * deltaTime, 0.0f);
    // Flip the sprite horizontally to face left
    sf::Vector2f scale = m_transform.getScale();
    scale.x = std::abs(scale.x) * -1.0f; // Flip horizontally
    m_transform.setScale(scale.x, scale.y);

  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
  {
    move(0.0f, 1.0f * m_speed * deltaTime);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
  {
    // Move right
    move(1.0f * m_speed * deltaTime, 0.0f);
    // Flip the sprite horizontally to face right
    sf::Vector2f scale = m_transform.getScale();
    scale.x = std::abs(scale.x) * 1.0f; // Ensure facing right
    m_transform.setScale(scale.x, scale.y);
  }

  Actor::update(deltaTime); // Call the base class update to update components
}
