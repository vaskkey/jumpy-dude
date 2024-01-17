#include "../Physics/Physics.hpp"
#include "EntityFactory.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include <__algorithm/remove.h>
#include <__algorithm/remove_if.h>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace Engine {

EntityFactory::EntityFactory() {}

EntityFactory::~EntityFactory()
{
  for (auto entity : this->m_entities) {
    delete entity;
  }
}

auto
EntityFactory::init() -> Entity*
{
  auto player = this->createEntity(ENTITY_TYPE::PLAYER);
  auto file = std::ifstream("entities.txt");

  int t;
  float from, to;

  while (file >> t >> from >> to) {
    auto type = static_cast<ENTITY_TYPE>(t);
    this->createEntity(type, from, to);
  }

  return player;
}

auto
EntityFactory::createEntity(ENTITY_TYPE type) -> Entity*
{
  switch (type) {
    case ENTITY_TYPE::PLAYER:
      return this->m_getPlayer();
    case ENTITY_TYPE::MUSHROOM:
      return this->m_getMushroom();
  }
}

auto
EntityFactory::createEntity(ENTITY_TYPE type, float from, float to) -> Entity*
{
  auto entity = this->createEntity(type);
  auto mushroomAI = new AI::Enemy(entity);
  mushroomAI->setPatrol(from, to);
  this->m_enemies.push_back(mushroomAI);
  return entity;
}

auto
EntityFactory::renderEntities(sf::RenderTarget& target) const -> void
{
  for (auto entity : this->m_entities) {
    entity->render(target);
  }
}

auto
EntityFactory::updateEntities(sf::RenderWindow& window, Entity* player) -> void
{
  this->m_cleanupDeadEntities();

  std::for_each(this->m_enemies.begin(), this->m_enemies.end(), [](auto enemy) {
    enemy->patrol();
  });

  for (auto entity : this->m_entities) {
    Physics::manageWindowCollision(window, *entity);

    entity->update();
    this->m_managePlayerDamage(player, entity);

    if (entity->getState() == Components::ENTITY_STATE::ATTACKING) {
      this->m_manageAttacks(entity);
    }
  }
}

auto
EntityFactory::getEntities() const -> const std::vector<Entity*>&
{
  return this->m_entities;
}

auto
EntityFactory::m_getPlayer() -> Entity*
{
  auto player = new Entity(3, 5, 100);
  player->setBoundingBox(56, 56);
  player->c_animation.setTexture("static/main-char-1.png")
    ->setTextureSize(56, 56)

    ->setFrames(Components::ENTITY_STATE::STILL, 1, 0)
    ->setFrames(Components::ENTITY_STATE::WALKING_LEFT, 8, 0)
    ->setFrames(Components::ENTITY_STATE::WALKING_RIGHT, 8, 0)
    ->setFrames(Components::ENTITY_STATE::ATTACKING, 8, 4)

    ->setAnimationTimeout(50)

    ->initSprite()
    ->animate(player->getState(), player->getFacingDirection());

  this->m_entities.push_back(player);
  return player;
}

auto
EntityFactory::m_getMushroom() -> Entity*
{
  auto mushroom = new Entity(2, 1, 10);
  mushroom->setBoundingBox(56, 56);
  mushroom->c_animation.setTexture("static/mushroom-1.png")
    ->setTextureSize(56, 56)

    ->setFrames(Components::ENTITY_STATE::STILL, 4, 0)
    ->setFrames(Components::ENTITY_STATE::WALKING_LEFT, 6, 1)
    ->setFrames(Components::ENTITY_STATE::WALKING_RIGHT, 6, 1)
    ->setAnimationTimeout(100)

    ->initSprite()
    ->animate(mushroom->getState(), mushroom->getFacingDirection());

  this->m_entities.push_back(mushroom);

  return mushroom;
}

auto
EntityFactory::m_manageAttacks(Entity* entity) -> void
{
  sf::FloatRect attack;
  attack.width = 1;
  attack.height = entity->getBox().height;
  attack.top = entity->getBox().top;

  switch (entity->getFacingDirection()) {
    case Components::RIGHT:
      attack.left = entity->getBox().left + entity->getBox().width;
    case Components::LEFT:
      attack.left = entity->getBox().left - attack.width;
      break;
  }

  for (auto ent : this->m_entities) {
    if (ent != entity && Physics::isColliding(ent->getBox(), attack)) {
      ent->takeDamage(entity->DAMAGE);
    }
  }
}

auto
EntityFactory::m_managePlayerDamage(Entity* player, Entity* entity) -> void
{
  if (player == entity)
    return;

  if (Physics::isColliding(player->getBox(), entity->getBox())) {
    player->takeDamage(entity->DAMAGE);
  }
}

auto
EntityFactory::m_cleanupDeadEntities() -> void
{
  auto iter = std::remove_if(
    this->m_entities.begin(), this->m_entities.end(), [this](auto ent) -> bool {
      bool toBeDeleted = ent->hp <= 0;

      if (toBeDeleted) {
        this->m_removeEnemy(ent);
        delete ent;
      }

      return toBeDeleted;
    });

  this->m_entities.erase(iter, this->m_entities.end());
}

auto
EntityFactory::m_removeEnemy(Entity* ent) -> void
{
  auto iter = std::remove_if(
    this->m_enemies.begin(), this->m_enemies.end(), [ent](auto enemy) -> bool {
      bool toBeDeleted = *enemy == ent;

      if (toBeDeleted)
        delete enemy;

      return toBeDeleted;
    });

  this->m_enemies.erase(iter, this->m_enemies.end());
}
}
