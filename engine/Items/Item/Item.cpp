#include "Item.hpp"

namespace Engine {

namespace Items {

Item::Item(const sf::Vector2f& position)
  : m_position(position)
{
}

Item::~Item() {}

auto
Item::render(sf::RenderTarget& target) -> void
{
  this->m_sprite.setPosition(this->m_position);
  target.draw(this->m_sprite);
}

auto
Item::getBox() const -> const sf::FloatRect&
{
  return this->m_boundingBox;
}
}
}
