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
  Tile(const sf::Vector2f& position);

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

  /**
   * Sets the texture of the tile.
   *
   * @param name Name of texture file.
   * @return The Tile.
   */
  auto setTexture(std::string name) -> Tile*;

  /**
   * Sets the bounding box of the tile.
   *
   * @param size Size of a bounding box.
   * @return The Tile.
   */
  auto setBox(const sf::Vector2f& size) -> Tile*;

  /**
   * Sets texture rectangle, used for sprites that have more than one tile on
   * them.
   *
   * @param rect Rectangle with size and position of texture on the sprite
   * @return The Tile
   */
  auto setTextureBox(const sf::IntRect& rect) -> Tile*;
};

}
