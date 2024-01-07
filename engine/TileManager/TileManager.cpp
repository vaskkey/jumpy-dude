#include "SFML/Graphics/RenderTarget.hpp"
#include "TileManager.hpp"

namespace Engine {

TileManager::TileManager() {}

TileManager::~TileManager()
{
  for (auto tile : this->m_tiles) {
    delete tile;
  }
}

auto
TileManager::createTile(TILE_TYPE type) -> Tile*
{
  switch (type) {
    case TILE_TYPE::BASIC:
      return this->m_getBasic();
  }
}

auto
TileManager::renderTiles(sf::RenderTarget& target) const -> void
{
  for (auto tile : this->m_tiles) {
    tile->render(target);
  }
}

auto
TileManager::getTiles() const -> const std::vector<Tile*>&
{
  return this->m_tiles;
}

auto
TileManager::m_getBasic() -> Tile*
{
  auto basicTile = new Tile();

  this->m_tiles.push_back(basicTile);

  return basicTile;
}
}
