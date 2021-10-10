//
// Created by Aeomanate on 09.08.2021.
//

#ifndef LODE_RUNNER_CHARACTERSTUCK_HPP
#define LODE_RUNNER_CHARACTERSTUCK_HPP

#include "EntityState.hpp"

class Character;
class CharacterStuck: public EntityState<Character> {
  public:
    explicit CharacterStuck(
        Character* character,
        TimeMs fall_interval,
        TimeMs animation_interval,
        std::string character_name
    );
    
    std::unique_ptr<EntityState<Character>> Update(Coord cur_pos) override;
    
    [[nodiscard]] bool IsStuckState() const override;
  private:
    RingBuffer<ALSprite*> cur_sprite;
    Timer anim_timer;
    Timer max_stuck_timer;
};


#endif // LODE_RUNNER_CHARACTERSTUCK_HPP
