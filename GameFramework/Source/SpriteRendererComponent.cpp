#include "SpriteRendererComponent.h"
#include "Actor.h"

SpriteRendererComponent::SpriteRendererComponent(const sf::Texture& _texture, bool centerOrigin, const sf::IntRect& intRect)
  : m_texture(_texture), m_sprite(m_texture)
{
  if (centerOrigin) {
    setOriginAtCenter(intRect);
  }
}

SpriteRendererComponent::SpriteRendererComponent(const sf::Sprite& _sprite, bool centerOrigin, const sf::IntRect& intRect)
  : m_sprite(_sprite)
{
  if (centerOrigin) {
    setOriginAtCenter(intRect);
  }
}

void
SpriteRendererComponent::setOriginAtCenter(const sf::IntRect& intRect)
{
  sf::FloatRect bounds(intRect);

  if (intRect == sf::IntRect()) {
    // If no texture rect is provided, we use the entire texture
    bounds = m_sprite.getGlobalBounds();
  }
  float originX = std::floor(bounds.size.x * 0.5f); // Floor the origin to ensure it is a whole number, which can help prevent sub-pixel rendering issues
  float originY = std::floor(bounds.size.y * 0.5f);

  m_sprite.setOrigin(sf::Vector2f(originX, originY));
}

void
SpriteRendererComponent::setTextureRect(const sf::IntRect& rect, const bool setOrigin)
{
  m_sprite.setTextureRect(rect);
  if (setOrigin) {
    setOriginAtCenter(rect);
  }
}

void
SpriteRendererComponent::update(const float /*deltaTime*/)
{
  if (m_pOwner && m_pOwner->isDirty()) {
    // Update the sprite's position, rotation, and scale based on the owner's transform
    const Transform& transform = m_pOwner->getTransform();
    m_sprite.setPosition(transform.getPosition());
    m_sprite.setRotation(sf::degrees(transform.getRotation()));
    m_sprite.setScale(transform.getScale());
  }
}
