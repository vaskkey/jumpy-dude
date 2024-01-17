#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include "Tile.hpp"
#include <iostream>

namespace Engine {

Tile::Tile(const sf::Vector2f& position)
  : m_position(position)
  , m_boundingBox(m_position, { 0, 0 })
{
  this->m_sprite.setTexture(this->m_texture);
}

auto
Tile::render(sf::RenderTarget& target) -> void
{
  this->m_sprite.setPosition(this->m_position);
  target.draw(this->m_sprite);
}

auto
Tile::getBox() const -> const sf::FloatRect&
{
  return this->m_boundingBox;
}

auto
Tile::setTexture(std::string name) -> Tile*
{
  this->m_texture.loadFromFile(name);

  return this;
}

auto
Tile::setBox(const sf::Vector2f& size) -> Tile*
{
  this->m_boundingBox.width = size.x;
  this->m_boundingBox.height = size.y;

  return this;
}

auto
Tile::setTextureBox(const sf::IntRect& rect) -> Tile*
{
  this->m_sprite.setTextureRect(rect);

  return this;
}
}
