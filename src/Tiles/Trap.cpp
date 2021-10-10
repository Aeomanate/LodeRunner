// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 07.08.2021.
//

#include <cassert>
#include "Trap.hpp"
#include "Field.hpp"
#include "TransparentCell.hpp"
#include "Character.hpp"
#include "CharacterStateFactory.hpp"
#include "EntityState.hpp"

bool Trap::IsOccupiable(Coord, Coord) const  {
    return false;
}

bool Trap::IsContainTrap() const {
    return true;
}

std::optional<std::unique_ptr<EntityState<Character>>>
Trap::Occupy(Coord this_pos, Coord occupant_pos, Character* player, EntityChecker) {
    Coord direction = this_pos - occupant_pos;
    if(direction.x == 0) {
        if(direction.y > 0) {
            content = g_field->ExtractEntity(occupant_pos, &Cell::IsPlayer);
            return player->StateFactory()->MakeFall();
        }
    } else {
        assert(direction.y == 0 and "Diagonal move restricted");
        content = g_field->ExtractEntity(occupant_pos, &Cell::IsPlayer);
        return player->StateFactory()->MakeOnBrick(direction);
    }
    
    if(direction.y < 0) {
        return nullptr;
    }
    
    throw std::logic_error("Other way to pass through trap?");
}

DrawQueue Trap::GetDrawOrder() const {
    DrawQueue draw_queue;
    if(content) {
        draw_queue.push(content.get());
        additionAssign(draw_queue, content->GetDrawOrder());
    }
    // No one entity will not draw after trap.
    draw_queue.push(g_transparent_cell.get());
    draw_queue.push(g_transparent_cell.get());
    draw_queue.push(this);
    
    return draw_queue;
}
