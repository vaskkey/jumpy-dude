#pragma once

#include "map"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components {
enum ENTITY_STATE
{
  STILL,
  WALKING_RIGHT,
  WALKING_LEFT
};

class Animation
{
  sf::Sprite m_sprite;
  sf::Texture m_texture;
  sf::IntRect m_intRect;
  sf::Clock m_animTimer;

  std::map<ENTITY_STATE, int> m_frames;

  float m_scale = 1;
  float m_origin = 0;

  int m_frame = 6;

public:
  Animation();

  auto setTexture(const std::string& file) -> Animation*;
  auto setTextureSize(const int width, const int height) -> Animation*;
  auto initSprite() -> Animation*;
  auto animate(const ENTITY_STATE& state) -> Animation*;
  auto move(const sf::Vector2f& position) -> Animation*;

  auto setFrames(ENTITY_STATE state, int numOfFrames) -> Animation*;

  auto getSprite() const -> const sf::Sprite&;

private:
  auto m_walkingAnimation() -> void;
  auto m_stillAnimation() -> void;
};
}
