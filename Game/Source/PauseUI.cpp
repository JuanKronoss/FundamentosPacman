/**
 * Includes
 */

#include "PauseUI.h"

PauseUI::PauseUI(const float _windowWidth, const float _windowHeight)
  : UI(_windowWidth, _windowHeight)
{
  populate();
}

void
PauseUI::populate()
{
  auto promptText = make_shared<sf::Text>(m_arcadeFont, "PAUSED", 36);
  centerText(promptText, m_halfWindowWidth, 388.0f);
  addDrawable(promptText);
}