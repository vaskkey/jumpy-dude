#pragma once
#include "SFML/System/Vector2.hpp"
#pragma once
#include "../../Components/Animation/Animation.hpp"
#include "../../Entity/Entity.hpp"
#include "SFML/Graphics/Rect.hpp"

namespace Engine {

namespace Items {

class Item
{
protected:
  sf::Vector2f m_position;     /**< Position of the item. */
  sf::FloatRect m_boundingBox; /**< Bounding box of the item. */
  sf::Texture m_texture;       /**< Texture of the item. */
  sf::Sprite m_sprite;         /**< Sprite of the item. */

public:
  /**
   * @param pos Vector representing a position
   */
  Item(const sf::Vector2f& position);

  virtual ~Item();

  /**
   * Renders the item.
   */
  auto render(sf::RenderTarget& target) -> void;

  /**
   * Retrieves the bounding box of the tile.
   *
   * @return The bounding box of the tile.
   */
  auto getBox() const -> const sf::FloatRect&;

  /**
   * Performs items effect on the Player.
   *
   * @param player Pointer to the Player entity.
   */
  virtual auto call(Entity* player) -> void = 0;
};

}

}
