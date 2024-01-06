#include "Entity.hpp"
#include <iostream>

namespace Engine {

Entity::Entity() {}

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
  this->m_position += this->m_velocity;
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
Entity::getState() const -> const Components::ENTITY_STATE&
{
  return this->m_state;
}
}
