#include "Game.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"

namespace Engine {
Game::Game()
{
  this->m_window.create(sf::VideoMode(800, 600), "Jumpy Dude");
}

auto
Game::loop() -> void
{
  while (this->m_window.isOpen()) {
    this->m_handleEvents();
    this->m_draw();
  }
}

auto
Game::m_handleEvents() -> void
{
  sf::Event event;
  while (this->m_window.pollEvent(event)) {
    switch (event.type) {
        // "close requested" event: we close the window
      case sf::Event::Closed:
        this->m_window.close();
        break;
      default:
        break;
    }
  }
}

auto Game::m_draw() -> void {
    this->m_window.clear();
    this->m_window.display();
  }
}
