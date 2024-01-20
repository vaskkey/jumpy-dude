#pragma once

#include "../Entity/Entity.hpp"
#include "../EntityFactory/EntityFactory.hpp"
#include "../Items/ItemManager/ItemManager.hpp"
#include "../TileManager/TileManager.hpp"

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Window/Keyboard.hpp"

namespace Engine {
/**
 * Game class representing the main game loop and logic.
 */
class Game
{
  sf::RenderWindow m_window;  /**< Render window for the game. */
  sf::View m_view;            /**< View for the game. */
  sf::Texture m_worldTexture; /**< Texture for the game world. */
  sf::Sprite m_worldBg;       /**< Background sprite for the game world. */

  Items::ItemManager
    m_itemManager;               /**< Item manager for managing game items. */
  TileManager m_tileManager;     /**< Tile manager for managing game tiles. */
  EntityFactory m_entityFactory; /**< Entity factory for creating entities. */
  Entity* m_player;              /**< Pointer to the player entity. */

  sf::Text m_hpText; /**< UI Text telling how much HP player has */
  sf::Font m_font;   /**< UI font */
  float m_cameraX;   /** X position of the Camera */

  bool m_gameOver = false; /* Determines which screen to show */

public:
  /**
   * Constructor for the Game class.
   */
  Game();

  /**
   * Main game loop.
   */
  auto loop() -> void;

private:
  /**
   * Handles events in the game.
   */
  auto m_handleEvents() -> void;

  /**
   * Draws the game.
   */
  auto m_draw() -> void;

  /**
   * Updates the view of the game.
   */
  auto m_updateView() -> void;

  /**
   * Updates UI data.
   * e.g. HP.
   *
   * x Position of a camera
   */
  auto m_updateUI() -> void;

  /**
   * Handles a key event.
   *
   * @param key The key that was pressed or released.
   * @param value The value indicating if the key was pressed or released.
   */
  auto m_handleKeyEvent(const sf::Keyboard::Key& key, bool value) -> void;

  /**
   * Handles game end.
   *
   * @param str String to display to player.
   */
  auto m_endScreen(const std::string& str) -> void;

  /**
  * Handles events and rendering while game is ongoing.
  */
  auto m_handleGame() -> void;
};

}
