#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine {

class Entity
{
  sf::Sprite m_sprite;
  sf::Texture m_texture;
  sf::Vector2f m_position;
  sf::Vector2f m_velocity;
  sf::IntRect m_intRect;
  sf::Clock m_animTimer;

  const int m_speed = 1;
  int m_frame = 6;

public:
  // Movement
  bool up = false, down = false, left = false, right = false;

  Entity(const std::string& file, int width, int height);

  auto update() -> void;
  auto render(sf::RenderTarget& target) -> void;

private:
  auto m_move() -> void;
  auto m_setSpeed() -> void;
  auto m_isMoving() -> bool;
  auto m_animate() -> void;
};

}
