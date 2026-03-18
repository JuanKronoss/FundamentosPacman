#pragma once

/**
 * Includes
 */

#include "UI.h"
#include "Module.h"

/**
 * @brief Represents the pause user interface (UI) of the game,
 * which is displayed when the player pauses the game and allows the player to resume.
 */
class PauseUI : public UI, public Module<PauseUI>
{
 public:
 
  PauseUI(const float _windowWidth, const float _windowHeight);
  ~PauseUI() = default;
  
  /**
   * @brief Populates the UI with drawable elements.
   */
  void
  populate() override;
 
 private:
 
   sf::Texture m_pauseTexture;
};
