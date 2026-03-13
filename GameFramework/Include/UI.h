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
   * @brief Draws all the drawable elements in the UI to the specified render target.
   * @param target The render target to draw the UI elements on.
   */
  void
  draw(sf::RenderTarget& target) const;

 protected:

  Vector<SPtr<sf::Drawable>> m_drawables;

  sf::Font m_arcadeFont; // Font used for UI text elements, can be loaded and used by derived classes

};
