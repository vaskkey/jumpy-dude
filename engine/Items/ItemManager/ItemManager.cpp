#include "../../Physics/Physics.hpp"
#include "../Heart/Heart.hpp"
#include "../PowerElixir/PowerElixir.hpp"
#include "../SpeedElixir/SpeedElixir.hpp"
#include "ItemManager.hpp"
#include <fstream>

namespace Engine {

namespace Items {

ItemManager::ItemManager() {}

ItemManager::~ItemManager()
{
  for (auto item : this->m_items) {
    delete item;
  }
}

auto
ItemManager::renderItems(sf::RenderTarget& target) const -> void
{
  for (auto item : this->m_items) {
    item->render(target);
  }
}

auto
ItemManager::updateItems(Entity* player) -> void
{
  for (auto item : this->m_items) {
    if (Physics::isColliding(item->getBox(), player->getBox())) {
      item->call(player);
      this->m_deleteItem(item);
    }
  }
}

auto
ItemManager::init() -> void
{
  auto file = std::ifstream("items.txt");

  int t;
  float x, y;

  while (file >> t >> x >> y) {
    auto type = static_cast<ITEM_TYPE>(t);
    this->m_createItem(type, { x, y });
  }
}

auto
ItemManager::m_createItem(ITEM_TYPE type, const sf::Vector2f& position) -> Item*
{
  switch (type) {
    case HEART:
      return this->m_getHeart(position);
    case SPEED_ELIXIR:
      return this->m_getSpeedElixir(position);
      break;
    case POWER_ELIXIR:
      return this->m_getPowerElixir(position);
      break;
  }
}

auto
ItemManager::m_getHeart(const sf::Vector2f& position) -> Item*
{
  auto heart = new Heart(position);
  this->m_items.push_back(heart);
  return heart;
}

auto
ItemManager::m_getSpeedElixir(const sf::Vector2f& position) -> Item*
{
  auto elixir = new SpeedElixir(position);
  this->m_items.push_back(elixir);
  return elixir;
}

auto
ItemManager::m_getPowerElixir(const sf::Vector2f& position) -> Item*
{
  auto elixir = new PowerElixir(position);
  this->m_items.push_back(elixir);
  return elixir;
}

auto
ItemManager::m_deleteItem(Item* item) -> void
{
  auto iter = std::remove_if(
    this->m_items.begin(), this->m_items.end(), [item](auto it) -> bool {
      bool toBeDeleted = it == item;

      if (toBeDeleted)
        delete it;

      return toBeDeleted;
    });

  this->m_items.erase(iter, this->m_items.end());
}
}
}
