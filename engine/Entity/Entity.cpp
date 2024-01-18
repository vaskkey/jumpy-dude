#include "Entity.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>

namespace Engine {

Entity::Entity(int speed, int damage, int hp)
  : m_speed(speed)
  , DAMAGE(damage)
  , hp(hp)
{
  this->m_damageTimer.restart();
}

auto
Entity::render(sf::RenderTarget& target) -> void
{
  this->c_animation.animate(this->getState(), this->getFacingDirection())
    ->move(this->m_position);
  target.draw(this->c_animation.getSprite());
  // auto box = sf::RectangleShape();
  // box.setPosition(this->m_boundingBox.getPosition());
  // box.setSize(this->m_boundingBox.getSize());
  // box.setFillColor(sf::Color::Transparent);
  // box.setOutlineColor(sf::Color::Red);
  // box.setOutlineThickness(1);
  // target.draw(box);
}

auto
Entity::update() -> void
{
  this->m_setState();
  this->m_move();

  this->c_animation.animate(this->getState(), this->getFacingDirection())
    ->move(this->m_position);
}

auto
Entity::getState() const -> Components::ENTITY_STATE
{
  return this->m_state;
}

auto
Entity::getFacingDirection() const -> Components::ENTITY_FACING
{
  return this->m_facingDirection;
}

auto
Entity::getBox() const -> const sf::FloatRect&
{
  return this->m_boundingBox;
}

auto
Entity::getPreviousBox() const -> const sf::FloatRect&
{
  return this->m_prevBox;
}

auto
Entity::position() const -> const sf::Vector2f&
{
  return this->m_position;
}

auto
Entity::velocity() const -> const sf::Vector2f&
{
  return this->m_velocity;
}

auto
Entity::getGrounded() const -> bool
{
  return this->m_grounded;
}

auto
Entity::moveTo(const sf::Vector2f& position) -> void
{
  this->m_position = position;
  this->m_prevBox = this->m_boundingBox;
  this->m_boundingBox.left = this->m_position.x;
  this->m_boundingBox.top = this->m_position.y;
}

auto
Entity::moveBy(const sf::Vector2f& distance) -> void
{
  this->m_position += distance;
  this->m_prevBox = this->m_boundingBox;
  this->m_boundingBox.left = this->m_position.x;
  this->m_boundingBox.top = this->m_position.y;
}

auto
Entity::takeDamage(int damage) -> void
{
  if (this->m_damageTimer.getElapsedTime().asMilliseconds() < 1000)
    return;
  this->m_damageTimer.restart();
  this->hp -= damage;
}

auto
Entity::land() -> void
{
  this->m_velocity.y = 0;
  this->m_grounded = true;
}

auto
Entity::setBoundingBox(int width, int height) -> void
{
  this->m_boundingBox.width = width;
  this->m_boundingBox.height = height;
}

auto
Entity::getPosition() const -> const sf::Vector2f&
{
  return this->m_position;
}

auto
Entity::getCanAttack() const -> bool
{
  return this->m_canAttack;
}

auto
Entity::setCanAttack(bool can) -> Entity*
{
  this->m_canAttack = can;
  return this;
}

auto
Entity::getAttackRange() const -> const sf::FloatRect&
{
  return this->m_attackReach;
}

auto
Entity::setAttackRange(float width, float height) -> Entity*
{
  this->m_attackReach = sf::FloatRect(this->m_position, { width, height });
  return this;
}

auto
Entity::m_move() -> void
{
  this->m_manageGravity();
  this->moveBy(this->m_velocity);

  // Adjist bounding box position
  this->m_boundingBox.left = this->m_position.x;
  this->m_boundingBox.top = this->m_position.y;

  // Adjist attack reach box position
  this->m_attackReach.left = this->m_position.x;
  this->m_attackReach.top = this->m_position.y;
}

auto
Entity::m_setState() -> void
{
  if (this->left) {
    this->m_velocity.x = this->m_speed * -1;
    this->m_state = Components::ENTITY_STATE::WALKING_LEFT;
    this->m_facingDirection = Components::ENTITY_FACING::LEFT;
  }

  if (this->right) {
    this->m_velocity.x = this->m_speed;
    this->m_state = Components::ENTITY_STATE::WALKING_RIGHT;
    this->m_facingDirection = Components::ENTITY_FACING::RIGHT;
  }

  if (!this->left && !this->right) {
    this->m_velocity.x = 0;
    this->m_state = Components::ENTITY_STATE::STILL;
  }

  if (this->up) {
    m_grounded = false;
    if (this->m_jumpedDistance <= 60) {
      this->m_velocity.y = -20;
      this->m_jumpedDistance += 20;
    }
  } else if (this->m_grounded)
    this->m_jumpedDistance = 0;

  if (this->attacking) {
    this->m_state = Components::ENTITY_STATE::ATTACKING;
  }
}

auto
Entity::m_isMoving() const -> bool
{
  return this->up || this->down || this->left || this->right;
}

auto
Entity::m_manageGravity() -> void
{
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
}
