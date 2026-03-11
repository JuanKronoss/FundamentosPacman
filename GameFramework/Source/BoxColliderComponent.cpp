/**
 * Includes
 */

#include "BoxColliderComponent.h"
#include "Actor.h"

BoxColliderComponent::BoxColliderComponent(const sf::FloatRect& bounds)
  : m_bounds(bounds)
{}

BoxColliderComponent::BoxColliderComponent(const sf::Vector2f& pos, const sf::Vector2f& size)
  : m_bounds(pos, size)
{}

void
BoxColliderComponent::update(const float /*deltaTime*/)
{
  if (m_pOwner && m_pOwner->isDirty()) {
    // Update the bounds' position based on the owner's transform
    const Transform& transform = m_pOwner->getTransform();
    m_bounds.position = transform.getPosition();
  }
}
