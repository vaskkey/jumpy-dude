#pragma once

#include "../Tile/Tile.hpp"
#include "SFML/System/Vector2.hpp"
#include <vector>

namespace Engine {

enum TILE_TYPE
{
  BASIC,
  BASIC_FILL,
  BASIC_HALF,
};
/**
 * TileManager class responsible for managing tiles in the game.
 */
class TileManager
{
  std::vector<Tile*>
    m_tiles; /**< Vector of tiles managed by the TileManager. */

public:
  /**
   * Constructor for the TileManager class.
   */
  TileManager();

  /**
   * Destructor for the TileManager class.
   */
  ~TileManager();

  /**
   * Reads from map.txt config and creates tiles
   */
  auto init() -> void;

  /**
   * Creates a tile of the specified type.
   *
   * @param type The type of tile to create.
   * @param position Position of the Tile.
   * @return Pointer to the created tile.
   */
  auto createTile(TILE_TYPE type, const sf::Vector2f& position) -> Tile*;

  /**
   * Renders all tiles on the specified render target.
   *
   * @param target The render target to render the tiles on.
   */
  auto renderTiles(sf::RenderTarget& target) const -> void;

  /**
   * Retrieves the vector of tiles managed by the TileManager.
   *
   * @return The vector of tiles.
   */
  auto getTiles() const -> const std::vector<Tile*>&;

private:
  /**
   * Creates a basic tile.
   *
   * @param position Position of the Tile.
   * @return Pointer to the created basic tile.
   */
  auto m_getBasic(const sf::Vector2f& position) -> Tile*;

  /**
   * Creates a basic fill tile.
   *
   * @param position Position of the Tile.
   * @return Pointer to the created basic fill tile.
   */
  auto m_getBasicFill(const sf::Vector2f& position) -> Tile*;

  /**
   * Creates a basic half tile.
   *
   * @param position Position of the Tile.
   * @return Pointer to the created basic half tile.
   */
  auto m_getBasicHalf(const sf::Vector2f& position) -> Tile*;
};

}
