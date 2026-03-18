/**
 * Includes
 */

#include "UI.h"

UI::UI(const float _windowWidth, const float _windowHeight)
  : m_windowWidth(_windowWidth), m_windowHeight(_windowHeight)
{
  m_halfWindowWidth = std::floor(m_windowWidth * 0.5f);
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
UI::centerText(WPtr<sf::Text> wpText, const float posX, const float posY)
{
  if (wpText.expired()) {
    return; // Do not attempt to center an expired text
  }
  SPtr<sf::Text> pText = wpText.lock();
  sf::FloatRect textBounds = pText->getLocalBounds();
  float originX = std::floor(textBounds.size.x * 0.5f);
  float originY = std::floor(textBounds.size.y * 0.5f);
  pText->setOrigin(sf::Vector2f(originX, originY));
  pText->setPosition(sf::Vector2f(posX, posY));
}

void
UI::draw(sf::RenderTarget& target) const
{
  for (const auto& drawable : m_drawables) {
    target.draw(*drawable);
  }
}
