#pragma once

/**
 * Includes
 */

#include "FrameworkPrerequisites.h"
#include "Scene.h"
#include "PhysicsManager.h"

#include <SFML/Graphics.hpp>

/**
 * Forward declarations
 */

class Player;

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
  
  /**
   * @brief Initializes the game, loading resources, setting up the initial scene, and preparing the game state.
   */
  void
  initialize();

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
   * @brief Handles the game over state, which may involve displaying a game over screen, resetting the game, or exiting.
   */
  void
  onGameOver();

  SPtr<sf::RenderWindow> m_pWindow;

  Vector<SPtr<Scene>> m_pScenes; // Vector to hold multiple scenes if needed
  PhysicsManager m_physicsManager; // Manages physics and collision detection

  SPtr<Player> m_pPlayer;

  bool m_isDebugMode = true; // Flag to enable/disable debug mode for additional logging or visual aids
  bool m_isPaused = false; // Flag to indicate whether the game is paused
  bool m_isGameOver = false; // Flag to indicate whether the game is over
  float m_deltaTime = 0.0f; // Time elapsed between frames, used for consistent movement and updates
};
