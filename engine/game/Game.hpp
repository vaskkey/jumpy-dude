#pragma once

#include "../Entity/Entity.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Keyboard.hpp"

namespace Engine {
class Game
{
  sf::RenderWindow m_window;
  sf::Texture m_worldTexture;
  sf::Sprite m_worldBg;
  Entity m_player;

public:
  Game();

  auto loop() -> void;

private:
  auto m_handleEvents() -> void;
  auto m_draw() -> void;
  auto m_updatePlayer() -> void;
  auto m_handleKeyEvent(const sf::Keyboard::Key& key, bool value) -> void;
};
}
