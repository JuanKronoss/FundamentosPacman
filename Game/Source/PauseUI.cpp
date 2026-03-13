/**
 * Includes
 */

#include "PauseUI.h"

PauseUI::PauseUI()
{
  populate();
}

void
PauseUI::populate()
{
  String promptString = "PAUSED";
  sf::Text promptText(m_arcadeFont, promptString, 36);
  promptText.setPosition(sf::Vector2f(285.0f, 400.0f));
  addDrawable(make_shared<sf::Text>(promptText));
}