#include "GameOverUI.h"

GameOverUI::GameOverUI()
{
  populate();
}

void
GameOverUI::populate()
{
  sf::Text gameOverText(m_arcadeFont, "GAME OVER", 48);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setPosition(sf::Vector2f(150.0f, 200.0f));
  addDrawable(make_shared<sf::Text>(gameOverText));

  sf::Text promptText(m_arcadeFont, "Press [Enter] to Restart\n\n\n    [Esc] to Exit", 24);
  promptText.setPosition(sf::Vector2f(120.0f, 400.0f));
  addDrawable(make_shared<sf::Text>(promptText));
}
