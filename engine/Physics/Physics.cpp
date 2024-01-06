#include "Physics.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>

namespace Engine::Physics {

auto
manageWindowCollision(const sf::RenderWindow& window, Entity& entity) -> void
{
    int winY = window.getSize().y;
    int entityBottom = entity.getBox().height + entity.getBox().top;

    if (winY < entityBottom) {
      entity.land(winY - entity.getBox().height);
    }
}

}
