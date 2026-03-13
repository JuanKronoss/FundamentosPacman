#pragma once

/**
 * Includes
 */

#include "UI.h"

/**
 * @brief Represents the heads-up display (HUD) user interface (UI) of the game,
 * which displays important information to the player during gameplay, such as the current score and high score.
 */
class HUD: public UI
{
 public:

  HUD();
  ~HUD() = default;

  /**
   * @brief Populates the UI with drawable elements.
   */
  void
  populate() override;

 private:

  SPtr<sf::Text> m_scoreNumText;
  SPtr<sf::Text> m_highScoreNumText;

};
