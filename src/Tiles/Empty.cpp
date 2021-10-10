// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 07.08.2021.
//

#include "Field.hpp"
#include "Empty.hpp"
#include "CharacterJumpDown.hpp"
#include "TransparentCell.hpp"
#include "CharacterStateFactory.hpp"
#include "EntityState.hpp"
#include "Character.hpp"

std::optional<std::unique_ptr<EntityState<Character>>>
EmptyCell::Occupy(Coord this_pos, Coord occupant_pos, Character* character, EntityChecker checker) {
    Coord move_direction = this_pos - occupant_pos;
    std::optional<std::unique_ptr<EntityState<Character>>> new_state;
    
    if(content and content->IsGold()) {
        character->AddGold();
        if(move_direction.y == 0) {
            new_state = character->StateFactory()->MakeOnBrick(move_direction);
            content = g_field->ExtractEntity(occupant_pos, checker);
        } else if(move_direction.y > 0) {
            if(character->IsFalling()) {
                new_state = std::nullopt;
            } else {
                new_state = character->StateFactory()->MakeJumpDown(character->LastDirection());
            }
            content = g_field->ExtractEntity(occupant_pos, checker);
        } else {
            new_state = nullptr;
        }
    }
    else if(move_direction.y < 0) {
        // Without jumps (to rope or from ladder to up)!
        if(content) {
            new_state = content->Occupy(this_pos, occupant_pos, character, checker);
        } else {
            new_state = nullptr;
        }
    }
    else if(move_direction.y == 0) {
        if(not content) {
            new_state = character->StateFactory()->MakeOnBrick(move_direction);
            content = g_field->ExtractEntity(occupant_pos, &Cell::IsPlayer);
        } else {
            new_state = content->Occupy(this_pos, occupant_pos, character, checker);
        }
    }
    else if(move_direction.y > 0) {
        if(not content) {
            if(character->IsFalling()) {
                new_state = std::nullopt;
            } else {
                new_state = character->StateFactory()->MakeJumpDown(character->LastDirection());
            }
            content = g_field->ExtractEntity(occupant_pos, &Cell::IsPlayer);
        } else {
            new_state = content->Occupy(this_pos, occupant_pos, character, checker);
        }
    }
    
    return new_state;
}

bool EmptyCell::IsOccupiable(Coord this_pos, Coord from_pos) const {
    if(not content) return this_pos - from_pos != Coord{0, -1};
    return content->IsOccupiable(this_pos, from_pos);
}

DrawQueue EmptyCell::GetDrawOrder() const {
    DrawQueue draw_queue;
    draw_queue.push(this);
    if(content) {
        if(content->IsPlayer()) {
            // Because other cells have content that may draw after player (e.g. ladder).
            draw_queue.push(g_transparent_cell.get());
            draw_queue.push(content.get());
        } else {
            additionAssign(draw_queue, content->GetDrawOrder());
        }
    }
    return draw_queue;
}
