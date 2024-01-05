#include "Entity.hpp"
#include <iostream>

namespace Engine {

Entity::Entity(const std::string& file, int width, int height)
  : m_intRect(0, 0, width, height)
{
  this->m_texture.loadFromFile(file);
  this->m_sprite.setTexture(this->m_texture);
  this->m_sprite.setPosition(this->m_position);

  this->m_animTimer.restart();
}

auto
Entity::render(sf::RenderTarget& target) -> void
{
  this->m_animate();
  target.draw(this->m_sprite);
}

auto
Entity::update() -> void
{
  this->m_move();

  this->m_sprite.setPosition(this->m_position);
  this->m_sprite.setTextureRect(this->m_intRect);
}

auto
Entity::m_move() -> void
{
  this->m_setSpeed();
  this->m_position += this->m_velocity;
}

auto
Entity::m_setSpeed() -> void
{
  if (this->left) {
    this->m_velocity.x = this->m_speed * -1;
  }

  if (this->right) {
    this->m_velocity.x = this->m_speed;
  }

  if (!this->left && !this->right) {
    this->m_velocity.x = 0;
  }

  if (this->up) {
    this->m_velocity.y = this->m_speed * -1;
  }

  if (this->down) {
    this->m_velocity.y = this->m_speed;
  }

  if (!this->up && !this->down) {
    this->m_velocity.y = 0;
  }
}

auto
Entity::m_isMoving() -> bool
{
  return this->up || this->down || this->left || this->right;
}

auto
Entity::m_animate() -> void
{
  if (this->m_animTimer.getElapsedTime().asMilliseconds() < 100)
    return;

  if (this->m_isMoving()) {
    if (++this->m_frame >= 8) {
      this->m_frame = 0;
    }
    this->m_intRect.left = this->m_intRect.width * this->m_frame;

    this->m_animTimer.restart();
    this->m_sprite.setTextureRect(this->m_intRect);
  }
}
}
