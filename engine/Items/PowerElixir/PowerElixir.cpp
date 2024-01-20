#include "PowerElixir.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine {

namespace Items {
PowerElixir::PowerElixir(const sf::Vector2f& position)
  : Item(position)
{
  this->m_texture.loadFromFile("static/power-elixir.png");
  this->m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
  this->m_sprite.setTexture(this->m_texture);
  this->m_boundingBox = sf::FloatRect(position, { 16, 16 });
}

auto
PowerElixir::call(Entity* player) -> void
{
  player->setPower(player->getPower() + 1);
}

}
}
