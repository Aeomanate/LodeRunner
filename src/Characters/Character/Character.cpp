// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 09.08.2021.
//

#include "Character.hpp"
#include "Field.hpp"
#include "EntityState.hpp"


Character::Character()
: move_state(this)
{ }

std::unique_ptr<CharacterStateFactory>& Character::StateFactory() {
    return state_factory;
}

bool Character::TryFireByView() {
    return TryFire(entity_state->CurViewDirection());
}

bool Character::TryFire(Coord direction) {
    if(not IsIdle() and not IsLadderMoving()) return false;
    
    std::unique_ptr<EntityState<Character>> new_state;
    if(IsIdle()) {
        new_state = state_factory->MakeFireIdle(direction);
        if(new_state) entity_state = std::move(new_state);
        return true;
    }
    else if(IsLadderMoving()) {
        new_state = state_factory->MakeFireLadder(direction);
        if(new_state) entity_state = std::move(new_state);
        return true;
    }
    return false;
}

void Character::TryAddNextMove(Coord next_direction) {
    if(not move_state.directions.empty() or entity_state->IsFiringState()) {
        return;
    }
    move_state.directions.push(next_direction);
}

void Character::ForceNextDirection(Coord new_direction) {
    move_state.ResetDirections();
    move_state.directions.push(new_direction);
}

bool Character::TryFall(Coord cur_coord) {
    Coord occupied_cell = cur_coord + Coord{0, 1};
    auto& below_cell = g_field->CellAtCoord(occupied_cell);
    
    bool is_occupiable = below_cell->IsOccupiable(occupied_cell, cur_coord);
    bool is_trap = below_cell->IsContainTrap();
    
    if(not (is_occupiable or is_trap)) return false;
    
    ForceNextDirection({0, 1});
    return true;
}

Coord Character::LastDirection() const { return move_state.LastDirection(); }
bool Character::IsFalling() const { return entity_state->IsFallState(); }
bool Character::IsMoving() const { return move_state.IsMoving(); }
bool Character::IsRopeMoving() const { return entity_state->IsOnRopeState(); }
bool Character::IsLadderMoving() const { return entity_state->IsOnLadderState(); }
bool Character::IsIdle() const { return entity_state->IsIdleState(); }
bool Character::IsFiring() const { return entity_state->IsFiringState(); }
bool Character::IsLose() const { return entity_state->IsLoseState(); }
bool Character::IsStuckPos(Coord cur_pos) {
    bool is_pass_exist = false;
    
    for(Coord direction: { Coord{1, 0}, Coord{-1, 0}, Coord{0, 1} }) {
        Coord near_pos = cur_pos + direction;
        bool is_in_field = Field::IsInField(near_pos);
        if(not is_in_field) {
            continue;
        }
        
        bool is_occupiable = g_field->CellAtCoord(near_pos)->IsOccupiable(near_pos, cur_pos);
        if(is_occupiable) {
            is_pass_exist = true;
            break;
        }
    }
    
    return not is_pass_exist;
}


int Character::DecLife() {
    entity_state = StateFactory()->MakeIdle(randIntXCoord(-1, 1));
    return 0;
}

void Character::SetMoveInterval(TimeMs new_interval) {
    move_state.SetMoveInterval(new_interval);
}
TimeMs Character::CurrentMoveInterval() const {
    return move_state.CurMoveInterval();
}
void Character::SetStuck() {
    if(not entity_state->IsStuckState()) entity_state = state_factory->MakeStuck();
}
