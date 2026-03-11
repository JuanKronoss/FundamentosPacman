#include "Transform.h"

void
Transform::setPosition(const float x, const float y)
{
  m_position.x = x;
  m_position.y = y;
}

void
Transform::move(const float deltaX, const float deltaY)
{
  m_position.x += deltaX;
  m_position.y += deltaY;
}

void
Transform::scale(const float scaleX, const float scaleY)
{
  m_scale.x *= scaleX;
  m_scale.y *= scaleY;
}

void
Transform::setScale(const float scaleX, const float scaleY)
{
  m_scale.x = scaleX;
  m_scale.y = scaleY;
}

void
Transform::setRotation(const float rotation)
{
  m_rotation = rotation;
}

void
Transform::rotate(const float deltaRotation)
{
  m_rotation += deltaRotation;
}
