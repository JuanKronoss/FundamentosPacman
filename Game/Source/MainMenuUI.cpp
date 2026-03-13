/**
 * Includes
 */

#include "MainMenuUI.h"

MainMenuUI::MainMenuUI()
{
  populate();
}

void
MainMenuUI::populate()
{
  // Load the title texture and create a sprite to display it
  if (m_titleTexture.loadFromFile(TEXTURES_PATH + "TitleLogo.png"))
  {
    sf::Sprite titleSprite(m_titleTexture);
    sf::FloatRect titleBounds = titleSprite.getLocalBounds();
    float originX = std::floor(titleBounds.size.x * 0.5f);
    float originY = std::floor(titleBounds.size.y * 0.5f);
    titleSprite.setOrigin(sf::Vector2f(originX, originY));
    titleSprite.setPosition(sf::Vector2f(400.0f, 200.0f));
    addDrawable(make_shared<sf::Sprite>(titleSprite));
  }
  else {
    throw std::runtime_error("Failed to load title texture from file: " + TEXTURES_PATH + "TitleLogo.png");
  }

  auto enterPromptText = make_shared< sf::Text>(m_arcadeFont, "Press [Enter] to Start", 24);
  centerText(enterPromptText, 400.0f, 400.0f);
  addDrawable(enterPromptText);

  auto exitPromptText = make_shared< sf::Text>(m_arcadeFont, "[Esc] to Exit", 24);
  centerText(exitPromptText, 400.0f, 500.0f);
  addDrawable(exitPromptText);

  auto pausePromptText = make_shared< sf::Text>(m_arcadeFont, "[P] to Pause", 24);
  centerText(pausePromptText, 400.0f, 600.0f);
  addDrawable(pausePromptText);
}
