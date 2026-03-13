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
  auto promptText = make_shared<sf::Text>(m_arcadeFont, "PAUSED", 36);
  centerText(promptText, 400.0f, 400.0f);
  addDrawable(promptText);
}