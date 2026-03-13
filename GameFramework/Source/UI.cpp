/**
 * Includes
 */

#include "UI.h"

UI::UI()
{
  // Load the arcade font from file
  if (!m_arcadeFont.openFromFile(FONTS_PATH + "ArcadeFont.ttf")) {
    throw std::runtime_error("Failed to load arcade font from file: " + FONTS_PATH + "ArcadeFont.ttf");
  }
}

void
UI::addDrawable(const SPtr<sf::Drawable>& drawable)
{
  m_drawables.push_back(drawable);
}

void
UI::draw(sf::RenderTarget& target) const
{
  for (const auto& drawable : m_drawables) {
    target.draw(*drawable);
  }
}
