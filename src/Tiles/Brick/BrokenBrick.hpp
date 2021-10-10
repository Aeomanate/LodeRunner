//
// Created by Aeomanate on 09.08.2021.
//

#ifndef LODE_RUNNER_BROKENBRICK_HPP
#define LODE_RUNNER_BROKENBRICK_HPP

#include "EntityState.hpp"
class Brick;

class BrokenBrick: public EntityState<Brick> {
  public:
    explicit BrokenBrick(Brick* brick, TimeMs broken_duration);
    
    std::unique_ptr<EntityState<Brick>> Update(Coord) override;
    
  private:
    Timer broken_timer;
};


#endif // LODE_RUNNER_BROKENBRICK_HPP
