#pragma once

#include "../AI/Enemy/Enemy.hpp"
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
  std::vector<Entity*> m_entities;   /**< A vector of all entities. */
  std::vector<AI::Enemy*> m_enemies; /**< A vector of Enemy AI's. */

public:
  EntityFactory();
  ~EntityFactory();

  /**
   * Initiates entities from the file
   *
   */
  auto init() -> Entity*;

  /**
   * Creates an entity of the specified type.
   *
   * @param type The type of entity to create.
   * @return Pointer to the created entity.
   */
  auto createEntity(ENTITY_TYPE type) -> Entity*;

  /**
   * Creates an entity of the specified type.
   *
   * @param type The type of entity to create.
   * @param from Where entity starts
   * @param to To which point entity patrols
   * @return Pointer to the created entity.
   */
  auto createEntity(ENTITY_TYPE type, float from, float to) -> Entity*;

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
   * @param player Player entity
   */
  auto updateEntities(sf::RenderWindow& window, Entity* player) -> void;

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
   * Manage player taking damage
   *
   * @param player The player to deal damage to
   * @param entity The entity to manage attacks for.
   */
  auto m_managePlayerDamage(Entity* player, Entity* entity) -> void;

  /**
   * Cleans up and removes dead entities from the vector.
   */
  auto m_cleanupDeadEntities() -> void;

  /**
   * Removes AI for dead entities
   */
  auto m_removeEnemy(Entity* ent) -> void;
};

}
