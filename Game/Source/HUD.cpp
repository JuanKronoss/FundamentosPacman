/**
 * Includes
 */

#include "HUD.h"

HUD::HUD(const float _windowWidth, const float _windowHeight)
  : UI(_windowWidth, _windowHeight)
{
  populate();
}

void
HUD::populate()
{
  uint32 fontSize = 20;
  float verticalPadding = 25.0f;

  sf::Text scoreText(m_arcadeFont, "SCORE", fontSize);
  scoreText.setPosition(sf::Vector2f(20.0f, 10.0f));
  addDrawable(make_shared<sf::Text>(scoreText));
  
  m_scoreNumText = make_shared<sf::Text>(m_arcadeFont, "0", fontSize);
  sf::Vector2f scorePos(scoreText.getPosition().x, scoreText.getPosition().y + verticalPadding);
  m_scoreNumText->setPosition(sf::Vector2f(scorePos));
  addDrawable(m_scoreNumText);

  sf::Text highScoreText(m_arcadeFont, "HIGH SCORE", fontSize);
  highScoreText.setPosition(sf::Vector2f(450.0f, 10.0f));
  addDrawable(make_shared<sf::Text>(highScoreText));

  m_highScoreNumText = make_shared<sf::Text>(m_arcadeFont, "0", fontSize);
  sf::Vector2f highScorePos(highScoreText.getPosition().x, highScoreText.getPosition().y + verticalPadding);
  m_highScoreNumText->setPosition(sf::Vector2f(highScorePos));
  addDrawable(m_highScoreNumText);
}

void
HUD::updateScore(const uint64 currentScore, const uint64 highScore)
{
  m_scoreNumText->setString(to_string(currentScore));
  m_highScoreNumText->setString(to_string(highScore));
}
