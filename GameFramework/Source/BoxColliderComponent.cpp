/**
 * Includes
 */

#include "BoxColliderComponent.h"
#include "Actor.h"

BoxColliderComponent::BoxColliderComponent(const sf::FloatRect& bounds)
  : m_bounds(bounds)
{
  // Set the origin of the bounds to its center for proper collision detection
  setBoundsAtCenter();
}

BoxColliderComponent::BoxColliderComponent(const sf::Vector2f& pos, const sf::Vector2f& size)
  : m_bounds(pos, size)
{
  // Set the origin of the bounds to its center for proper collision detection
  setBoundsAtCenter();
}

void
BoxColliderComponent::setBoundsAtCenter()
{
  m_bounds.position.x -= m_bounds.size.x * 0.5f;
  m_bounds.position.y -= m_bounds.size.y * 0.5f;
}

void
BoxColliderComponent::update(const float /*deltaTime*/)
{
  if (m_pOwner && m_pOwner->isDirty()) {
    // Update the bounds' position based on the owner's transform
    const Transform& transform = m_pOwner->getTransform();
    m_bounds.position = transform.getPosition();
    // Since the origin of the bounds is at its center, we need to adjust the position to account for that
    setBoundsAtCenter();
  }
}
