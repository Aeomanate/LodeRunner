//
// Created by Aeomanate on 08.08.2021.
//

#ifndef LODE_RUNNER_BREAKINGBRICK_HPP
#define LODE_RUNNER_BREAKINGBRICK_HPP


#include "EntityState.hpp"

class Brick;

class BreakingBrick: public EntityState<Brick> {
  public:
    explicit BreakingBrick(Brick* brick, TimeMs break_duration);
    
    std::unique_ptr<EntityState<Brick>> Update(Coord) override;
    
  private:
    RingBuffer<ALSprite*> cur_breaking_sprite;
    Timer breaking_timer;
};


#endif // LODE_RUNNER_BREAKINGBRICK_HPP
