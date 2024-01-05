#include "Engine/Game/Game.hpp"

auto
main() -> int
{
  auto game = Engine::Game();

  game.loop();
}
