/**
 * Includes
 */

#include "Game.h"

#include "FrameworkPrerequisites.h"
#include "Scene.h"
#include "Actor.h"
#include "SpriteRendererComponent.h"
#include "BoxColliderComponent.h"
#include "Player.h"
#include "Ghost.h"
#include "PacDot.h"

constexpr float FPS = 60.0f;
constexpr float FRAME_RATE = 1.0f / FPS;

Game::Game(const String& title, uint16 windowWidth, uint16 windowHeight, int16 posX, int16 posY)
{
  uint32 style = sf::Style::Titlebar | sf::Style::Close; // Create a window with a title bar and close button, but no resize option
  m_pWindow = make_shared<sf::RenderWindow>(sf::VideoMode({ windowWidth, windowHeight }), title, style);
  m_pWindow->setPosition({ posX, posY });
  initialize();
}

void
Game::initialize()
{
  // Initialize game resources, load assets, set up initial game state, etc.
  m_pActiveScene = std::make_shared<Scene>();
  m_pScenes.push_back(m_pActiveScene);

  sf::Texture pacmanTexture(TEXTURES_PATH + "Pac-Man.png");
  sf::Texture ghostsTexture(TEXTURES_PATH + "Ghosts.png");
  //sf::Texture redGhostTexture(TEXTURES_PATH + "RedGhost.png");
  
  SPtr<Player> pPlayer = std::make_shared<Player>(m_pWindow);
  pPlayer->addTag("Player");
  pPlayer->setPosition(m_pWindow->getSize().x * 0.5f, m_pWindow->getSize().y * 0.5f);
  pPlayer->addComponent<SpriteRendererComponent>(pacmanTexture);
  pPlayer->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(60.0f, 60.0f));

  m_pActiveScene->addActor(pPlayer);

  pPlayer->onDeath.subscribe(
    [&]()
    {
      onGameOver();
    });

  //SPtr<Ghost> pRedGhost = std::make_shared<Ghost>(GhostType::Red);
  pRedGhost = std::make_shared<Ghost>(GhostType::Red);
  pRedGhost->addTag("Enemy");
  pRedGhost->addComponent<SpriteRendererComponent>(ghostsTexture);
  pRedGhost->setProperSprite();
  pRedGhost->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(60.0f, 60.0f));
  pRedGhost->setPosition(m_pWindow->getSize().x * 0.5f, m_pWindow->getSize().y * 0.25f);

  m_pActiveScene->addActor(pRedGhost);

  SPtr<Ghost> pOrangeGhost = std::make_shared<Ghost>(GhostType::Orange);
  pOrangeGhost->addTag("Enemy");
  pOrangeGhost->addComponent<SpriteRendererComponent>(ghostsTexture);
  pOrangeGhost->setProperSprite();
  pOrangeGhost->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(60.0f, 60.0f));
  pOrangeGhost->setPosition(m_pWindow->getSize().x * 0.25f, m_pWindow->getSize().y * 0.25f);

  m_pActiveScene->addActor(pOrangeGhost);

  sf::Texture scoreBallTexture(TEXTURES_PATH + "PacDot.png");
  SPtr<PacDot> pPacDot = std::make_shared<PacDot>();
  pPacDot->addTag("PacDot");
  pPacDot->setPosition(m_pWindow->getSize().x * 0.5f, m_pWindow->getSize().y * 0.75f);
  pPacDot->addComponent<SpriteRendererComponent>(scoreBallTexture);
  pPacDot->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(15.0f, 15.0f));
  pPacDot->getComponent<SpriteRendererComponent>().lock()->setDrawOrder(-1);

  m_pActiveScene->addActor(pPacDot);

  sf::Texture powerPelletTexture(TEXTURES_PATH + "PowerPellet.png");
  SPtr<PacDot> pPowerPellet = std::make_shared<PacDot>(50);
  pPowerPellet->addTag("PacDot");
  pPowerPellet->addTag("PowerPellet");
  pPowerPellet->setPosition(m_pWindow->getSize().x * 0.75f, m_pWindow->getSize().y * 0.75f);
  pPowerPellet->addComponent<SpriteRendererComponent>(powerPelletTexture);
  pPowerPellet->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(33.0f, 33.0f));
  pPowerPellet->getComponent<SpriteRendererComponent>().lock()->setDrawOrder(-1);

  m_pActiveScene->addActor(pPowerPellet);

  m_pActiveScene->setAllActorsVisibility(false); // Start with all actors invisible until the main menu is dismissed

  m_scoreManager.loadHighScoreFile();
  m_hud.updateScore(m_scoreManager.getCurrentScore(), m_scoreManager.getHighScore()); // Initialize the HUD with the current score and high score

  pPlayer->onScoreChange.subscribe(
    [&](uint64 scoreValue)
    {
      m_scoreManager.addPoints(scoreValue); // Update the score in the Score Manager when the player scores points
      m_hud.updateScore(m_scoreManager.getCurrentScore(), m_scoreManager.getHighScore()); // Notify the HUD to update the displayed score and high score
    });

  pPlayer->onInvincibilityChanged.subscribe(
    [=](bool isInvincible)
    {
      // Toggle the vulnerability of the ghosts when the player's invincibility state changes
      pRedGhost->toggleVulnerability(isInvincible);
      pOrangeGhost->toggleVulnerability(isInvincible);
    });
}

