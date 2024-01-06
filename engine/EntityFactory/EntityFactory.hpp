#pragma once

#include "../Entity/Entity.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "ranges"

namespace Engine {
enum ENTITY_TYPE
{
  PLAYER,
  MUSHROOM
};

class EntityFactory
{
  std::vector<Entity*> m_entities;

public:
  EntityFactory();
  ~EntityFactory();

  auto createEntity(ENTITY_TYPE type) -> Entity*;
  auto renderEntities(sf::RenderTarget& target) -> void;
  auto updateEntities(sf::RenderWindow& window) -> void;

private:
  auto m_getPlayer() -> Entity*;
  auto m_getMushroom() -> Entity*;
};

}
