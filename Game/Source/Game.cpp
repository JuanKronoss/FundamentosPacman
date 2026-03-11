/**
 * Includes
 */

#include "Game.h"

#include "Scene.h"
#include "Actor.h"
#include "SpriteRendererComponent.h"
#include "BoxColliderComponent.h"
#include "Player.h"

const String ASSETS_PATH = "Assets/";
const String TEXTURES_PATH = ASSETS_PATH + "Textures/";

Game::Game(const String& title, uint16 windowWidth, uint16 windowHeight, int16 posX, int16 posY)
{
  m_pWindow = make_shared<sf::RenderWindow>(sf::VideoMode({ windowWidth, windowHeight }), title);
  m_pWindow->setPosition({ posX, posY });
  initialize();
}

void
Game::initialize()
{
  // Initialize game resources, load assets, set up initial game state, etc.
  SPtr<Scene> pScene = std::make_shared<Scene>();
  m_pScenes.push_back(pScene);

  sf::Texture pacmanTexture(TEXTURES_PATH + "Pacman.png");
  
  SPtr<Actor> pPlayer = std::make_shared<Player>(m_pWindow);
  pPlayer->setPosition(m_pWindow->getSize().x * 0.5f, m_pWindow->getSize().y * 0.5f);
  pPlayer->addComponent<SpriteRendererComponent>(pacmanTexture);
  pPlayer->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(53.0f, 59.0f));

  pScene->addActor(pPlayer);

}

void
Game::run()
{
  while (m_pWindow->isOpen()) {

    while (const Optional event = m_pWindow->pollEvent()) {

      if (event->is<sf::Event::Closed>()) {
        m_pWindow->close();
      }
    }

    m_pWindow->clear();
    
    updateScene(*m_pScenes[0]);
    renderScene(*m_pScenes[0]);
    m_pWindow->display();
  }
}

void Game::updateScene(const Scene& scene)
{
  for (const auto& actor : scene.getActors()) {
    actor->update(0.016f); // Assuming a fixed delta time of 16ms for simplicity
  }
}

void Game::renderScene(const Scene& scene)
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
    }

  }

}
