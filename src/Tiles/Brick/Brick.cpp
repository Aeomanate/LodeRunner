// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and Cur#: http://www.viva64.com
//
// Created by Aeomanate on 06.08.2021.
//

#include <memory>
#include "Brick.hpp"
#include "Drawer.hpp"
#include "BreakingBrick.hpp"
#include "Field.hpp"
#include "BrokenBrick.hpp"
#include "RecoveringBrick.hpp"
#include "CharacterStateFactory.hpp"
#include "Character.hpp"

void Brick::Update(Coord cur_pos) {
    Cell::Update(cur_pos);
    while(true) {
        std::unique_ptr<EntityState<Brick>> new_state = breaking_state->Update(cur_pos);
        if(new_state == nullptr) break;
        breaking_state = std::move(new_state);
    }
}

DrawQueue Brick::GetDrawOrder() const {
    DrawQueue draw_queue;
    if(content) {
        additionAssign(draw_queue, content->GetDrawOrder());
    }
    draw_queue.push(this);
    return draw_queue;
}

bool Brick::IsBreackable() const { return breaking_state->IsEmptyState(); }
bool Brick::TryBreak() {
    if(IsBreackable()) {
        breaking_state = MakeBreakingState();
        return true;
    }
    return false;
}


bool Brick::IsOccupiable(Coord, Coord) const {
    return not breaking_state->IsEmptyState(); // Otherwise, state is breaking.
}

std::optional<std::unique_ptr<EntityState<Character>>>
Brick::Occupy(Coord cur_pos, Coord occupant_pos, Character* character, EntityChecker checker) {
    std::optional<std::unique_ptr<EntityState<Character>>> new_state;

    if(IsOccupiable(cur_pos, occupant_pos)) {
        if(not character->IsFalling()) {
            new_state = character->StateFactory()->MakeJumpDown(cur_pos - occupant_pos);
        }
        content = g_field->ExtractEntity(occupant_pos, &Cell::IsPlayer);
    } else {
        return nullptr;
    }
    
    return new_state;
}

std::unique_ptr<EntityState<Brick>> Brick::MakeBreakingState() {
    return std::make_unique<BreakingBrick>(this, 500);
}

std::unique_ptr<EntityState<Brick>> Brick::MakeBrokenState() {
    return std::make_unique<BrokenBrick>(this, 3000);
}

std::unique_ptr<EntityState<Brick>> Brick::MakeRecoveringState() {
    return std::make_unique<RecoveringBrick>(this, 5000);
}


