#pragma once

#include "../Entity/Entity.hpp"
#include "../EntityFactory/EntityFactory.hpp"
#include "../TileManager/TileManager.hpp"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Keyboard.hpp"

namespace Engine {
class Game
{
  sf::RenderWindow m_window;
  sf::View m_view;
  sf::Texture m_worldTexture;
  sf::Sprite m_worldBg;

  EntityFactory m_entityFactory;
  Entity* m_player;

  TileManager m_tileManager;

public:
  Game();

  auto loop() -> void;

private:
  auto m_handleEvents() -> void;
  auto m_draw() -> void;
  auto m_updateView() -> void;
  auto m_handleKeyEvent(const sf::Keyboard::Key& key, bool value) -> void;
};
}
