#include "Animation.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components {

Animation::Animation()
{
  this->m_animTimer.restart();
}

auto
Animation::animate(const ENTITY_STATE& state) -> Animation*
{
  if (this->m_animTimer.getElapsedTime().asMilliseconds() < 100)
    return this;

  if (state == ENTITY_STATE::WALKING_LEFT ||
      state == ENTITY_STATE::WALKING_RIGHT) {
    if (++this->m_frame >= 8) {
      this->m_frame = 0;
    }

    this->m_intRect.left = this->m_intRect.width * this->m_frame;
  } else {
    this->m_intRect.left = 0;
  }

  this->m_animTimer.restart();
  this->m_sprite.setTextureRect(this->m_intRect);
  this->m_sprite.setTextureRect(this->m_intRect);
  return this;
}

auto
Animation::setTexture(const std::string& file) -> Animation*
{
  this->m_texture.loadFromFile(file);
  return this;
}

auto
Animation::setTextureSize(const int width, const int height) -> Animation*
{
  this->m_intRect.height = height;
  this->m_intRect.width = width;
  return this;
}

auto
Animation::initSprite() -> Animation*
{
  this->m_sprite.setTexture(this->m_texture);
  return this;
}

auto
Animation::getSprite() const -> const sf::Sprite&
{
  return this->m_sprite;
}

auto
Animation::move(const sf::Vector2f& position) -> Animation*
{
  this->m_sprite.setPosition(position);

  return this;
}
}
