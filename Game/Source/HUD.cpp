/**
 * Includes
 */

#include "HUD.h"

HUD::HUD()
{
  populate();
}

void
HUD::populate()
{
  sf::Text scoreText(m_arcadeFont, "SCORE", 24);
  scoreText.setPosition(sf::Vector2f(20.0f, 20.0f));
  addDrawable(make_shared<sf::Text>(scoreText));
  
  m_scoreNumText = make_shared<sf::Text>(m_arcadeFont, "0", 24);
  m_scoreNumText->setPosition(sf::Vector2f(20.0f, 60.0f));
  addDrawable(m_scoreNumText);

  sf::Text highScoreText(m_arcadeFont, "HIGH SCORE", 24);
  highScoreText.setPosition(sf::Vector2f(400.0f, 20.0f));
  addDrawable(make_shared<sf::Text>(highScoreText));

  m_highScoreNumText = make_shared<sf::Text>(m_arcadeFont, "0", 24);
  m_highScoreNumText->setPosition(sf::Vector2f(400.0f, 60.0f));
  addDrawable(m_highScoreNumText);
}

void
HUD::updateScore(const uint32 currentScore, const uint32 highScore)
{
  m_scoreNumText->setString(to_string(currentScore));
  m_highScoreNumText->setString(to_string(highScore));
}
