#include "SpriteRendererComponent.h"
#include "Actor.h"

SpriteRendererComponent::SpriteRendererComponent(const sf::Texture& texture, const sf::IntRect rect)
  : m_sprite(texture/*, rect*/)
{}

SpriteRendererComponent::SpriteRendererComponent(const sf::Sprite& _sprite)
  : m_sprite(_sprite)
{}

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
