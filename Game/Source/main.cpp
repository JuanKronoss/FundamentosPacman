#include <SFML/Graphics.hpp>

#include "FrameworkPrerequisites.h"

int32 main() {

  sf::RenderWindow window(sf::VideoMode({ 800, 900 }), "SFML works!");
  window.setPosition({ 560, 50 });

  sf::CircleShape shape(20.0f);
  shape.setFillColor(sf::Color::Yellow);

  while (window.isOpen()) {

    while (const Optional event = window.pollEvent()) {

      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear();
    window.draw(shape);
    window.display();
  }
}
