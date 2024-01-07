#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

#include "../Entity/Entity.hpp"
#include "../EntityFactory/EntityFactory.hpp"
#include "../TileManager/TileManager.hpp"

namespace Engine::Physics {

auto
manageWindowCollision(const sf::RenderWindow& window, Entity& entity) -> void;

auto
manageTileMapCollision(const Engine::EntityFactory& ef,
                       const Engine::TileManager& tm) -> void;

auto
isColliding(const sf::FloatRect& pos1, const sf::FloatRect& pos2) -> bool;

auto
isColliding(const sf::Vector2f& overlap) -> bool;

auto
getCollisionOverlap(const sf::FloatRect& pos1, const sf::FloatRect& pos2)
  -> sf::Vector2f;
}
