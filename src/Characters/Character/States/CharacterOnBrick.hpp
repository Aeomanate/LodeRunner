//
// Created by Aeomanate on 07.08.2021.
//

#ifndef LODE_RUNNER_CHARACTERONBRICK_HPP
#define LODE_RUNNER_CHARACTERONBRICK_HPP


#include "EntityState.hpp"

class Character;
class CharacterOnBrick: public EntityState<Character> {
  public:
    CharacterOnBrick(
        Coord direction,
        Character* character,
        TimeMs move_interval,
        TimeMs frame_delay,
        std::string character_name
    );
    
    std::unique_ptr<EntityState<Character>> Update(Coord) override;
    
  private:
    RingBuffer<ALSprite*> move_left_sprites;
    RingBuffer<ALSprite*> move_right_sprites;
    RingBuffer<ALSprite*>& cur_move_sprites;
    Timer move_timer;
};

#endif // LODE_RUNNER_CHARACTERONBRICK_HPP
