//
// Created by Aeomanate on 09.08.2021.
//

#ifndef LODE_RUNNER_CHARACTER_HPP
#define LODE_RUNNER_CHARACTER_HPP

#include "Cell.hpp"
#include "CharacterMoveState.hpp"
#include "CharacterStateFactory.hpp"

class Character: public Cell {
    friend class CharacterMoveState;
    
  public:
    Character();
    
    std::unique_ptr<CharacterStateFactory>& StateFactory();
    
    bool TryFireByView();
    bool TryFire(Coord direction);
    
    void TryAddNextMove(Coord next_direction);
    [[maybe_unused]] void ForceNextDirection(Coord new_direction);
    bool TryFall(Coord cur_coord);
    
    [[nodiscard]] bool IsMoving() const;
    [[nodiscard]] bool IsFalling() const;
    [[nodiscard]] bool IsRopeMoving() const;
    [[nodiscard]] bool IsLadderMoving() const;
    [[nodiscard]] bool IsIdle() const;
    [[nodiscard]] bool IsFiring() const;
    [[nodiscard]] bool IsLose() const;
    [[nodiscard]] Coord LastDirection() const;
    [[nodiscard]] static bool IsStuckPos(Coord cur_pos);
    
    virtual void ClearGold() = 0;
    virtual void AddGold() = 0;
    virtual int DecLife();
    void SetStuck() override;
    void SetMoveInterval(TimeMs new_interval);
    [[nodiscard]] TimeMs CurrentMoveInterval() const;
  
  protected:
    CharacterMoveState move_state;
    std::unique_ptr<CharacterStateFactory> state_factory;
    std::unique_ptr<EntityState<Character>> entity_state;
};


#endif // LODE_RUNNER_CHARACTER_HPP
