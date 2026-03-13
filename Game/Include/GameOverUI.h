#pragma once

/**
 * Includes
 */

#include "UI.h"

/**
 * @brief Represents the game over user interface (UI) of the game,
 * which is displayed when the player loses the game and allows the player to restart or exit.
 */
class GameOverUI: public UI
{
 public:

  GameOverUI();
  ~GameOverUI() = default;

  /**
   * @brief Populates the UI with drawable elements.
   */
  void
  populate() override;

 private:

  sf::Texture m_gameOverTexture;

};
