#pragma once

#include "../Tile/Tile.hpp"
#include <vector>

namespace Engine {

enum TILE_TYPE
{
  BASIC
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
   * Creates a tile of the specified type.
   *
   * @param type The type of tile to create.
   * @return Pointer to the created tile.
   */
  auto createTile(TILE_TYPE type) -> Tile*;

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
   * @return Pointer to the created basic tile.
   */
  auto m_getBasic() -> Tile*;
};

}
