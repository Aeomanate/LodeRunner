//
// Created by Aeomanate on 07.08.2021.
//

#ifndef LODE_RUNNER_CHARACTERJUMPDOWN_HPP
#define LODE_RUNNER_CHARACTERJUMPDOWN_HPP


#include "EntityState.hpp"

class Character;
class CharacterJumpDown: public EntityState<Character> {
  public:
    explicit CharacterJumpDown(
        Coord direction,
        Character* character,
        TimeMs fall_interval,
        std::string character_name
    );
    
    std::unique_ptr<EntityState<Character>> Update(Coord cur_pos) override;
    
    [[nodiscard]] bool IsFallState() const override;
    
  private:
};


#endif // LODE_RUNNER_CHARACTERJUMPDOWN_HPP
