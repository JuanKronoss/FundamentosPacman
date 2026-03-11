#include "SpriteRendererComponent.h"
#include "Actor.h"

SpriteRendererComponent::SpriteRendererComponent(const sf::Texture& _texture, bool centerOrigin)
  : m_texture(_texture), m_sprite(m_texture)
{
  if (centerOrigin) {
    setOriginAtCenter();
  }
}

SpriteRendererComponent::SpriteRendererComponent(const sf::Sprite& _sprite, bool centerOrigin)
  : m_sprite(_sprite)
{
  if (centerOrigin) {
    setOriginAtCenter();
  }
}

void
SpriteRendererComponent::setOriginAtCenter()
{
  sf::FloatRect bounds = m_sprite.getLocalBounds();
  m_sprite.setOrigin(sf::Vector2f(bounds.size.x * 0.5f, bounds.size.y * 0.5f));
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

void
SpriteRendererComponent::flipX(const bool flipped)
{
  sf::Vector2f scale = m_sprite.getScale();
  scale.x = std::abs(scale.x) * (flipped ? -1.0f : 1.0f);
  m_sprite.scale(scale);
}
