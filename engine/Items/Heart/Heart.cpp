#include "Heart.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine {

namespace Items {
Heart::Heart(const sf::Vector2f& position)
  : Item(position)
{
  this->m_texture.loadFromFile("static/heart.png");
  this->m_sprite.setTextureRect(sf::IntRect(0, 0, 13, 12));
  this->m_sprite.setTexture(this->m_texture);
  this->m_boundingBox = sf::FloatRect(position, { 13, 12 });
}

auto
Heart::call(Entity* player) -> void
{
  int hp = player->hp + 10;
  player->hp = hp >= 100 ? 100 : hp;
}

}
}
