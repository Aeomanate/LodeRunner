//
// Created by Aeomanate on 06.08.2021.
//

#ifndef LODE_RUNNER_CHARACTERMOVESTATE_HPP
#define LODE_RUNNER_CHARACTERMOVESTATE_HPP

#include <queue>
#include <memory>
#include <optional>
#include "AeoGameFramework.hpp"
#include "Coord.hpp"

template <class Character>
class EntityState;
class Character;
class CharacterMoveState {
    friend class Character;
    
  public:
    CharacterMoveState(Character* character);
    void Update(Coord cur_pos);
    void Draw(Coord cur_pos) const;
    
    [[nodiscard]] bool IsMoving() const;
    [[nodiscard]] bool IsNeedMoving() const;
    [[nodiscard]] Coord CurOffset() const;
    [[nodiscard]] Coord LastDirection() const;
    [[nodiscard]] TimeMs CurMoveInterval() const;
    void SetMoveInterval(TimeMs new_interval);
    void ResetDirections();
    
  private:
    void Move();
    
    [[nodiscard]] std::optional<std::unique_ptr<EntityState<Character>>>
    InitMove(Coord cur_pos);
    
    [[nodiscard]] std::optional<std::unique_ptr<EntityState<Character>>>
    OccupyOtherCell(Coord other_cell_pos, Coord cur_pos);
    
    void RemoveCurDirection();
    [[nodiscard]] Coord CurDirection() const;
    [[nodiscard]] bool IsMoveNeedToStop() const;
    
  private:
    Character* character;
    std::queue<Coord> directions;
    Timer move_timer;
    Coord cur_sprite_offset = {0, 0};
    bool is_moving = false;
    Coord last_direction = {0, 0};
};

#endif // LODE_RUNNER_CHARACTERMOVESTATE_HPP
