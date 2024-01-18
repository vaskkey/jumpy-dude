#include "../../Physics/Physics.hpp"
#include "Enemy.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>

namespace Engine {

namespace AI {

Enemy::Enemy(Entity* entity)
  : m_entity(entity)
{
}

auto
Enemy::setPatrol(float from, float to) -> void
{
  this->m_patrolFrom = from;
  this->m_patrolTo = to;
  this->m_patrolling = true;

  this->m_entity->moveTo(sf::Vector2f(from, this->m_entity->getPosition().y));
}

auto
Enemy::patrol() -> void
{
  if (this->m_patrolling) {
    m_manageDirection();
  } else {
    this->m_entity->left = false;
    this->m_entity->right = false;
  }
}

auto
Enemy::manageAttackingRange(Entity* player) -> void
{
  if (!this->m_entity->getCanAttack())
    return;

  if (Physics::isColliding(player->getBox(),
                           this->m_entity->getAttackRange())) {
    this->m_entity->attacking = true;
    this->m_patrolling = false;
  } else {
    this->m_entity->attacking = false;
    this->m_patrolling = true;
  }
}

auto
Enemy::operator==(Entity* ent) -> bool
{
  return this->m_entity == ent;
}

auto
Enemy::m_manageDirection() -> void
{
  switch (this->m_pDirection) {

    case LEFT:
      this->m_entity->left = true;
      this->m_entity->right = false;
      this->m_pDirection =
        this->m_entity->getPosition().x <= this->m_patrolFrom ? RIGHT : LEFT;
      break;
    case RIGHT:
      this->m_entity->right = true;
      this->m_entity->left = false;
      this->m_pDirection =
        this->m_entity->getPosition().x >= this->m_patrolTo ? LEFT : RIGHT;
      break;
  }
}

}
}
