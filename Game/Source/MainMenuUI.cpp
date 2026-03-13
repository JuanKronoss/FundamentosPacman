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
    titleSprite.setPosition(sf::Vector2f(132.0f, 142.0f));
    addDrawable(make_shared<sf::Sprite>(titleSprite));    
  }
  else {
    throw std::runtime_error("Failed to load title texture from file: " + TEXTURES_PATH + "TitleLogo.png");
  }

  String promptString = "Press [Enter] to Start\n\n\n    [Esc] to Exit\n\n\n     [P] to Pause";

  sf::Text promptText(m_arcadeFont, promptString, 24);
  promptText.setFillColor(sf::Color::White);

  promptText.setPosition(sf::Vector2f(150.0f, 400.0f));

  addDrawable(make_shared<sf::Text>(promptText));
}
