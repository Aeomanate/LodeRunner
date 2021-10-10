//
// Created by Aeomanate on 10.08.2021.
//

#ifndef LODE_RUNNER_CHARACTERFIRELADDERLEFT_HPP
#define LODE_RUNNER_CHARACTERFIRELADDERLEFT_HPP

#include "EntityState.hpp"
class Character;

class CharacterFireLadderLeft: public EntityState<Character> {
  public:
    explicit CharacterFireLadderLeft(
        Character* character,
        TimeMs animation_interval,
        std::string character_name
        );
    
    std::unique_ptr<EntityState<Character>> Update(Coord cur_pos) override;
    
    [[nodiscard]] bool IsFiringState() const override;
    
  private:
    Timer fire_timer;
};


#endif // LODE_RUNNER_CHARACTERFIRELADDERLEFT_HPP
