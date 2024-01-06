#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"

#include "../Components/Animation/Animation.hpp"

namespace Engine {
class Entity
{
  sf::Vector2f m_position;
  sf::Vector2f m_velocity;
  Components::ENTITY_STATE m_state = Components::ENTITY_STATE::STILL;

  const float m_maxVelocity = 10;
  const float m_minVelocity = .2;
  const float m_acceleration = 1;
  const float m_drag = 0.95;
  const float m_gravity = 4;
  const float m_maxYVelocity = 10;

  const int m_speed = 1;

public:
  // Animation
  Components::Animation c_animation;
  // Movement
  bool up = false, down = false, left = false, right = false;

  Entity();

  auto update() -> void;
  auto render(sf::RenderTarget& target) -> void;

  auto getState() const -> const Components::ENTITY_STATE&;

private:
  auto m_move() -> void;
  auto m_setSpeed() -> void;
  auto m_manageGravity() -> void;
  auto m_isMoving() -> bool;
};

}
