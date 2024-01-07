#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine {

class Tile {
  sf::Vector2f m_position;
  sf::FloatRect m_boundingBox;
  sf::Texture m_texture;
  sf::Sprite m_sprite;

	public:
	Tile();

  auto render(sf::RenderTarget& target) -> void;
  auto getBox() const -> const sf::FloatRect&;
};

}

