// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 08.08.2021.
//

#include "CharacterMoveState.hpp"
#include "EntityState.hpp"
#include "Player.hpp"
#include "Field.hpp"


CharacterMoveState::CharacterMoveState(Character* character)
: character(character)
{ }

void CharacterMoveState::Update(Coord cur_pos) {
    if(IsMoving()) {
        Move();
    } else if(IsNeedMoving()) {
        std::optional<std::unique_ptr<EntityState<Character>>> new_state = InitMove(cur_pos);
        if(new_state) {
            if(*new_state == nullptr) {
                return;
            } else {
                character->entity_state = std::move(*new_state);
            }
        }
    }
}

void CharacterMoveState::Draw(Coord cur_pos) const {
    Coord draw_pos = cur_pos * Cell::dss + character->move_state.CurOffset();
    character->sprite->Draw(draw_pos.x, draw_pos.y);
}

bool CharacterMoveState::IsMoving() const {
    return is_moving;
}
bool CharacterMoveState::IsNeedMoving() const {
    return not directions.empty();
}

void CharacterMoveState::Move() {
    if(not move_timer.IfExpiredThenStart()) return;
    cur_sprite_offset += CurDirection();
    if(IsMoveNeedToStop()) {
        is_moving = false;
        last_direction = CurDirection();
        RemoveCurDirection();
    }
}

std::optional<std::unique_ptr<EntityState<Character>>>
CharacterMoveState::InitMove(Coord cur_pos) {
    Coord new_pos = cur_pos + directions.front();
    
    if(not Field::IsInField(new_pos)) {
        RemoveCurDirection();
        return nullptr; // Revoke this move.
    }
    
    std::optional<std::unique_ptr<EntityState<Character>>> new_state =
        OccupyOtherCell(new_pos, cur_pos);
    
    if(new_state and *new_state == nullptr) {
        RemoveCurDirection();
        return nullptr; // Cell cannot be occupied, revoke move.
    }
        // If new_state == std::nullopt
        // Than state not change, the movement is same.
    
    is_moving = true;
    cur_sprite_offset = -CurDirection() * Cell::default_sprite_size;
    return new_state;
}

std::optional<std::unique_ptr<EntityState<Character>>>
CharacterMoveState::OccupyOtherCell(Coord other_cell_pos, Coord cur_pos) {
    return g_field->CellAtCoord(other_cell_pos)->
           Occupy(other_cell_pos, cur_pos, character, &Cell::IsPlayer);
}

Coord CharacterMoveState::CurOffset() const {
    return cur_sprite_offset;
}

Coord CharacterMoveState::LastDirection() const {
    return last_direction;
}

TimeMs CharacterMoveState::CurMoveInterval() const {
    return move_timer.Interval();
}

void CharacterMoveState::SetMoveInterval(TimeMs new_interval) {
    move_timer.SetInterval(new_interval);
}

void CharacterMoveState::ResetDirections() {
    while(not directions.empty()) directions.pop();
}

void CharacterMoveState::RemoveCurDirection() {
    directions.pop();
}

Coord CharacterMoveState::CurDirection() const {
    return directions.front();
}

bool CharacterMoveState::IsMoveNeedToStop() const {
    return cur_sprite_offset == Coord{0, 0};
}
