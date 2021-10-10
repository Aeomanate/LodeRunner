// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 09.08.2021.
//

#include "RecoveringBrick.hpp"
#include "Brick.hpp"


RecoveringBrick::RecoveringBrick(Brick* brick, TimeMs recovery_duration)
: EntityState(brick, "brick")
{
    cur_recovery_sprite = {
        &Sprites::smap["restore_0"],
        &Sprites::smap["restore_1"],
        &Sprites::smap["restore_2"],
        &Sprites::smap["restore_3"],
        &Sprites::smap["brick"],
    };
    
    recovery_timer.SetInterval(recovery_duration / (TimeMs)cur_recovery_sprite.size());
    entity->sprite = cur_recovery_sprite;
}

std::unique_ptr<EntityState<Brick>> RecoveringBrick::Update(Coord) {
    if(not recovery_timer.IsStarted()) {
        recovery_timer.Start();
        return nullptr;
    }
    
    if(cur_recovery_sprite.IsEnd()) {
        if(entity->content and entity->breaking_state->IsEmptyState()) {
            entity->content->SetStuck();
        }
        return std::make_unique<EmptyState<Brick>>();
    }
    
    if(recovery_timer.IfExpiredThenStart()) {
        entity->sprite = cur_recovery_sprite.Next();
    }
    
    return nullptr;
}