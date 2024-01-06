#include "Entity.hpp"
#include <cstdlib>
#include <iostream>

namespace Engine {

Entity::Entity(int speed)
  : m_speed(speed)
{
}

auto
Entity::render(sf::RenderTarget& target) -> void
{
  this->c_animation.animate(this->getState())->move(this->m_position);
  target.draw(this->c_animation.getSprite());
}

auto
Entity::update() -> void
{
  this->m_move();

  this->c_animation.animate(this->getState())->move(this->m_position);
}

auto
Entity::m_move() -> void
{
  this->m_setSpeed();
  this->m_manageGravity();
  this->m_position += this->m_velocity;

  this->m_boundingBox.left = this->m_position.x;
  this->m_boundingBox.top = this->m_position.y;
}

auto
Entity::m_setSpeed() -> void
{
  if (this->left) {
    this->m_velocity.x = this->m_speed * -1;
    this->m_state = Components::ENTITY_STATE::WALKING_LEFT;
  }

  if (this->right) {
    this->m_velocity.x = this->m_speed;
    this->m_state = Components::ENTITY_STATE::WALKING_RIGHT;
  }

  if (!this->left && !this->right) {
    this->m_velocity.x = 0;
    this->m_state = Components::ENTITY_STATE::STILL;
  }

  if (this->up) {
    if (this->m_jumpedDistance <= 60) {
      this->m_velocity.y = -20;
      m_grounded = false;
      this->m_jumpedDistance += 20;
    }
  } else if (this->m_grounded) {
    this->m_jumpedDistance = 0;
  }
}

auto
Entity::m_isMoving() -> bool
{
  return this->up || this->down || this->left || this->right;
}

auto
Entity::getState() const -> const Components::ENTITY_STATE&
{
  return this->m_state;
}

auto
Entity::m_manageGravity() -> void
{
  if (m_grounded)
    return;

  this->m_velocity.y += this->m_gravity;
  if (std::abs(this->m_velocity.y) > this->m_maxYVelocity) {
    float yDir = this->m_velocity.y < 0 ? -1 : 1;
    this->m_velocity.y = this->m_maxYVelocity * yDir;
  }

  this->m_velocity.y *= this->m_drag;

  if (std::abs(this->m_velocity.y) < this->m_minVelocity) {
    this->m_velocity.y = 0;
  }
}

auto
Entity::getBox() const -> const sf::FloatRect&
{
  return this->m_boundingBox;
}

auto
Entity::land(float yPos) -> void
{
  this->m_position.y = yPos;
  this->m_velocity.y = 0;
  this->m_grounded = true;
}

auto
Entity::setBoundingBox(int width, int height) -> void
{
  this->m_boundingBox.width = 56;
  this->m_boundingBox.height = 56;
}
}
