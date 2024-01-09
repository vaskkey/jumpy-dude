#include "Tile.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"
#include <iostream>

namespace Engine {

Tile::Tile()
  : m_position(200, 550)
  , m_boundingBox(m_position, sf::Vector2f(100, 10))
{
  this->m_texture.loadFromFile("static/tileset.png");
  this->m_sprite.setTextureRect(sf::IntRect(0, 0, 96, 23));
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
}
