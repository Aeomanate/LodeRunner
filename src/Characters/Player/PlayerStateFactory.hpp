//
// Created by Aeomanate on 09.08.2021.
//

#ifndef LODE_RUNNER_PLAYERSTATEFACTORY_HPP
#define LODE_RUNNER_PLAYERSTATEFACTORY_HPP


#include "CharacterStateFactory.hpp"
class Player;

class PlayerStateFactory: public CharacterStateFactory {
  public:
    explicit PlayerStateFactory(Character* player);
    
    StatePtr MakeFireIdle(Coord direction) override;
    StatePtr MakeFireLadder(Coord direction) override;
    StatePtr MakeIdle(Coord direction) override;
    StatePtr MakeJumpDown(Coord direction) override;
    StatePtr MakeFall() override;
    StatePtr MakeOnBrick(Coord direction) override;
    StatePtr MakeOnLadder() override;
    StatePtr MakeOnRope(Coord direction) override;
    StatePtr MakeStuck() override;
    StatePtr MakeLose() override;
  
};


#endif // LODE_RUNNER_PLAYERSTATEFACTORY_HPP
