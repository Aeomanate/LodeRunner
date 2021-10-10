//
// Created by Aeomanate on 09.08.2021.
//

#ifndef LODE_RUNNER_CHARACTERFALL_HPP
#define LODE_RUNNER_CHARACTERFALL_HPP

#include "EntityState.hpp"

class Character;
class CharacterFall: public EntityState<Character> {
  public:
    explicit CharacterFall(
        Character* character,
        TimeMs fall_interval,
        TimeMs animation_interval,
        std::string character_name
    );
    
    std::unique_ptr<EntityState<Character>> Update(Coord cur_pos) override;
    
    [[nodiscard]] bool IsFallState() const override;
    
  private:
    RingBuffer<ALSprite*> cur_fall_sprite;
    Timer fall_timer;
};


#endif // LODE_RUNNER_CHARACTERFALL_HPP
