//
// Created by Aeomanate on 08.08.2021.
//

#ifndef LODE_RUNNER_CHARACTERONROPE_HPP
#define LODE_RUNNER_CHARACTERONROPE_HPP

#include "EntityState.hpp"

class Character;
class CharacterOnRope: public EntityState<Character> {
  public:
    CharacterOnRope(
        Coord direction,
        Character* character,
        TimeMs move_interval,
        TimeMs animation_interval,
        std::string character_name
    );
    
    std::unique_ptr<EntityState<Character>> Update(Coord cur_pos) override;
    [[nodiscard]] bool IsOnRopeState() const override;
    
  private:
    RingBuffer<ALSprite*> on_rope_left;
    RingBuffer<ALSprite*> on_rope_right;
    RingBuffer<ALSprite*>& cur_frame;
    Timer animation_timer;
};


#endif // LODE_RUNNER_CHARACTERONROPE_HPP
