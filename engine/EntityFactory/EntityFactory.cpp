#include "EntityFactory.hpp"
#include "../Physics/Physics.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include <__algorithm/remove.h>
#include <__algorithm/remove_if.h>
#include <algorithm>
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
EntityFactory::renderEntities(sf::RenderTarget& target) const -> void
{
  for (auto entity : this->m_entities) {
    entity->render(target);
  }
}

auto
EntityFactory::updateEntities(sf::RenderWindow& window) -> void
{
  this->m_cleanupDeadEntities();

  for (auto entity : this->m_entities) {
    Physics::manageWindowCollision(window, *entity);

    entity->update();

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
  auto mushroom = new Entity(2, 0, 50);
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
      ent->hp -= entity->DAMAGE;
    }
  }
}

auto
EntityFactory::m_cleanupDeadEntities() -> void
{
  auto iter = std::remove_if(
    this->m_entities.begin(), this->m_entities.end(), [](auto ent) -> bool {
      bool toBeDeleted = ent->hp <= 0;

      if (toBeDeleted)
        delete ent;

      return toBeDeleted;
    });

  this->m_entities.erase(iter, this->m_entities.end());
}
}
