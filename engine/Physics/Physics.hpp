#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

#include "../Entity/Entity.hpp"
#include "../EntityFactory/EntityFactory.hpp"
#include "../TileManager/TileManager.hpp"

namespace Engine::Physics {

/**
 * Manages collision between an entity and the game window boundaries.
 *
 * @param window The game window.
 * @param entity The entity to manage collision for.
 */
auto
manageWindowCollision(const sf::RenderWindow& window, Entity& entity) -> void;

/**
 * Manages collision between an entity and the game tile map.
 *
 * @param ef The entity factory.
 * @param tm The tile manager.
 */
auto
manageTileMapCollision(const Engine::EntityFactory& ef,
                       const Engine::TileManager& tm) -> void;

/**
 * Checks if two bounding rectangles are colliding.
 *
 * @param pos1 The position and size of the first bounding rectangle.
 * @param pos2 The position and size of the second bounding rectangle.
 * @return True if the rectangles are colliding, false otherwise.
 */
auto
isColliding(const sf::FloatRect& pos1, const sf::FloatRect& pos2) -> bool;

/**
 * Checks if there is a collision overlap between two bounding rectangles.
 *
 * @param overlap The overlap between the two rectangles.
 * @return True if there is a collision overlap, false otherwise.
 */
auto
isColliding(const sf::Vector2f& overlap) -> bool;

/**
 * Calculates the overlap between two bounding rectangles.
 *
 * @param pos1 The position and size of the first bounding rectangle.
 * @param pos2 The position and size of the second bounding rectangle.
 * @return The overlap between the two rectangles.
 */
auto
getCollisionOverlap(const sf::FloatRect& pos1, const sf::FloatRect& pos2)
  -> sf::Vector2f;

}
