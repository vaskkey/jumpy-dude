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
  sf::FloatRect m_boundingBox;

  Components::ENTITY_STATE m_state = Components::ENTITY_STATE::STILL;

  const float m_maxVelocity = 10;
  const float m_minVelocity = .2;
  const float m_acceleration = 1;
  const float m_drag = 0.95;
  const float m_gravity = 2;
  const float m_maxYVelocity = 20;

  bool m_grounded = false;
  float m_jumpedDistance = 0;

  const int m_speed;

public:
  // Animation
  Components::Animation c_animation;
  // Movement
  bool up = false, down = false, left = false, right = false;

  Entity(int speed);

  auto update() -> void;
  auto render(sf::RenderTarget& target) -> void;

  auto getState() const -> const Components::ENTITY_STATE&;
  auto getBox() const -> const sf::FloatRect&;
  auto position() const -> const sf::Vector2f&;

  auto land(float yPos) -> void;
  auto fixLeft() -> void;
  auto setBoundingBox(int width, int height) -> void;

private:
  auto m_move() -> void;
  auto m_setSpeed() -> void;
  auto m_manageGravity() -> void;
  auto m_isMoving() -> bool;
};

}
