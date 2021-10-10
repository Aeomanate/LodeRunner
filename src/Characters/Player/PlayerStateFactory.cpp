// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
//
// Created by Aeomanate on 09.08.2021.
//

#include <CharacterLose.hpp>
#include "Character/States/Fire/CharacterFireIdleRight.hpp"
#include "Character/States/Fire/CharacterFireIdleLeft.hpp"
#include "Character/States/Fire/CharacterFireLadderRight.hpp"
#include "Character/States/Fire/CharacterFireLadderLeft.hpp"
#include "CharacterStuck.hpp"
#include "CharacterIdle.hpp"
#include "CharacterOnRope.hpp"
#include "CharacterJumpDown.hpp"
#include "CharacterFall.hpp"
#include "CharacterOnBrick.hpp"
#include "CharacterOnLadder.hpp"
#include "PlayerStateFactory.hpp"

PlayerStateFactory::PlayerStateFactory(Character* player)
: CharacterStateFactory(player)
{ }

StatePtr PlayerStateFactory::MakeFireIdle(Coord direction) {
    if(direction.x > 0) {
        return std::make_unique<CharacterFireIdleRight>(character, 100, "player");
    } else if(direction.x < 0) {
        return std::make_unique<CharacterFireIdleLeft>(character, 100, "player");
    }
    return nullptr;
}

StatePtr PlayerStateFactory::MakeFireLadder(Coord direction) {
    if(direction.x > 0) {
        return std::make_unique<CharacterFireLadderRight>(character, 100, "player");
    } else if(direction.x < 0) {
        return std::make_unique<CharacterFireLadderLeft>(character, 100, "player");
    }
    
    return nullptr;
}

StatePtr PlayerStateFactory::MakeIdle(Coord direction) {
    return std::make_unique<CharacterIdle>(character, direction, "player");
}

StatePtr PlayerStateFactory::MakeJumpDown(Coord direction) {
    return std::make_unique<CharacterJumpDown>(direction, character, 8, "player");
}

StatePtr PlayerStateFactory::MakeFall() {
    return std::make_unique<CharacterFall>(character, 10, 80, "player");
}

StatePtr PlayerStateFactory::MakeOnBrick(Coord direction) {
    return std::make_unique<CharacterOnBrick>(direction, character, 8, 80, "player");
}

StatePtr PlayerStateFactory::MakeOnLadder() {
    return std::make_unique<CharacterOnLadder>(character, 15, 80, "player");
}

StatePtr PlayerStateFactory::MakeOnRope(Coord direction) {
    return std::make_unique<CharacterOnRope>(direction, character, 18, 80, "player");
}

StatePtr PlayerStateFactory::MakeStuck() {
    return std::make_unique<CharacterStuck>(character, 100500, 120, "player");
}

StatePtr PlayerStateFactory::MakeLose() {
    return std::make_unique<CharacterLose>(character, "player");
}

