/**
 * Includes
 */

#include "Game.h"

#include "FrameworkPrerequisites.h"
#include "UI.h"
#include "MainMenuUI.h"
#include "HUD.h"
#include "PauseUI.h"
#include "GameOverUI.h"
#include "ResourceManager.h"
#include "ScoreManager.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include "Level.h"
#include "Actor.h"
#include "Ghost.h"
#include "PacDot.h"
#include "SpriteRendererComponent.h"
#include "BoxColliderComponent.h"
#include "Player.h"

constexpr float FPS = 60.0f;
constexpr float FRAME_RATE = 1.0f / FPS;

Game::Game(const String& title, uint16 windowWidth, uint16 windowHeight, int16 posX, int16 posY)
{
  uint32 style = sf::Style::Titlebar | sf::Style::Close; // Create a window with a title bar and close button, but no resize option
  m_pWindow = make_shared<sf::RenderWindow>(sf::VideoMode({ windowWidth, windowHeight }), title, style);
  m_pWindow->setPosition({ posX, posY });
  initSystems();
  loadResources();
}

void
Game::initSystems()
{
  ResourceManager::startUp(); // Start up the ResourceManager module to manage game resources such as textures and sounds
  MainMenuUI::startUp(); // Start up the MainMenuUI module to manage the main menu user interface (UI) that is displayed when the game starts
  HUD::startUp(); // Start up the HUD module to manage the heads-up display (HUD) user interface (UI) that shows the player's score and high score during gameplay
  PauseUI::startUp(); // Start up the PauseUI module to manage the pause menu user interface (UI) that is displayed when the game is paused
  GameOverUI::startUp(); // Start up the GameOverUI module to manage the game over screen user interface (UI) that is displayed when the player loses the game
  ScoreManager::startUp(); // Start up the ScoreManager module to manage player scores and high scores
  PhysicsManager::startUp(); // Start up the PhysicsManager module to handle physics calculations and collision detection
  SceneManager::startUp(); // Start up the SceneManager module to manage game scenes and transitions
}

void
Game::shutDownSystems()
{
  ResourceManager::shutDown(); // Shut down the ResourceManager module and free any resources it is using
  MainMenuUI::shutDown(); // Shut down the MainMenuUI module and free any resources it is using
  HUD::shutDown(); // Shut down the HUD module and free any resources it is using
  PauseUI::shutDown(); // Shut down the PauseUI module and free any resources it is using
  GameOverUI::shutDown(); // Shut down the GameOverUI module and free any resources it is using
  ScoreManager::shutDown(); // Shut down the ScoreManager module and free any resources it is using
  PhysicsManager::shutDown(); // Shut down the PhysicsManager module and free any resources it is using
  SceneManager::shutDown(); // Shut down the SceneManager module and free any resources it is using
}

void
Game::loadResources()
{
  // Load game textures
  ResourceManager& resourceMan = ResourceManager::instance();

  resourceMan.loadTexture("PacMan", TEXTURES_PATH + "Pac-Man.png");
  resourceMan.loadTexture("Ghosts", TEXTURES_PATH + "Ghosts.png");
  resourceMan.loadTexture("PacDot", TEXTURES_PATH + "PacDot.png");
  resourceMan.loadTexture("PowerPellet", TEXTURES_PATH + "PowerPellet.png");
  resourceMan.loadTexture("Wall", TEXTURES_PATH + "Wall.png");

  // Load level data and set up the initial scene
  SceneManager& sceneMan = SceneManager::instance();
  sf::Vector2u windowSize = getWindowSize();
  sceneMan.addScene(make_shared<Level>(LEVELS_PATH + "Level1.txt", windowSize.x, windowSize.y)); // Add the level scene to the scene manager
  subscribeToPlayerEvent();
}

void
Game::subscribeToPlayerEvent()
{
  SceneManager& sceneMan = SceneManager::instance();
  auto pPlayer = dynamic_pointer_cast<Player>(sceneMan.getActiveScene()->getActorByName("Player")); // Get a shared pointer to the player actor in the active scene

  pPlayer->onDeath.subscribe(
    [&]()
    {
      onGameOver(); // Trigger the game over state when the player dies
    });

  sceneMan.getActiveScene()->setAllActorsVisibility(false); // Hide all actors in the active scene when the game starts, so that only the main menu is visible until the player starts the game
}

