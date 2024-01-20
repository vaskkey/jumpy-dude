#pragma once

#include "../Item/Item.hpp"

namespace Engine {

namespace Items {

class PowerElixir : public Item
{
public:
  PowerElixir(const sf::Vector2f& position);

  /**
   * Performs items effect on the Player.
   *
   * @param player Pointer to the Player entity.
   */
  auto call(Entity* player) -> void override;
};

}
}
