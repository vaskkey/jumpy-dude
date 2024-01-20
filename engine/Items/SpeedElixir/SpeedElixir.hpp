#pragma once

#include "../Item/Item.hpp"

namespace Engine {

namespace Items {

class SpeedElixir : public Item
{
public:
  SpeedElixir(const sf::Vector2f& position);

  /**
   * Performs items effect on the Player.
   *
   * @param player Pointer to the Player entity.
   */
  auto call(Entity* player) -> void override;
};

}
}
