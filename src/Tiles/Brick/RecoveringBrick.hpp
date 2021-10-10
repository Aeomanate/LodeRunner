//
// Created by Aeomanate on 09.08.2021.
//

#ifndef LODE_RUNNER_RECOVERINGBRICK_HPP
#define LODE_RUNNER_RECOVERINGBRICK_HPP

#include "EntityState.hpp"
class Brick;

class RecoveringBrick: public EntityState<Brick> {
  public:
    explicit RecoveringBrick(Brick* brick, TimeMs recovery_duration = 1500);
    
    std::unique_ptr<EntityState<Brick>> Update(Coord) override;
    
  private:
    RingBuffer<ALSprite*> cur_recovery_sprite;
    Timer recovery_timer;
};


#endif // LODE_RUNNER_RECOVERINGBRICK_HPP
