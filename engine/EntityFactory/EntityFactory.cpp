#include "../Physics/Physics.hpp"
#include "EntityFactory.hpp"

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
  for (auto entity : this->m_entities) {
    Physics::manageWindowCollision(window, *entity);
    entity->update();
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
  auto player = new Entity(3);
  player->setBoundingBox(56, 56);
  player->c_animation.setTexture("static/main-char-1.png")
    ->setTextureSize(56, 56)

    ->setFrames(Components::ENTITY_STATE::STILL, 1, 0)
    ->setFrames(Components::ENTITY_STATE::WALKING_LEFT, 8, 0)
    ->setFrames(Components::ENTITY_STATE::WALKING_RIGHT, 8, 0)

    ->setAnimationTimeut(50)

    ->initSprite()
    ->animate(player->getState());

  this->m_entities.push_back(player);
  return player;
}

auto
EntityFactory::m_getMushroom() -> Entity*
{
  auto mushroom = new Entity(2);
  mushroom->setBoundingBox(56, 56);
  mushroom->c_animation.setTexture("static/mushroom-1.png")
    ->setTextureSize(56, 56)

    ->setFrames(Components::ENTITY_STATE::STILL, 4, 0)
    ->setFrames(Components::ENTITY_STATE::WALKING_LEFT, 6, 1)
    ->setFrames(Components::ENTITY_STATE::WALKING_RIGHT, 6, 1)
    ->setAnimationTimeut(100)

    ->initSprite()
    ->animate(mushroom->getState());

  this->m_entities.push_back(mushroom);
  return mushroom;
}

}
