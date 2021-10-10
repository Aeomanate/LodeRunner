//
// Created by Aeomanate on 10.08.2021.
//

#ifndef LODE_RUNNER_CHARACTERLOSE_HPP
#define LODE_RUNNER_CHARACTERLOSE_HPP

#include "EntityState.hpp"
class Character;

class CharacterLose: public EntityState<Character> {
  public:
    CharacterLose(Character* character, std::string character_name);
    bool IsLoseState() const override;
    std::unique_ptr<EntityState<Character>> Update(Coord) override { return nullptr; }
};


#endif // LODE_RUNNER_CHARACTERLOSE_HPP
