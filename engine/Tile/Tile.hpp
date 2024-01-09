#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine {

/**
 * Tile class representing a single tile in the game.
 */
class Tile
{
  sf::Vector2f m_position;     /**< Position of the tile. */
  sf::FloatRect m_boundingBox; /**< Bounding box of the tile. */
  sf::Texture m_texture;       /**< Texture of the tile. */
  sf::Sprite m_sprite;         /**< Sprite of the tile. */

public:
  /**
   * Constructor for the Tile class.
   */
  Tile();

  /**
   * Renders the tile on the specified render target.
   *
   * @param target The render target to render the tile on.
   */
  auto render(sf::RenderTarget& target) -> void;

  /**
   * Retrieves the bounding box of the tile.
   *
   * @return The bounding box of the tile.
   */
  auto getBox() const -> const sf::FloatRect&;
};

}
