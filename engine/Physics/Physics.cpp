#include "Physics.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Physics {

auto
manageWindowCollision(const sf::RenderWindow& window, Entity& entity) -> void
{
  int winY = window.getSize().y;
  int entityBottom = entity.getBox().height + entity.getBox().top;
  int entityLeft = entity.getBox().left;

  if (winY < entityBottom) {
    entity.land(winY - entity.getBox().height);
  }

  if (entityLeft < 0) {
    entity.fixLeft();
  }
}

}
