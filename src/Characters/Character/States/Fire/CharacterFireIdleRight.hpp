//
// Created by Aeomanate on 10.08.2021.
//

#ifndef LODE_RUNNER_CHARACTERFIREIDLERIGHT_HPP
#define LODE_RUNNER_CHARACTERFIREIDLERIGHT_HPP

#include "EntityState.hpp"
class Character;

class CharacterFireIdleRight: public EntityState<Character> {
  public:
    explicit CharacterFireIdleRight(
        Character* character,
        TimeMs animation_interval,
        std::string character_name
    );
    
    std::unique_ptr<EntityState<Character>> Update(Coord cur_pos) override;
    
    bool IsFiringState() const override;
    
  private:
    RingBuffer<ALSprite*> cur_fire_sprite;
    Timer fire_timer;
};


#endif // LODE_RUNNER_CHARACTERFIREIDLERIGHT_HPP
