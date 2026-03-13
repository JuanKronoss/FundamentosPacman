#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

#include <SFML/Graphics.hpp>

/**
 * @brief Represents the user interface (UI) of the game, which can contain various drawable elements such as text, shapes, and sprites.
 */
class UI
{
 public:

  UI();
  virtual ~UI() = default;

  /**
   * @brief Populates the UI with drawable elements.
   * This function should be overridden by derived classes to add specific UI elements.
   */
  virtual void
  populate() = 0;

  /**
   * @brief Adds a drawable element to the UI.
   * @param drawable A shared pointer to the drawable element to add.
   */
  void
  addDrawable(const SPtr<sf::Drawable>& drawable);

  /**
   * @brief Centers the specified text element at the given position.
   * @param wpText A weak pointer to the text element to center.
   * @param posX The x-coordinate of the position to center the text at.
   * @param posY The y-coordinate of the position to center the text at.
   */
  void
  centerText(WPtr<sf::Text> wpText, const float posX, const float posY); 

  /**
   * @brief Draws all the drawable elements in the UI to the specified render target.
   * @param target The render target to draw the UI elements on.
   */
  void
  draw(sf::RenderTarget& target) const;

 protected:

  Vector<SPtr<sf::Drawable>> m_drawables;

  sf::Font m_arcadeFont; // Font used for UI text elements, can be loaded and used by derived classes

};
