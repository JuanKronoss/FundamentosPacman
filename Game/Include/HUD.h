#pragma once

/**
 * Includes
 */

#include "UI.h"
#include "Module.h"

/**
 * @brief Represents the heads-up display (HUD) user interface (UI) of the game,
 * which displays important information to the player during gameplay, such as the current score and high score.
 */
class HUD : public UI, public Module<HUD>
{
 public:

  HUD();
  ~HUD() = default;

  /**
   * @brief Populates the UI with drawable elements.
   */
  void
  populate() override;

  /**
   * @brief Updates the displayed score and high score text elements with the current values.
   * @param currentScore The current score to display.
   * @param highScore The high score to display.
   */
  void
  updateScore(const uint64 currentScore, const uint64 highScore);

 private:

  SPtr<sf::Text> m_scoreNumText;
  SPtr<sf::Text> m_highScoreNumText;

};
