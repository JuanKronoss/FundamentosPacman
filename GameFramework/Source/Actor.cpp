/**
 * Includes
 */

#include "Actor.h"
#include "Component.h"
#include "SpriteRendererComponent.h"
#include "BoxColliderComponent.h"

#include <SFML/Graphics.hpp>

Actor::Actor(const String& _name)
  : m_name(_name)
{}

Actor::Actor(const Transform& _iniTransform)
  : m_transform(_iniTransform)
{
  m_isDirty = true; // Mark the actor as dirty to ensure it gets updated in the first frame
}

Actor::Actor(const String& _name, const Transform& _iniTransform)
  : m_name(_name), m_transform(_iniTransform)
{
  m_isDirty = true; // Mark the actor as dirty to ensure it gets updated in the first frame
}

void
Actor::resetState()
{
  m_transform = m_initialTransform;
  m_isDirty = true; // Mark the actor as dirty to ensure it gets updated in the next frame
  for (const auto& component : m_components) {
    component->setActive(true); // Reactivate all components when resetting the actor's state
  }
}

void
Actor::addTag(const String& tag)
{
  // Check if the tag already exists before adding it
  if (find(m_tags.begin(), m_tags.end(), tag) != m_tags.end()) {
    return; // Tag already exists, do not add it again
  }
  m_tags.push_back(tag);
}

void
Actor::removeTag(const String& tag)
{
  auto it = find(m_tags.begin(), m_tags.end(), tag);
  if (it != m_tags.end()) {
    m_tags.erase(it);
  }
}

void
Actor::setDrawOrder(const int32 drawOrder) const
{
  // Get the SpriteRendererComponent of the actor and set its draw order
  WPtr<SpriteRendererComponent> spriteRenderer = getComponent<SpriteRendererComponent>();
  if (!spriteRenderer.expired()) {
    spriteRenderer.lock()->setDrawOrder(drawOrder);
  }
}

bool
Actor::hasTag(const String& tag) const
{
  return find(m_tags.begin(), m_tags.end(), tag) != m_tags.end();
}

void
Actor::update(const float deltaTime)
{
  // If the actor is not dirty, we can skip the update to save performance
  if (!m_isDirty) {
    return;
  }

  // Update all components of the actor
  for (const auto& component : m_components) {
    component->update(deltaTime);
  }

  m_isDirty = false;
}

void
Actor::setPosition(const float x, const float y)
{
  m_transform.setPosition(x, y);
  m_isDirty = true;
}

void
Actor::move(const float deltaX, const float deltaY)
{
  m_transform.move(deltaX, deltaY);
  m_isDirty = true;
}

void
Actor::onCollisionEnter(const WPtr<Actor> other, const sf::FloatRect& intersection)
{
  if (other.expired()) {
    return; // Do not handle collision with expired actors
  }  
}

void
Actor::onCollisionStay(const WPtr<Actor> other, const sf::FloatRect& intersection)
{
  if (other.expired()) {
    return; // Do not handle collision with expired actors
  }
}

void
Actor::onCollisionExit(const WPtr<Actor> other)
{
  if (other.expired()) {
    return; // Do not handle collision with expired actors
  }
}

bool
Actor::isVisible() const
{
  auto spriteRenderer = getComponent<SpriteRendererComponent>();
  if (!spriteRenderer.expired()) {
    return spriteRenderer.lock()->isActive();
  }
  return false; // If the actor doesn't have a SpriteRendererComponent, we consider it invisible
}

void
Actor::setVisible(const bool isVisible) const
{
  auto spriteRenderer = getComponent<SpriteRendererComponent>();
  if (!spriteRenderer.expired()) {
    spriteRenderer.lock()->setActive(isVisible);
  }
}

void
Actor::toggleActiveCollisions(const bool active) const
{
  auto boxCollider = getComponent<BoxColliderComponent>();
  if (!boxCollider.expired()) {
    boxCollider.lock()->setActive(active);
  }
}

