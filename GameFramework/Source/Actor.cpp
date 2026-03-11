/**
 * Includes
 */

#include "Actor.h"
#include "Component.h"
#include "SpriteRendererComponent.h"

#include <SFML/Graphics.hpp>

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
Actor::onCollision(const WPtr<Actor> other, const sf::FloatRect& intersection)
{
  if (other.expired()) {
    return; // Do not handle collision with expired actors
  }  
}
