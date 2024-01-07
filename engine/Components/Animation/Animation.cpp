#include "Animation.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components {

Animation::Animation()
{
  this->m_animTimer.restart();
}

auto
Animation::animate(ENTITY_STATE state, ENTITY_FACING direction) -> Animation*
{
  if (this->m_animTimer.getElapsedTime().asMilliseconds() <
      this->m_animationTimeout)
    return this;

  this->m_setDirection(direction);
  this->m_playAnimation(state);

  this->m_animTimer.restart();
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

auto
Animation::m_playAnimation(ENTITY_STATE state) -> void
{
  int frames = this->m_frames.at(state);
  int offsetY = this->m_verticalOffset.at(state);

  if (++this->m_frame >= frames) {
    this->m_frame = 0;
  }

  this->m_intRect.left = this->m_intRect.width * this->m_frame;
  this->m_intRect.top = this->m_intRect.height * offsetY;
  this->m_sprite.setScale(this->m_scale, 1);
  this->m_sprite.setOrigin(this->m_origin, 0);
}

auto
Animation::setFrames(ENTITY_STATE state, int numOfFrames, int offsetY)
  -> Animation*
{
  this->m_frames[state] = numOfFrames;
  this->m_verticalOffset[state] = offsetY;
  return this;
}

auto
Animation::setAnimationTimeout(int timeout) -> Animation*
{
  this->m_animationTimeout = timeout;
  return this;
}

auto
Animation::m_setDirection(ENTITY_FACING direction) -> void
{
  switch (direction) {
    case ENTITY_FACING::LEFT:
      this->m_scale = -1;
      this->m_origin = this->m_sprite.getGlobalBounds().width;
      break;
    case ENTITY_FACING::RIGHT:
      this->m_scale = 1;
      this->m_origin = 0;
  }
}
}
