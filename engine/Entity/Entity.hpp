#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

#include "../Components/Animation/Animation.hpp"

namespace Engine {
/**
 * Entity class representing a game entity.
 */
class Entity
{
  sf::Vector2f m_position;     /**< The position of the entity. */
  sf::Vector2f m_velocity;     /**< The velocity of the entity. */
  sf::FloatRect m_boundingBox; /**< The bounding box of the entity. */
  sf::FloatRect m_prevBox;     /**< The previous bounding box of the entity. */
  sf::Clock m_damageTimer;     /**< Timer for entity taking damage */

  Components::ENTITY_STATE m_state =
    Components::ENTITY_STATE::STILL; /**< The state of the entity. */
  Components::ENTITY_FACING m_facingDirection =
    Components::ENTITY_FACING::LEFT; /**< The facing direction of the entity. */

  const float m_maxVelocity = 10; /**< The maximum velocity of the entity. */
  const float m_minVelocity = .2; /**< The minimum velocity of the entity. */
  const float m_acceleration = 1; /**< The acceleration of the entity. */
  const float m_drag = 0.95; /**< The drag applied to the entity's velocity. */
  const float m_gravity = 2; /**< The gravity applied to the entity. */
  const float m_maxYVelocity =
    20; /**< The maximum vertical velocity of the entity. */

  bool m_grounded = false;    /**< Flag indicating if the entity is grounded. */
  float m_jumpedDistance = 0; /**< The distance the entity has jumped. */

  const int m_speed; /**< The speed of the entity. */

public:
  Components::Animation
    c_animation; /**< The animation component of the entity. */
  bool up = false, down = false, left = false, right = false,
       attacking = false; /**< Flags indicating the movement and attack state of
                             the entity. */

  const int DAMAGE; /**< The damage inflicted by the entity. */
  int hp;           /**< The hit points of the entity. */

  /**
   * Constructor for the Entity class.
   *
   * @param speed The speed of the entity.
   * @param damage The damage inflicted by the entity.
   * @param hp The hit points of the entity.
   */
  Entity(int speed, int damage, int hp);

  /**
   * Updates the entity's state and position.
   */
  auto update() -> void;

  /**
   * Renders the entity on the target.
   *
   * @param target The render target.
   */
  auto render(sf::RenderTarget& target) -> void;

  /**
   * Retrieves the state of the entity.
   *
   * @return The state of the entity.
   */
  auto getState() const -> Components::ENTITY_STATE;

  /**
   * Retrieves the facing direction of the entity.
   *
   * @return The facing direction of the entity.
   */
  auto getFacingDirection() const -> Components::ENTITY_FACING;

  /**
   * Retrieves the bounding box of the entity.
   *
   * @return The bounding box of the entity.
   */
  auto getBox() const -> const sf::FloatRect&;

  /**
   * Retrieves the previous bounding box of the entity.
   *
   * @return The previous bounding box of the entity.
   */
  auto getPreviousBox() const -> const sf::FloatRect&;

  /**
   * Retrieves the position of the entity.
   *
   * @return The position of the entity.
   */
  auto position() const -> const sf::Vector2f&;

  /**
   * Retrieves the grounded state of the entity.
   *
   * @return True if the entity is grounded, false otherwise.
   */
  auto getGrounded() const -> bool;

  /**
   * Retrieves the velocity of the entity.
   *
   * @return The velocity of the entity.
   */
  auto velocity() const -> const sf::Vector2f&;

  /**
   * Moves the entity to a specific position.
   *
   * @param position The position to move the entity to.
   */
  auto moveTo(const sf::Vector2f& position) -> void;

  /**
   * Moves the entity by a specific distance.
   *
   * @param distance The distance to move the entity by.
   */
  auto moveBy(const sf::Vector2f& distance) -> void;

  /**
   * Sets the grounded state of the entity.
   */
  auto land() -> void;

  /**
   * Sets the bounding box size of the entity.
   *
   * @param width The width of the bounding box.
   * @param height The height of the bounding box.
   */
  auto setBoundingBox(int width, int height) -> void;

  /**
   * Inflicts damage to the entity.
   *
   * @param damage The amount of damage to inflict.
   */
  auto takeDamage(int damage) -> void;

  /**
   * Gets Entity's current position
   *
   * @return Vector representing current position
   */
  auto getPosition() const -> const sf::Vector2f&;

private:
  /**
   * Moves the entity based on its velocity.
   */
  auto m_move() -> void;

  /**
   * Sets the state of the entity based on its movement flags.
   */
  auto m_setState() -> void;

  /**
   * Manages the gravity effect on the entity.
   */
  auto m_manageGravity() -> void;

  /**
   * Checks if the entity is currently moving.
   *
   * @return True if the entity is moving, false otherwise.
   */
  auto m_isMoving() const -> bool;
};

}
