#include <SFML/Graphics.hpp>

#include "FrameworkPrerequisites.h"
#include "Scene.h"
#include "Actor.h"
#include "SpriteRendererComponent.h"
#include "BoxColliderComponent.h"
#include "Player.h"

const String ASSETS_PATH = "Assets/";
const String TEXTURES_PATH = ASSETS_PATH + "Textures/";

void
updateScene(const Scene& scene);

void
renderScene(const Scene& scene, sf::RenderWindow& window);

int32 main() {

  sf::RenderWindow window(sf::VideoMode({ 800, 900 }), "SFML works!");
  window.setPosition({ 560, 50 });

  //sf::CircleShape shape(20.0f);
  //shape.setFillColor(sf::Color::Yellow);

  SPtr<Scene> pScene = std::make_shared<Scene>();

  //sf::Texture pacmanTexture(TEXTURES_PATH + "Pacman.png");
  sf::Texture pacmanTexture("C:/Users/juanc/Documents/UAD/Especialidad/FundamentosProgra/FundamentosPacman/Assets/Textures/Pacman.png");
  SPtr<Actor> pPlayer = std::make_shared<Player>();
  pPlayer->addComponent<SpriteRendererComponent>(pacmanTexture);
  pPlayer->addComponent<BoxColliderComponent>(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(32.0f, 32.0f));

  pScene->addActor(pPlayer);

  while (window.isOpen()) {

    while (const Optional event = window.pollEvent()) {

      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear();
    //window.draw(shape);
    updateScene(*pScene);
    renderScene(*pScene, window);
    window.display();
  }
}

void
updateScene(const Scene& scene)
{
  for (const auto& actor : scene.getActors()) {
    actor->update(0.016f); // Assuming a fixed delta time of 16ms for simplicity
  }
}

void
renderScene(const Scene& scene, sf::RenderWindow& window)
{
  auto actorsInDrawingOrder = scene.getActorsInDrawingOrder();
  for (const auto& actor : actorsInDrawingOrder) {
    WPtr<SpriteRendererComponent> spriteRenderer = actor->getComponent<SpriteRendererComponent>();
    if (!spriteRenderer.expired()) {
      window.draw(spriteRenderer.lock()->getSprite());
    }

    //Debug rendering of box colliders
    WPtr<BoxColliderComponent> boxCollider = actor->getComponent<BoxColliderComponent>();
    if (!boxCollider.expired()) {
      sf::FloatRect bounds = boxCollider.lock()->getBounds();
      sf::RectangleShape debugShape(sf::Vector2f(bounds.size.x, bounds.size.y));
      debugShape.setPosition(sf::Vector2f(bounds.position.x, bounds.position.y));
      debugShape.setFillColor(sf::Color::Transparent);
      debugShape.setOutlineColor(sf::Color::Red);
      debugShape.setOutlineThickness(1.0f);
      window.draw(debugShape);
    }
  }

}
