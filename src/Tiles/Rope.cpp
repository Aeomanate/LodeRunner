// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 07.08.2021.
//

#include "Rope.hpp"
#include "Field.hpp"
#include "CharacterStateFactory.hpp"
#include "Character.hpp"
#include "EntityState.hpp"

bool Rope::IsOccupiable(Coord, Coord) const { return true; }
bool Rope::IsContainRope() const { return true; }

std::optional<std::unique_ptr<EntityState<Character>>>
Rope::Occupy(Coord this_pos, Coord occupant_pos, Character* character, EntityChecker checker) {
    std::optional<std::unique_ptr<EntityState<Character>>> new_state;
    Coord direction = this_pos - occupant_pos;
    
    if(not content) {
        if(direction.y == 0) {
            if(not character->IsRopeMoving()) {
                new_state = character->StateFactory()->MakeOnRope(direction);
            }
            content = g_field->ExtractEntity(occupant_pos, &Cell::IsPlayer);
        } else if(direction.y > 0) {
            content = g_field->ExtractEntity(occupant_pos, &Cell::IsPlayer);
        } else {
            if(g_field->CellAtCoord(occupant_pos)->IsContainLadder()) {
                content = g_field->ExtractEntity(occupant_pos, &Cell::IsPlayer);
            } else {
                return nullptr;
            }
        }
    } else {
        new_state = content->Occupy(this_pos, occupant_pos, character, checker);
    }
    
    return new_state;
}
