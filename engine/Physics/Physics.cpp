#include "Physics.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include <complex>
#include <iostream>

auto
getCenter(sf::FloatRect box) -> sf::Vector2f
{
  auto xy = box.getPosition();
  auto wh = box.getSize();

  return xy + (wh / 2.f);
}

namespace Engine::Physics {

auto
manageWindowCollision(const sf::RenderWindow& window, Entity& entity) -> void
{
  int winY = window.getSize().y;
  int entityBottom = entity.getBox().height + entity.getBox().top;
  int entityLeft = entity.getBox().left;

  if (winY < entityBottom) {
    entity.moveTo(sf::Vector2f(entity.position().x,
                               window.getSize().y - entity.getBox().height));
    entity.land();
  }

  if (entityLeft < 0) {
    entity.moveTo(sf::Vector2f(0, entity.position().y));
  }
}

auto
manageTileMapCollision(const Engine::EntityFactory& ef,
                       const Engine::TileManager& tm) -> void
{
  for (auto entity : ef.getEntities()) {
    for (auto tile : tm.getTiles()) {
      auto overlap = getCollisionOverlap(entity->getBox(), tile->getBox());
      bool collides = isColliding(overlap);

      if (!collides)
        continue;

      // Get previous overlap to determine the direction
      auto prevOverlap =
        getCollisionOverlap(entity->getPreviousBox(), tile->getBox());

      if (prevOverlap.y <= 0) {
        overlap.x = 0;
        overlap.y *= entity->velocity().y > 0 ? -1 : 1;
        entity->moveBy(overlap);

        if (overlap.y < 0)
          entity->land();

      } else if (prevOverlap.x <= 0) {
        overlap.y = 0;
        overlap.x *= entity->velocity().x > 0 ? -1 : 1;
        entity->moveBy(overlap);
      } else {
        entity->moveBy(overlap);
      }
    }
  }
}

auto
isColliding(const sf::FloatRect& boundingBox1,
            const sf::FloatRect& boundingBox2) -> bool
{
  auto overlap = Physics::getCollisionOverlap(boundingBox1, boundingBox2);

  return isColliding(overlap);
};

auto
isColliding(const sf::Vector2f& overlap) -> bool
{
  return overlap.x > 0 && overlap.y > 0;
};

auto
getCollisionOverlap(const sf::FloatRect& boundingBox1,
                    const sf::FloatRect& boundingBox2) -> sf::Vector2f
{
  // AABB
  auto center1 = getCenter(boundingBox1);
  auto center2 = getCenter(boundingBox2);

  auto dx = std::abs(center2.x - center1.x);
  auto dy = std::abs(center2.y - center1.y);

  auto overlapX = (boundingBox2.width / 2) + (boundingBox1.width / 2) - dx;
  auto overlapY = (boundingBox2.height / 2) + (boundingBox1.height / 2) - dy;

  return sf::Vector2f(overlapX, overlapY);
}
}
