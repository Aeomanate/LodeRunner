//
// Created by Aeomanate on 08.08.2021.
//

#ifndef LODE_RUNNER_SPRITES_HPP
#define LODE_RUNNER_SPRITES_HPP


#include <unordered_map>
#include "AeoGameFramework.hpp"

namespace Sprites {
  extern std::unordered_map<std::string, ALSprite> smap;
  void load();
}


#endif // LODE_RUNNER_SPRITES_HPP
