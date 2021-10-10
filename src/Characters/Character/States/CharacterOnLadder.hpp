//
// Created by Aeomanate on 08.08.2021.
//

#ifndef LODE_HPP_PLAYERONLADDER_HPP
#define LODE_HPP_PLAYERONLADDER_HPP


#include "EntityState.hpp"

class Character;

class CharacterOnLadder: public EntityState<Character> {
  public:
    CharacterOnLadder(
        Character* player,
        TimeMs move_interval,
        TimeMs animation_interval,
        std::string character_name
    );
    
    std::unique_ptr<EntityState<Character>> Update(Coord cur_pos) override;
    
    [[nodiscard]] bool IsOnLadderState() const override;
    
  private:
    RingBuffer<ALSprite*> cur_frame;
    Timer animation_timer;
};


#endif // LODE_HPP_PLAYERONLADDER_HPP
