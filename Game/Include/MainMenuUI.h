#pragma once

/**
 * Includes
 */

#include "UI.h"
#include "Module.h"

#include <SFML/Graphics.hpp>

/**
 * @brief Represents the main menu user interface (UI) of the game,
 * which is displayed when the game starts and allows the player to start the game or access other options.
 */
class MainMenuUI : public UI, public Module<MainMenuUI>
{
  public:
  
  MainMenuUI(const float _windowWidth, const float _windowHeight);
  ~MainMenuUI() = default;

  /**
   * @brief Populates the UI with drawable elements.
   */
  void
  populate() override;

private:
 
  sf::Texture m_titleTexture;

};
