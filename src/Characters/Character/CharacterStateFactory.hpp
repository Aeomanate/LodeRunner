//
// Created by Aeomanate on 09.08.2021.
//

#ifndef LODE_RUNNER_CHARACTERSTATEFACTORY_HPP
#define LODE_RUNNER_CHARACTERSTATEFACTORY_HPP

#include <memory>
#include "Coord.hpp"
#include "EntityState.hpp"

template <class Character>
class EntityState;
class Character;

using StatePtr = std::unique_ptr<EntityState<Character>>;

class CharacterStateFactory;
template<class... Params>
using StateMakerF = StatePtr (CharacterStateFactory::*)(Params...);

class CharacterStateFactory {
  public:
    explicit CharacterStateFactory(Character* character): character(character) { }
    virtual ~CharacterStateFactory() = default;
    
    inline static StatePtr CreateEmpty() { return EmptyState<Character>::Make(); }
    virtual StatePtr MakeFireIdle(Coord direction) = 0;
    virtual StatePtr MakeFireLadder(Coord direction) = 0;
    virtual StatePtr MakeIdle(Coord direction) = 0;
    virtual StatePtr MakeJumpDown(Coord direction) = 0;
    virtual StatePtr MakeFall() = 0;
    virtual StatePtr MakeOnBrick(Coord direction) = 0;
    virtual StatePtr MakeOnLadder() = 0;
    virtual StatePtr MakeOnRope(Coord direction) = 0;
    virtual StatePtr MakeStuck() = 0;
    virtual StatePtr MakeLose() = 0;
  
  protected:
    Character* character;
    
};


#endif // LODE_RUNNER_CHARACTERSTATEFACTORY_HPP
