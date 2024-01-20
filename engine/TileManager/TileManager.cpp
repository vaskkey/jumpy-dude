#include "TileManager.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include <fstream>

namespace Engine {

TileManager::TileManager() {}

TileManager::~TileManager()
{
  for (auto tile : this->m_tiles) {
    delete tile;
  }
}

auto
TileManager::init() -> void
{
  auto file = std::ifstream("configs/map.txt");

  int t;
  float x, y;

  while (file >> t >> x >> y) {
    auto type = static_cast<TILE_TYPE>(t);
    this->createTile(type, { x, y });
  }
}

auto
TileManager::createTile(TILE_TYPE type, const sf::Vector2f& position) -> Tile*
{
  switch (type) {
    case TILE_TYPE::BASIC:
      return this->m_getBasic(position);
    case BASIC_FILL:
      return this->m_getBasicFill(position);
      break;
    case BASIC_HALF:
      return this->m_getBasicHalf(position);
      break;
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
TileManager::m_getBasic(const sf::Vector2f& position) -> Tile*
{
  auto basicTile = new Tile(position);
  basicTile->setTexture("static/tileset.png")
    ->setTextureBox(sf::IntRect(0, 0, 96, 23))
    ->setBox({ 96, 10 });

  this->m_tiles.push_back(basicTile);

  return basicTile;
}

auto
TileManager::m_getBasicFill(const sf::Vector2f& position) -> Tile*
{
  auto basicTile = new Tile(position);
  basicTile->setTexture("static/tileset.png")
    ->setTextureBox(sf::IntRect(0, 25, 47, 23))
    ->setBox({ 47, 10 });

  this->m_tiles.push_back(basicTile);

  return basicTile;
}

auto
TileManager::m_getBasicHalf(const sf::Vector2f& position) -> Tile*
{
  auto basicTile = new Tile(position);
  basicTile->setTexture("static/tileset.png")
    ->setTextureBox(sf::IntRect(0, 0, 47, 23))
    ->setBox({ 50, 10 });

  this->m_tiles.push_back(basicTile);

  return basicTile;
}
}
