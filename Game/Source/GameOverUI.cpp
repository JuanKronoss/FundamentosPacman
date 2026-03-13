#include "GameOverUI.h"

GameOverUI::GameOverUI()
{
  populate();
}

void
GameOverUI::populate()
{
  auto gameOverText = make_shared<sf::Text>(m_arcadeFont, "GAME OVER", 48);
  gameOverText->setFillColor(sf::Color::Red);
  centerText(gameOverText, 400.0f, 200.0f);
  addDrawable(gameOverText);

  auto enterPromptText = make_shared< sf::Text>(m_arcadeFont, "Press [Enter] to Restart", 24);
  centerText(enterPromptText, 400.0f, 450.0f);
  addDrawable(enterPromptText);

  auto exitPromptText = make_shared< sf::Text>(m_arcadeFont, "[Esc] to Exit", 24);
  centerText(exitPromptText, 400.0f, 550.0f);
  addDrawable(exitPromptText);

  m_highScoreText = make_shared<sf::Text>(m_arcadeFont, "Your score:", 24);
  addDrawable(m_highScoreText);

  m_highScoreNumText = make_shared<sf::Text>(m_arcadeFont, "0", 24);
  addDrawable(m_highScoreNumText);
}

void
GameOverUI::displayScore(const uint64 score, const bool isHighScore)
{
  if (isHighScore) {
    m_highScoreText->setString("You got a High Score!");
  }
  centerText(m_highScoreText, 400.0f, 300.0f);

  m_highScoreNumText->setString(to_string(score));
  centerText(m_highScoreNumText, 400.0f, 350.0f);  
}
