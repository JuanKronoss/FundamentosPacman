#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Component.h"

#include <SFML/Graphics.hpp>

/**
 * @brief A component that handles rendering a sprite for an actor.
 */
class SpriteRendererComponent: public Component
{
 public:

  SpriteRendererComponent(const sf::Texture& _texture, bool centerOrigin = true);
  SpriteRendererComponent(const sf::Sprite& _sprite, bool centerOrigin = true);
  ~SpriteRendererComponent() = default;
  
  /**
   * @brief Updates the sprite renderer component.
   * 
   * @param deltaTime The time elapsed since the last update, in seconds.
   */
  void
  update(const float deltaTime) override;

  /**
   * @brief Gets the sprite associated with this component.
   * @return A reference to the sprite associated with this component.
   */
  inline const sf::Sprite&
  getSprite() const
  {
    return m_sprite;
  }

  /**
   * @brief Sets the texture of the sprite.
   * @param texture The new texture to use for the sprite.
   */
  inline void
  setTexture(const sf::Texture& texture)
  {
    m_sprite.setTexture(texture);
  }

  /**
   * @brief Sets the texture rectangle of the sprite.
   * @param rect The new texture rectangle to use for the sprite.
   */
  inline void
  setTextureRect(const sf::IntRect& rect)
  {
    m_sprite.setTextureRect(rect);
  }

  /**
   * @brief Flips the sprite horizontally.
   */
  void
  flipX(const bool flipped);

  /**
   * @brief Returns the draw order of the owner actor.
   */
  inline int32
  getDrawOrder() const
  {
    return m_drawOrder;
  }

  /**
   * @brief Sets the draw order of the owner actor. Actors with lower draw orders are drawn first.
   */
  inline void
  setDrawOrder(const int32 drawOrder)
  {
    m_drawOrder = drawOrder;
  }

 private:

  /**
   * @brief Sets the origin of the sprite to its center for proper rotation and scaling.
   */
  void
  setOriginAtCenter();

  sf::Texture m_texture;
  sf::Sprite m_sprite;
  int32 m_drawOrder = 0;
};
