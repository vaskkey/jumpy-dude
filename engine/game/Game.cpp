#include "Game.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/VideoMode.hpp"

namespace Engine {
Game::Game()
  : m_player("static/main-char-1.png", 56, 56)
{
  this->m_window.create(sf::VideoMode(800, 600), "Jumpy Dude");
  this->m_window.setFramerateLimit(60);
}

auto
Game::loop() -> void
{
  while (this->m_window.isOpen()) {
    this->m_handleEvents();
    this->m_updatePlayer();
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
      case sf::Event::KeyPressed:
        this->m_handleKeyEvent(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        this->m_handleKeyEvent(event.key.code, false);
        break;

      default:
        break;
    }
  }
}

auto
Game::m_draw() -> void
{
  this->m_window.clear();

  this->m_player.render(this->m_window);

  this->m_window.display();
}

auto
Game::m_updatePlayer() -> void
{
  this->m_player.update();
}

auto
Game::m_handleKeyEvent(const sf::Keyboard::Key& key, bool value) -> void
{
  switch (key) {
    case sf::Keyboard::Key::W:
      this->m_player.up = value;
      break;
    case sf::Keyboard::Key::S:
      this->m_player.down = value;
      break;
    case sf::Keyboard::Key::A:
      this->m_player.left = value;
      break;
    case sf::Keyboard::Key::D:
      this->m_player.right = value;
      break;
    default:
      break;
  }
}
}
