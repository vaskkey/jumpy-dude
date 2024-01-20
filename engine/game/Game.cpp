#include "Game.hpp"
#include "../Config/Config.hpp"
#include "../GameEnd/GameEnd.hpp"
#include "../Physics/Physics.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/VideoMode.hpp"

namespace Engine {
Game::Game()
{
  this->m_window.create(sf::VideoMode(800, 600), "Jumpy Dude");
  this->m_window.setFramerateLimit(60);

  this->m_font.loadFromFile("static/RubikBurned-Regular.ttf");
  this->m_hpText.setFont(this->m_font);
  this->m_hpText.setCharacterSize(30);
  this->m_hpText.setFillColor(sf::Color::Red);

  this->m_tileManager.init();
  this->m_itemManager.init();

  this->m_player = this->m_entityFactory.init();

  this->m_worldTexture.loadFromFile("static/background_layer_1.png");
  this->m_worldTexture.setRepeated(true);
  this->m_worldBg.setTexture(this->m_worldTexture);
  this->m_worldBg.scale(3.5, 3.5);
  this->m_worldBg.setTextureRect(sf::IntRect(0, 0, Config::GAME_WIDTH, 180));
}

auto
Game::loop() -> void
{
  std::string result = "";
  while (this->m_window.isOpen()) {
    try {
      if (this->m_gameOver) {
        this->m_endScreen(result);
      } else {
        this->m_handleGame();
      }
    } catch (GameEnd::PlayerWon& ex) {
      result = "You Won!";
      this->m_gameOver = true;
    } catch (GameEnd::PlayerLost& ex) {
      result = "You Lost!";
      this->m_gameOver = true;
    }
  }

  this->m_endScreen("You Won!");
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
  this->m_itemManager.renderItems(this->m_window);
  this->m_entityFactory.renderEntities(this->m_window);
  this->m_updateUI();

  this->m_window.display();
}

auto
Game::m_handleKeyEvent(const sf::Keyboard::Key& key, bool value) -> void
{
  if (this->m_gameOver)
    return;

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
  float desiredPos = Config::GAME_WIDTH - 600;

  if (cameraX > desiredPos) {
    this->m_cameraX = desiredPos;
    return;
  }

  this->m_cameraX = cameraX < 0 ? 0 : cameraX;

  this->m_view.reset(sf::FloatRect(this->m_cameraX, 0, 800, 600));
  this->m_window.setView(this->m_view);
}

auto
Game::m_updateUI() -> void
{
  this->m_hpText.setString(std::to_string(this->m_player->hp));
  this->m_hpText.setPosition({ this->m_cameraX + 50, 50 });
  this->m_window.draw(this->m_hpText);
}

auto
Game::m_endScreen(const std::string& str) -> void
{
  this->m_window.clear();
  this->m_view.reset(sf::FloatRect(0, 0, 800, 600));
  this->m_window.setView(this->m_view);
  auto text = sf::Text(str, this->m_font);
  text.setFillColor(sf::Color::White);
  text.setPosition({ 350, 250 });
  this->m_window.draw(text);
  this->m_window.display();
  this->m_handleEvents();
}

auto
Game::m_handleGame() -> void
{

  this->m_handleEvents();

  this->m_entityFactory.updateEntities(this->m_window, this->m_player);
  this->m_itemManager.updateItems(this->m_player);
  Physics::manageTileMapCollision(this->m_entityFactory, this->m_tileManager);
  this->m_updateView();

  this->m_draw();
}
}
