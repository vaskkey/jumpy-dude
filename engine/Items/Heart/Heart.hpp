#pragma once

#include "../Item/Item.hpp"

namespace Engine {

namespace Items {

class Heart : public Item
{
public:
  Heart(const sf::Vector2f& position);

  /**
   * Performs items effect on the Player.
   *
   * @param player Pointer to the Player entity.
   */
  auto call(Entity* player) -> void override;
};

}
}
