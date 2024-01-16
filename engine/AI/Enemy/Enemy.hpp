#pragma once

#include "../../Entity/Entity.hpp"

namespace Engine {

namespace AI {
enum PATROLING_DIRECTION
{
  LEFT,
  RIGHT
};

class Enemy
{
  Entity* m_entity;          /**< Entity controlled by this AI */
  float m_patrolFrom = 0;    /**< Starting point of patrolling */
  float m_patrolTo = 0;      /**< End point of patrolling */
  bool m_patrolling = false; /**< Whether entity should be patrolling */

  PATROLING_DIRECTION m_pDirection; /**< Direction Entity should be walking */

public:
  Enemy(Entity* entity);

  /**
   * Set patrolling properties for an Entity
   *
   * @param from Where Entity should start
   * @param to Where Entity should turn back
   */
  auto setPatrol(float from, float to) -> void;
  /**
   * Starts patrolling if properties have been set
   */
  auto patrol() -> void;

  /**
   * A shorthand to determine if this AI controlls a given Entity
   */
  auto operator==(Entity* ent) -> bool;

private:
  /**
   * Manages Entity direction depending on which point it has crossed
   */
  auto m_manageDirection() -> void;
};

}

}
