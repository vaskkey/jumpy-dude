#pragma once

#include "../Tile/Tile.hpp"
#include <vector>

namespace Engine {

enum TILE_TYPE
{
  BASIC
};
class TileManager
{
  std::vector<Tile*> m_tiles;

public:
  TileManager();
  ~TileManager();

  auto createTile(TILE_TYPE type) -> Tile*;
  auto renderTiles(sf::RenderTarget& target) const -> void;

  auto getTiles() const -> const std::vector<Tile*>&;

private:
  auto m_getBasic() -> Tile*;
};

}
