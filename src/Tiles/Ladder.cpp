// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 07.08.2021.
//

#include <Character/States/CharacterOnLadder.hpp>
#include "Ladder.hpp"
#include "Field.hpp"
#include "Character.hpp"
#include "CharacterStateFactory.hpp"

bool Ladder::IsOccupiable(Coord this_pos, Coord from_pos) const {
    bool is_ladder_below = g_field->CellAtCoord(from_pos)->IsContainLadder();
    Coord direction = this_pos - from_pos;
    bool is_move_up = direction == Coord{0, -1};
    return not is_move_up or is_ladder_below;
}

std::optional<std::unique_ptr<EntityState<Character>>>
Ladder::Occupy(Coord this_pos, Coord occupant_pos, Character* character, EntityChecker checker) {
    std::optional<std::unique_ptr<EntityState<Character>>> new_state;
    
    if(not content) {
        if(not character->IsLadderMoving()) {
            new_state = character->StateFactory()->MakeOnLadder();
        }
        content = g_field->ExtractEntity(occupant_pos, &Cell::IsPlayer);
    } else {
        new_state = content->Occupy(this_pos, occupant_pos, character, checker);
    }
    
    return new_state;
}

bool Ladder::IsLadder() const { return true; }

bool Ladder::IsContainLadder() const { return true; }
