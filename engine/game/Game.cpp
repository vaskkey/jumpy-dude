#include "../Physics/Physics.hpp"
#include "Game.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/VideoMode.hpp"

namespace Engine {
Game::Game()
{
  this->m_window.create(sf::VideoMode(800, 600), "Jumpy Dude");
  this->m_window.setFramerateLimit(60);

  this->m_tileManager.createTile(TILE_TYPE::BASIC);

  this->m_player = this->m_entityFactory.createEntity(ENTITY_TYPE::PLAYER);
  this->m_entityFactory.createEntity(ENTITY_TYPE::MUSHROOM, 500, 600);

  this->m_worldTexture.loadFromFile("static/background_layer_1.png");
  this->m_worldTexture.setRepeated(true);
  this->m_worldBg.setTexture(this->m_worldTexture);
  this->m_worldBg.scale(3.5, 3.5);
}

auto
Game::loop() -> void
{
  while (this->m_window.isOpen()) {
    this->m_handleEvents();

    this->m_entityFactory.updateEntities(this->m_window, this->m_player);
    Physics::manageTileMapCollision(this->m_entityFactory, this->m_tileManager);
    this->m_updateView();

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

  this->m_window.draw(this->m_worldBg);
  this->m_tileManager.renderTiles(this->m_window);
  this->m_entityFactory.renderEntities(this->m_window);

  this->m_window.display();
}

auto
Game::m_handleKeyEvent(const sf::Keyboard::Key& key, bool value) -> void
{
  switch (key) {
    case sf::Keyboard::Key::W:
      this->m_player->up = value;
      break;
    case sf::Keyboard::Key::S:
      this->m_player->down = value;
      break;
    case sf::Keyboard::Key::A:
      this->m_player->left = value;
      break;
    case sf::Keyboard::Key::D:
      this->m_player->right = value;
      break;
    case sf::Keyboard::Key::Space:
      this->m_player->attacking = value;
    default:
      break;
  }
}

auto
Game::m_updateView() -> void
{
  float cameraX = this->m_player->position().x - 100;
  cameraX = cameraX < 0 ? 0 : cameraX;

  this->m_view.reset(sf::FloatRect(cameraX, 0, 800, 600));
  this->m_window.setView(this->m_view);
}

}
