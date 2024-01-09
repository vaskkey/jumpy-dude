#pragma once

#include "map"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"

namespace Engine::Components {

/**
 * Enumeration of entity states.
 */
enum ENTITY_STATE
{
  STILL,
  WALKING_RIGHT,
  WALKING_LEFT,
  ATTACKING
};

/**
 * Enumeration of entity facing directions.
 */
enum ENTITY_FACING
{
  RIGHT,
  LEFT
};

/**
 * Animation class for animating entities in a game.
 */
class Animation
{
  sf::Sprite m_sprite;   /**< The sprite used for animation. */
  sf::Texture m_texture; /**< The texture used for animation. */
  sf::IntRect m_intRect; /**< The rectangle defining the size of the texture. */
  sf::Clock m_animTimer; /**< Timer for controlling the animation timing. */

  int m_animationTimeout; /**< The timeout duration between animations. */

  std::map<ENTITY_STATE, int>
    m_frames; /**< Map of frames for each entity state. */
  std::map<ENTITY_STATE, int>
    m_verticalOffset; /**< Map of vertical offsets for each entity state. */

  float m_scale = 1;  /**< The scale of the sprite. Used to flip the asset */
  float m_origin = 0; /**< The origin of the sprite. Used to flip the asset */

  int m_frame = 6; /**< The current frame of the animation. */

public:
  Animation();

  /**
   * Sets the texture of the animation.
   *
   * @param file The file path of the texture.
   * @return Pointer to the current Animation object.
   */
  auto setTexture(const std::string& file) -> Animation*;

  /**
   * Sets the size of the texture.
   *
   * @param width The width of the texture.
   * @param height The height of the texture.
   * @return Pointer to the current Animation object.
   */
  auto setTextureSize(const int width, const int height) -> Animation*;

  /**
   * Initializes the sprite with the loaded texture.
   *
   * @return Pointer to the current Animation object.
   */
  auto initSprite() -> Animation*;

  /**
   * Animates the entity based on its state and facing direction.
   *
   * @param state The state of the entity.
   * @param direction The facing direction of the entity.
   * @return Pointer to the current Animation object.
   */
  auto animate(ENTITY_STATE state, ENTITY_FACING direction) -> Animation*;

  /**
   * Moves the animation to a new position.
   *
   * @param position The new position of the animation.
   * @return Pointer to the current Animation object.
   */
  auto move(const sf::Vector2f& position) -> Animation*;

  /**
   * Sets the timeout duration between animations.
   *
   * @param timeout The timeout duration in milliseconds.
   * @return Pointer to the current Animation object.
   */
  auto setAnimationTimeout(int timeout) -> Animation*;

  /**
   * Sets the number of frames and vertical offset for a specific entity state.
   *
   * @param state The entity state.
   * @param numOfFrames The number of frames for the state.
   * @param offsetY The vertical offset for the sprite.
   * @return Pointer to the current Animation object.
   */
  auto setFrames(ENTITY_STATE state, int numOfFrames, int offsetY)
    -> Animation*;

  /**
   * Retrieves the sprite used for animation.
   *
   * @return The sprite used for animation.
   */
  auto getSprite() const -> const sf::Sprite&;

private:
  /**
   * Plays the animation based on the entity's state.
   *
   * @param state The state of the entity.
   */
  auto m_playAnimation(ENTITY_STATE state) -> void;

  /**
   * Sets the direction of the animation based on the entity's facing direction.
   *
   * @param direction The facing direction of the entity.
   */
  auto m_setDirection(ENTITY_FACING direction) -> void;
};

}
