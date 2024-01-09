#pragma once

#include "../Entity/Entity.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "ranges"

namespace Engine {
/**
 * Enumeration of entity types.
 */
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

  /**
   * Creates an entity of the specified type.
   *
   * @param type The type of entity to create.
   * @return Pointer to the created entity.
   */
  auto createEntity(ENTITY_TYPE type) -> Entity*;

  /**
   * Renders all entities on the specified render target.
   *
   * @param target The render target to render the entities on.
   */
  auto renderEntities(sf::RenderTarget& target) const -> void;

  /**
   * Updates all entities based on the specified window.
   *
   * @param window The window used for updating the entities.
   */
  auto updateEntities(sf::RenderWindow& window) -> void;

  /**
   * Retrieves the vector of entities created by the factory.
   *
   * @return The vector of entities.
   */
  auto getEntities() const -> const std::vector<Entity*>&;

private:
  /**
   * Creates a new player entity.
   *
   * @return Pointer to the created player entity.
   */
  auto m_getPlayer() -> Entity*;

  /**
   * Creates a new mushroom entity.
   *
   * @return Pointer to the created mushroom entity.
   */
  auto m_getMushroom() -> Entity*;

  /**
   * Manages the attacks of the specified entity.
   *
   * @param entity The entity to manage attacks for.
   */
  auto m_manageAttacks(Entity* entity) -> void;

  /**
   * Cleans up and removes dead entities from the vector.
   */
  auto m_cleanupDeadEntities() -> void;
};

}
