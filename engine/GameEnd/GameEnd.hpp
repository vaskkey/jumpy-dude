#pragma once
#include <exception>

namespace Engine::GameEnd {
class PlayerWon : std::exception
{};

class PlayerLost : std::exception
{};
}