void
Game::run()
{
  sf::Clock clock;
  while (m_pWindow->isOpen()) {

    sf::Time elapsed = clock.restart();
    float deltaTime = elapsed.asSeconds();

    handleEventsAndInput();

    m_pWindow->clear();

    if (!m_isPaused) {
      updateScene(*m_pScenes[0], deltaTime);
      m_physicsManager.handleCollisions(m_pScenes[0]->getActors());
    }

    renderScene(*m_pScenes[0]);
    renderUI();
    m_pActiveScene->destroyMarkedActors(); // Destroy any actors that were marked for destruction during the update or collision handling
    m_pWindow->display();

  }
}

void
Game::handleEventsAndInput()
{
  while (const Optional<sf::Event> event = m_pWindow->pollEvent()) {

    if (event->is<sf::Event::Closed>()) {
      m_pWindow->close();
    }
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
     
      if (keyPressed->code == sf::Keyboard::Key::Escape) {
        m_pWindow->close(); // Close the window when 'Escape' is pressed
      }

      if (keyPressed->code == sf::Keyboard::Key::Enter) {
        m_mainMenuActive = m_mainMenuActive = false;
        m_isPaused = false; // Start the game when 'Enter' is pressed
        m_pActiveScene->setAllActorsVisibility(true); // Make all actors visible when the main menu is dismissed
      }

      if (keyPressed->scancode == sf::Keyboard::Scancode::P) {
        m_isPaused = !m_isPaused; // Toggle pause state when 'P' is pressed
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
        sf::FloatRect bounds = boxCollider.lock()->getBounds();
        sf::RectangleShape debugShape(sf::Vector2f(bounds.size.x, bounds.size.y));
        debugShape.setPosition(sf::Vector2f(bounds.position.x, bounds.position.y));
        debugShape.setFillColor(sf::Color::Transparent);
        debugShape.setOutlineColor(sf::Color::Red);
        debugShape.setOutlineThickness(1.0f);
        m_pWindow->draw(debugShape);
      }

      sf::Vector2f position = pRedGhost->getTransform().getPosition();
      sf::FloatRect bounds = pRedGhost->getComponent<BoxColliderComponent>().lock()->getBounds();
      sf::Vector2f boundsPos = sf::Vector2f(bounds.position.x, bounds.position.y);
      bool stop = true;
    }

  }

}

void
Game::renderUI()
{
  if (m_mainMenuActive) {
    m_mainMenuUI.draw(*m_pWindow);
  }
  else if (m_isGameOver) {
    m_gameOverUI.draw(*m_pWindow);
  }
  else {
    if (!m_isPaused) {
      m_hud.draw(*m_pWindow);
    }
    else {
      m_pauseUI.draw(*m_pWindow);
    }
  }
}

void Game::onGameOver()
{
  // Handle game over state, e.g., display game over screen, reset game, etc.
  cout << "Game Over!\n\a";
  m_isGameOver = true;

  m_scoreManager.saveHighScoreFile(); // Save the high score to file when the game is over
  m_gameOverUI.displayScore(m_scoreManager.getCurrentScore(), m_scoreManager.hasGotHighScore());
}
