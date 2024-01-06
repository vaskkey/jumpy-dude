#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

#include "../Entity/Entity.hpp"

namespace Engine::Physics {

auto
manageWindowCollision(const sf::RenderWindow& window, Entity& entity) -> void;

}
