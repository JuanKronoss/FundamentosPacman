#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"

#include <SFML/Graphics.hpp>

/**
 * Forward declarations
 */

class Player;
class Ghost;
class Scene;

/**
 * @brief Main game class responsible for managing the game loop, window, and overall game state.
 */
class Game
{
 public:

  Game(const String& title = "Pakkuman",
       uint16 windowWidth = 800,
       uint16 windowHeight = 900,
       int16 posX = 560,
       int16 posY = 50);

  ~Game() = default;

  /**
   * @brief Runs the main game loop, handling events, updating the game state, and rendering the scene.
   */
  void
  run();

  /**
   * @brief Enables or disables debug mode, which may provide additional logging or visual aids for development purposes.
   */
  inline void
  setDebugMode(bool isEnabled)
  {
    m_isDebugMode = isEnabled;
  }

private:
  
  void
  initSystems();

  void
  shutDownSystems();

  /**
   * @brief Loads game resources such as textures
   */
  void
  loadResources();

  /**
   * @brief Subscribes to player onGameOver event to trigger the game over state when the player dies.
   */
  void
  subscribeToPlayerEvent();

  /**
   * @brief Handles window events and player input, such as closing the window or pausing the game.
   */
  void
  handleEventsAndInput();

  /**
   * @brief Updates the game state based on the current scene, handling actor updates and game logic.
   */
  void
  updateScene(const Scene& scene, const float deltaTime);

  /**
   * @brief Renders the current scene to the window, drawing all actors and visual elements.
   */
  void
  renderScene(const Scene& scene);

  /**
    * @brief Renders the user interface (UI) elements, such as the main menu or game over screen, on top of the game scene.
    */
  void
  renderUI();


 public:

  /**
   * @brief Gets the size of the game window.
   */
  inline sf::Vector2u
  getWindowSize() const
  {
    return m_pWindow->getSize();
  }

  /**
   * @brief Handles the game over state, which may involve displaying a game over screen, resetting the game, or exiting.
   */
  void
  onGameOver();

private:

  SPtr<sf::RenderWindow> m_pWindow;

  SPtr<Player> m_pPlayer;

  bool m_isDebugMode = true; // Flag to enable/disable debug mode for additional logging or visual aids
  bool m_mainMenuActive = true; // Flag to indicate whether the main menu is active
  bool m_isPaused = true; // Flag to indicate whether the game is paused
  bool m_isGameOver = false; // Flag to indicate whether the game is over

};
