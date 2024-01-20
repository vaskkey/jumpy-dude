#pragma once

#include "../Item/Item.hpp"
#include <vector>

namespace Engine {

namespace Items {
enum ITEM_TYPE
{
  HEART,
  SPEED_ELIXIR,
  POWER_ELIXIR
};

class ItemManager
{
  std::vector<Item*>
    m_items; /**< Vector of items managed by the ItemManager. */
public:
  ItemManager();
  ~ItemManager();

  /**
   * Reads from items.txt config and creates items
   */
  auto init() -> void;

  /**
   * Renders all items on the specified render target.
   *
   * @param target The render target to render the items on.
   */
  auto renderItems(sf::RenderTarget& target) const -> void;

  /**
   * Checks if player entity is in position to collect an item.
   *
   * @param player Pointer to player entity.
   */
  auto updateItems(Entity* player) -> void;

private:
  /**
   * Creates an item of the specified type.
   *
   * @param type The type of tile to create.
   * @param position Position of the Tile.
   * @return Pointer to the created tile.
   */
  auto m_createItem(ITEM_TYPE type, const sf::Vector2f& position) -> Item*;

  /**
   * Creates a heart that refills player's HP.
   *
   * @param position Position of the Heart.
   * @return Pointer to the created heart.
   */
  auto m_getHeart(const sf::Vector2f& position) -> Item*;

  /**
   * Creates an elixir that increases player's speed.
   *
   * @param position Position of the Elixir.
   * @return Pointer to the created elixir.
   */
  auto m_getSpeedElixir(const sf::Vector2f& position) -> Item*;

  /**
   * Creates an elixir that increases player's damaging power.
   *
   * @param position Position of the Elixir.
   * @return Pointer to the created elixir.
   */
  auto m_getPowerElixir(const sf::Vector2f& position) -> Item*;

  /**
   * Removes item from vector and deletes its pointer.
   *
   * @param item Pointer to an item.
   */
  auto m_deleteItem(Item* item) -> void;
};

}

}
