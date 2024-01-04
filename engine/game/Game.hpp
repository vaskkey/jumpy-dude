#pragma once

#include "SFML/Graphics/RenderWindow.hpp"

namespace Engine {
class Game
{
  sf::RenderWindow m_window;

public:
  Game();

  auto loop() -> void;

private:
    auto m_handleEvents() -> void;
    auto m_draw() -> void;
};
}