void
Game::run()
{
  sf::Clock clock;
  SceneManager& sceneMan = SceneManager::instance();
  PhysicsManager& physicsMan = PhysicsManager::instance();
  while (m_pWindow->isOpen()) {

    sf::Time elapsed = clock.restart();
    float deltaTime = elapsed.asSeconds();

    handleEventsAndInput();

    m_pWindow->clear();

    if (!m_isPaused) {
      updateScene(*sceneMan.getActiveScene(), deltaTime);
      physicsMan.handleCollisions(sceneMan.getActiveScene()->getActors());
    }

    renderScene(*sceneMan.getActiveScene());
    renderUI();
    sceneMan.getActiveScene()->destroyMarkedActors(); // Destroy any actors that were marked for destruction during the update or collision handling
    m_pWindow->display();

  }
}

void
Game::handleEventsAndInput()
{
  SceneManager& sceneMan = SceneManager::instance();
  ScoreManager& scoreMan = ScoreManager::instance();
  while (const Optional<sf::Event> event = m_pWindow->pollEvent()) {

    if (event->is<sf::Event::Closed>()) {
      m_pWindow->close();
    }
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
     
      if (keyPressed->code == sf::Keyboard::Key::Escape) {
        m_pWindow->close(); // Close the window when 'Escape' is pressed
      }

      if (keyPressed->code == sf::Keyboard::Key::Enter) {
        if (m_mainMenuActive) {
          m_mainMenuActive = m_mainMenuActive = false;
          m_isPaused = false; // Start the game when 'Enter' is pressed
          sceneMan.getActiveScene()->setAllActorsVisibility(true); // Make all actors visible when the main menu is dismissed
        }
        else if (m_isGameOver) {
          // Reset the game state to start a new game when 'Enter' is pressed on the game over screen
          m_isGameOver = false;
          m_isPaused = false; // Unpause the game to start a new game
          scoreMan.resetCurrentScore(); // Reset the current score for the new game
          HUD::instance().updateScore(scoreMan.getCurrentScore(), scoreMan.getHighScore()); // Update the HUD with the reset score and current high score
          sceneMan.getActiveScene()->reload(); // Reset the active scene to restart the game
          subscribeToPlayerEvent();
          sceneMan.getActiveScene()->setAllActorsVisibility(true);
        }
      }

      if (keyPressed->scancode == sf::Keyboard::Scancode::P) {
        if (!m_mainMenuActive && !m_isGameOver) {
          m_isPaused = !m_isPaused; // Toggle pause state when 'P' is pressed
        }
      }
    }

  }
}

void
Game::updateScene(const Scene& scene, const float deltaTime)
{
  for (const auto& actor : scene.getActors()) {
    actor->update(deltaTime);
  }
}

void
Game::renderScene(const Scene& scene)
{
  auto actorsInDrawingOrder = scene.getActorsInDrawingOrder();
  for (const auto& actor : actorsInDrawingOrder) {
    WPtr<SpriteRendererComponent> spriteRenderer = actor->getComponent<SpriteRendererComponent>();
    if (!spriteRenderer.expired()) {
      m_pWindow->draw(spriteRenderer.lock()->getSprite());
    }

    //Debug rendering of box colliders
    if (m_isDebugMode) {
      WPtr<BoxColliderComponent> boxCollider = actor->getComponent<BoxColliderComponent>();
      if (!boxCollider.expired()) {
        auto pBoxCollider = boxCollider.lock();
        if (!pBoxCollider->isActive()) {
          continue; // Skip rendering inactive box colliders
        }
        sf::FloatRect bounds = pBoxCollider->getBounds();
        sf::RectangleShape debugShape(sf::Vector2f(bounds.size.x, bounds.size.y));
        debugShape.setPosition(sf::Vector2f(bounds.position.x, bounds.position.y));
        debugShape.setFillColor(sf::Color::Transparent);
        debugShape.setOutlineColor(sf::Color::Red);
        debugShape.setOutlineThickness(1.0f);
        m_pWindow->draw(debugShape);
      }
    }

  }

}

void
Game::renderUI()
{
  if (m_mainMenuActive) {
    MainMenuUI::instance().draw(*m_pWindow);
  }
  else if (m_isGameOver) {
    GameOverUI::instance().draw(*m_pWindow);
  }
  else {
    if (m_isPaused && !m_isGameOver) {
      PauseUI::instance().draw(*m_pWindow);
    }
    else {
      HUD::instance().draw(*m_pWindow);
    }
  }
}

void Game::onGameOver()
{
  m_isPaused = true; // Pause the game when it is over
  m_isGameOver = true;

  ScoreManager& scoreMan = ScoreManager::instance();
  GameOverUI& gameOverUI = GameOverUI::instance();
  SceneManager& sceneMan = SceneManager::instance();

  scoreMan.saveHighScoreFile(); // Save the high score to file when the game is over
  gameOverUI.displayScore(scoreMan.getCurrentScore(), scoreMan.hasGotHighScore());
  sceneMan.getActiveScene()->setAllActorsVisibility(false); // Hide all actors in the active scene when the game is over, so that only the game over screen is visible
}
